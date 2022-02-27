#include <stdio.h>
#include "20000000.h"

int main(void) {
    
    /* Get WIDTH, HEIGHT */
    get_size();
    
    /* Allocate memory */
    allocate_memory();
    
    /* Make .maz file */
    open_maze_file();
    
    /* Draw the top horizontal wall.
       It should be blocked. */
    draw_border();
    
    /* Exception: If HEIGHT==1, then maze should not be blocked. */
    if (HEIGHT == 1) {
        draw_vertical();
        draw_border();
        finish_program();
        return 0;
    }
    
    /* Randomization */
    srand((unsigned)time(NULL));
    
    /* 첫 번째 라인의 세로 벽을 세우며 group을 정한다. */
    set_first_line();
    
    /* 첫 번째 라인의 세로 벽을 그린다. */
    draw_vertical();
    
    /* 각 라인마다 아래로 뚫고, 가로 선 그리고, 옆으로 뚫고, 세로 선 그리기를 반복 */
    for (int i = 1; i < HEIGHT; i++) {
        /* 아래로 뚫을 곳을 결정해 뚫는다. */
        break_down();
        /* 가로 선을 그린다. */
        draw_horizontal();
        /* 옆으로 뚫을 곳을 결정해 뚫는다. */
        if (i != HEIGHT-1) {
            /* 중간 라인들의 경우, 어떤 곳을 뚫을지 랜덤으로 결정해 뚫는다. */
            break_side();
        }
        else {
            /* 마지막 라인의 경우, 다른 집합끼리 인접하면 무조건 뚫는다. */
            break_side_last();
        }
        /* 세로 선을 그린다. */
        draw_vertical();
    }
    
    /* Draw the bottom horizontal wall.
       It should be blocked. */
    draw_border();
    
    /* Close .maz file and deallocate memory. */
    finish_program();
    
    return 0;
}

