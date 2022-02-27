#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE* fp;
int WIDTH, HEIGHT;
int* horizontal;
int* vertical;
int* maze_set;
int group = 0;
int prev_wall = -1;
int prev_set;

void get_size(void);
void allocate_memory(void);
void open_maze_file(void);
void draw_border(void);
void set_first_line(void);
void draw_vertical(void);
void draw_horizontal(void);
void break_down(void);
void break_side(void);
void break_side_last(void);
void finish_program(void);

void get_size(void) {
    /* Get WIDTH, HEIGHT */
    printf("WIDTH: ");
    scanf("%d", &WIDTH);
    printf("HEIGHT: ");
    scanf("%d", &HEIGHT);
    if (WIDTH < 0 || HEIGHT < 0) {
        printf("Error! Width and height should be positive integer.\n");
        exit(1);
    }
}

void allocate_memory(void) {
    /* Allocate memory */
    horizontal = (int*)malloc(sizeof(int) * WIDTH);
    vertical = (int*)calloc((WIDTH-1), sizeof(int)); //Initialize to 0
    maze_set = (int*)calloc(WIDTH, sizeof(int)); //Initialize to 0
    if (!(horizontal && vertical && maze_set)) {
        printf("Error! Memory allocation error.\n");
        exit(1);
    }
}

void open_maze_file(void) {
    /* Make .maz file */
    fp = fopen("MazeGenerated.maz", "wt");
    if (fp == NULL) {
        printf("Error! Cannot open maze file.\n");
        finish_program();
        exit(1);
    }
}

void draw_border(void) {
    /* Draw blocked ceiling or floor. */
    for (int i = 0; i < WIDTH; i++) {
        fprintf(fp, "+-");
    }
    fprintf(fp, "+\n");
}

void set_first_line(void) {
    /* 첫 번째 라인의 세로 벽을 세우며 group을 정한다. */
    int i, j;
    for (i = 0; i < WIDTH-1; i++) {
        vertical[i] = rand() % 2; //0(뚫는다) or 1(막는다)
        if (vertical[i]) { //막혀 있다면 이전 벽들을 깬다.
            for (j = (prev_wall+1); j <= i; j++) {
                maze_set[j] = group; //같은 그룹으로 만든다.
            }
            prev_wall = i; //이전 벽 위치 set
            group++; //다음 그룹으로 set
        }
    }
    for (i = prev_wall + 1; i < WIDTH; i++) { //남은 부분 group
        maze_set[i] = group;
    }
    group++;
}

void draw_vertical(void) {
    /* Print vertical wall */
    fprintf(fp, "|");
    for (int i = 0; i < WIDTH-1; i++) {
        fprintf(fp, " ");
        if (vertical[i])
            fprintf(fp, "|");
        else
            fprintf(fp, " ");
    }
    fprintf(fp, " |\n");
}

void draw_horizontal(void) {
    /* Print horizontal wall */
    fprintf(fp, "+");
    for (int i = 0; i < WIDTH; i++) {
        if (horizontal[i]) //막힌 곳
            fprintf(fp, "-+");
        else               //뚫린 곳
            fprintf(fp, " +");
    }
    fprintf(fp, "\n");
}


void break_down(void) {
    /* +-+-+-+-+-+ 중에서 어느 -를 뚫을 것인가 */
    int prev_group = maze_set[0];
    int broken = 0;
    int i;

    for (i = 0; i < WIDTH; i++) {
        horizontal[i] = rand() % 2; //0(뚫는다) or 1(막는다)
        if (!horizontal[i]) { //뚫었다면 뚫었다고 표시한다.
            broken = 1;
        }
        if (horizontal[i]) { //막힌 곳은 다른 group으로 지정한다.
            maze_set[i] = group;
            group++;
        }
        if (i < WIDTH-1) {
            if (prev_group != maze_set[i+1]) {
                if (!broken) { //한 번도 뚫지 않았다면 최소 한 번은 뚫어야 한다.
                    horizontal[i] = 0;
                }
                else {
                    broken = 0;
                }
                prev_group = maze_set[i+1];
            }
        }
    }
    if (!broken) { //끝까지 한 번도 뚫지 않았다면 뚫어줘야 한다.
        horizontal[i-1] = 0;
    }
}

void break_side(void) {
    /* | | | | | | |에서 어떤 |를 뚫어줄 것인가 */
    int break_flag = 0;
    int prev_group;
    int i, j;
    
    for (i = 0; i < WIDTH-1; i++) {
        //같은 그룹끼리 인접할 때는 벽을 제거하지 않는다.
        if (maze_set[i] == maze_set[i+1]) {
            vertical[i] = 1;
        }
        //다른 그룹끼리 인접할 때는 벽을 제거할지, 막아둘지 랜덤으로 결정한다.
        else {
            break_flag = rand() % 2; //0(뚫는다) or 1(막는다)
            //뚫는 경우
            if (break_flag) {
                vertical[i] = 0; //벽을 뚫는다.
                prev_group = maze_set[i+1]; //합치기 전 그 그룹의 번호를 저장해둔다.
                maze_set[i+1] = maze_set[i]; //같은 group으로 합친다.
                for (j = 0; j < WIDTH; j++) { //prev_group의 번호를 가진 group을 모두 합쳐준다.
                    if (maze_set[j] == prev_group)
                        maze_set[j] = maze_set[i];
                }
            }
            //막는 경우
            else {
                vertical[i] = 1; //벽을 세워둔다.
            }
        }
    }
}

void break_side_last(void) {
    /* | | | | | | |에서 어떤 |를 뚫어줄 것인가 */
    /* 가장 마지막 라인이므로, 다른 집합이 인접했다면 무조건 뚫어준다. */
    int prev_group;
    int i, j;
    
    for (i = 0; i < WIDTH-1; i++) {
        //같은 그룹끼리 인접할 때는 벽을 제거하지 않는다.
        if (maze_set[i] == maze_set[i+1]) {
            vertical[i] = 1; //벽을 세워둔다.
        }
        //다른 그룹끼리 인접할 때는 벽을 제거할지, 막아둘지 랜덤으로 결정한다.
        else {
            vertical[i] = 0; //벽을 뚫는다.
            prev_group = maze_set[i+1]; //합치기 전 그 그룹의 번호를 저장해둔다.
            maze_set[i+1] = maze_set[i]; //같은 group으로 합친다.
            for (j = 0; j < WIDTH; j++) { //prev_group의 번호를 가진 group을 모두 합쳐준다.
                if (maze_set[j] == prev_group)
                    maze_set[j] = maze_set[i];
            }
        }
    }
}

void finish_program(void) {
    /* close .maz file */
    if (fp != NULL) {
        fclose(fp);
    }
    
    /* Deallocation */
    free(horizontal);
    free(vertical);
    free(maze_set);
}
