#include "tetris.h"

static struct sigaction act, oact;

int main(){
    int exit=0;

    initscr();
    noecho();
    keypad(stdscr, TRUE);

    srand((unsigned int)time(NULL));
    
    createRankList(); //week7

    while(!exit){
        clear();
        switch(menu()){
            case MENU_PLAY: play(); break;
            case MENU_RANK: rank(); break; //week7
            case MENU_EXIT: exit=1; break;
        default: break;
        }
    }

    endwin();
    system("clear");
    return 0;
}

void InitTetris(){
    int i,j;

    for(j=0;j<HEIGHT;j++)
        for(i=0;i<WIDTH;i++)
            field[j][i]=0;

    nextBlock[0]=rand()%7;
    nextBlock[1]=rand()%7;
    nextBlock[2]=rand()%7;
    blockRotate=0;
    blockY=-1;
    blockX=WIDTH/2-2;
    score=0;
    gameOver=0;
    timed_out=0;

    DrawOutline();
    DrawField();
    DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
    DrawNextBlock(nextBlock);
    PrintScore(score);
}

void DrawOutline(){
    int i,j;
    /* 블럭이 떨어지는 공간의 태두리를 그린다.*/
    DrawBox(0,0,HEIGHT,WIDTH);

    /* next block을 보여주는 공간의 태두리를 그린다.*/
    move(2,WIDTH+10);
    printw("NEXT BLOCK");
    DrawBox(3,WIDTH+10,4,8);
    DrawBox(9,WIDTH+10,4,8);

    /* score를 보여주는 공간의 태두리를 그린다.*/
    move(15,WIDTH+10);
    printw("SCORE");
    DrawBox(16,WIDTH+10,1,8);
}

int GetCommand(){
    int command;
    command = wgetch(stdscr);
    switch(command){
    case KEY_UP:
        break;
    case KEY_DOWN:
        break;
    case KEY_LEFT:
        break;
    case KEY_RIGHT:
        break;
    case ' ':    /* space key*/
        /*fall block*/
        break;
    case 'q':
    case 'Q':
        command = QUIT;
        break;
    default:
        command = NOTHING;
        break;
    }
    return command;
}

int ProcessCommand(int command){
    int ret=1;
    int drawFlag=0;
    switch(command){
    case QUIT:
        ret = QUIT;
        break;
    case KEY_UP:
        if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
            blockRotate=(blockRotate+1)%4;
        break;
    case KEY_DOWN:
        if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
            blockY++;
        break;
    case KEY_RIGHT:
        if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
            blockX++;
        break;
    case KEY_LEFT:
        if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
            blockX--;
        break;
    default:
        break;
    }
    if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
    return ret;
}

void DrawField(){
    int i,j;
    for(j=0;j<HEIGHT;j++){
        move(j+1,1);
        for(i=0;i<WIDTH;i++){
            if(field[j][i]==1){
                attron(A_REVERSE);
                printw(" ");
                attroff(A_REVERSE);
            }
            else printw(".");
        }
    }
}


void PrintScore(int score){
    move(17,WIDTH+11);
    printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
    int i, j;
    //1st next block
    for( i = 0; i < 4; i++ ){
        move(4+i,WIDTH+13);
        for( j = 0; j < 4; j++ ){
            if( block[nextBlock[1]][0][i][j] == 1 ){
                attron(A_REVERSE);
                printw(" ");
                attroff(A_REVERSE);
            }
            else printw(" ");
        }
    }
    //2nd next block
    for( i = 0; i < 4; i++ ){
        move(10+i,WIDTH+13);
        for( j = 0; j < 4; j++ ){
            if( block[nextBlock[2]][0][i][j] == 1 ){
                attron(A_REVERSE);
                printw(" ");
                attroff(A_REVERSE);
            }
            else printw(" ");
        }
    }
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
    int i,j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++){
            if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
                move(i+y+1,j+x+1);
                attron(A_REVERSE);
                printw("%c",tile);
                attroff(A_REVERSE);
            }
        }

    move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
    int i,j;
    move(y,x);
    addch(ACS_ULCORNER);
    for(i=0;i<width;i++)
        addch(ACS_HLINE);
    addch(ACS_URCORNER);
    for(j=0;j<height;j++){
        move(y+j+1,x);
        addch(ACS_VLINE);
        move(y+j+1,x+width+1);
        addch(ACS_VLINE);
    }
    move(y+j+1,x);
    addch(ACS_LLCORNER);
    for(i=0;i<width;i++)
        addch(ACS_HLINE);
    addch(ACS_LRCORNER);
}

void play(){
    int command;
    clear();
    act.sa_handler = BlockDown;
    sigaction(SIGALRM,&act,&oact);
    InitTetris();
    do{
        if(timed_out==0){
            alarm(1);
            timed_out=1;
        }

        command = GetCommand();
        if(ProcessCommand(command)==QUIT){
            alarm(0);
            DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
            move(HEIGHT/2,WIDTH/2-4);
            printw("Good-bye!!");
            refresh();
            getch();

            return;
        }
    }while(!gameOver);

    alarm(0);
    getch();
    DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
    move(HEIGHT/2,WIDTH/2-4);
    printw("GameOver!!");
    refresh();
    getch();
    newRank(score);
}

char menu(){
    printw("1. play\n");
    printw("2. rank\n");
    printw("3. recommended play\n");
    printw("4. exit\n");
    return wgetch(stdscr);
}

//************************************ week6 exercise

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX) {
    //블록이 명령에 따라 이동할 수 있는지 없는지 판단해 있다면 1, 없다면 0을 리턴한다.
    int i, j, x, y;
    
    for(i = 0; i < BLOCK_HEIGHT; i++) {
        for(j = 0; j < BLOCK_WIDTH; j++) {
            if(block[currentBlock][blockRotate][i][j] == 1) {
                y = blockY + i;
                x = blockX + j;
                
                //이동하려는 위치가 범위를 벗어난다면 0을 리턴한다.
                if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
                    return 0;
                if (f[y][x] == 1)
                    return 0;
            }
        }
    }
    return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
    //명령에 따라 이동한/회전한 블록을 다시 그린다. (이전 블록을 지우고, 새 블록을 그린다.)
    int pre_blockRotate = blockRotate;
    int pre_blockY = blockY;
    int pre_blockX = blockX;
    
    int i, j, x, y;
    int sh = 0;

    //Save the information of previous block.
    switch (command)
    {
        case KEY_UP:
            pre_blockRotate = (blockRotate + 3) % 4;
            break;
        case KEY_DOWN:
            pre_blockY -= 1;
            break;
        case KEY_LEFT:
            pre_blockX += 1;
            break;
        case KEY_RIGHT:
            pre_blockX -= 1;
    }
    
    //Find where the shadow is.
    while (CheckToMove(field, currentBlock, pre_blockRotate, blockY + sh, pre_blockX) == 1)
        sh++;
    sh--;
    
    //Erase the previous block and its shadow.
    for (i = 0; i < BLOCK_HEIGHT; i++) {
        for (j = 0; j < BLOCK_WIDTH; j++) {
            if (block[currentBlock][pre_blockRotate][i][j] == 1) {
                //erase the previous block
                y = i + pre_blockY + 1;
                x = j + pre_blockX + 1;
                move(y, x);
                printw(".");
                
                //erase the shadow
                y = i + pre_blockY + 1 + sh;
                x = j + pre_blockX + 1;
                move(y, x);
                printw(".");
            }
        }
    }
    
    //Draw the new block.
    DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);
}

void BlockDown(int sig){
    //현재 블록을 아래로 내릴 수 있다면 내린다.
    if (CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX)) {
        blockY++;
        DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
    }
    
    //현재 블록을 아래로 내릴 수 없는 경우.
    else {
        //블록이 시작부터 내릴 수 없다면, 필드에 블록을 놓을 공간이 없다는 의미이므로 게임오버이다.
        if (blockY == -1) gameOver = 1;
        
        //블록을 필드에 쌓는다.
        score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
        
        //빈 칸 없는 줄이 있는지 확인해서 삭제하고, 점수를 계산한다.
        score += DeleteLine(field);
        
        //현재 블록과 다음 블록(2개) 설정
        nextBlock[0] = nextBlock[1];
        nextBlock[1] = nextBlock[2];
        nextBlock[2] = rand() % 7;
        
        //블록의 위치 초기화
        blockY = -1;
        blockX = WIDTH/2 - 2;
        blockRotate = 0;
        
        //다음 블록을 디스플레이한다.
        DrawNextBlock(nextBlock);
        
        //점수를 디스플레이한다.
        PrintScore(score);
        
        DrawField();
    }
    //블록이 다 떨어졌으므로 0으로 초기화한다.
    timed_out = 0;
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
    //해당 좌표에 맞게 필드에 현재 블록을 쌓는다.
    int i, j, x, y;
    int touched = 0;
    
    for (i = 0; i < BLOCK_HEIGHT; i++) {
        for (j = 0; j < BLOCK_WIDTH; j++) {
            //블록의 모양대로 추가된 영역의 필드 값을 바꾼다.
            if (block[currentBlock][blockRotate][i][j] == 1) {
                y = blockY + i;
                x = blockX + j;
                f[y][x] = 1;
                //블록의 밑부분이 맞닿는다면 touched++
                if (y == HEIGHT-1 || field[y+1][x] == 1)
                    touched++;
            }
        }
    }
    return touched * 10;
}

int DeleteLine(char f[HEIGHT][WIDTH]){
    //빈 칸이 없는 줄을 찾아서 지우고, 지워진 줄 개수에 따라 점수를 계산해 리턴한다.

    //1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
    //2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
    int i, j, x, y;
    int count = 0;
    bool filled_flag;
    
    //필드를 위에서부터 아래로 탐색한다.
    for (i = 0; i < HEIGHT; i++) {
        //완전히 1로 채워진 줄을 찾는다.
        for (j = 0; j < WIDTH; j++) {
            if (!f[i][j]) {
                filled_flag = false;
                break;
            }
            else
                filled_flag = true;
        }
        
        //완전히 1로 채워진 줄인 경우
        if (filled_flag) {
            //점수 계산을 위해 지운 줄 개수를 센다.
            count++;
            
            //지운 줄 바로 위부터 가장 위까지, 필드를 내려준다.
            for (y = i; y >= 0; y--) {
                for (x = 0; x < WIDTH; x++) {
                    f[y][x] = f[y-1][x];
                }
            }
            for (x = 0; x < WIDTH; x++) { //가장 윗 줄은 새로 생겼으므로 0으로 셋팅한다.
                f[0][x] = 0;
            }
            //한 줄 지워주고 나머지 필드를 내려줬으므로 i--
            i--;
        }
    }
    
    return count * count * 100;
}

//************************************

//************************************ week 6 homework
void DrawShadow(int y, int x, int blockID,int blockRotate){
    int i = 0;
    //Find a location where the block can no longer go down
    while (CheckToMove(field, blockID, blockRotate, y + i, x) == 1)
        i++;
    //Cannot move to (y+i, x), so i--
    i--;
    DrawBlock(y + i, x, blockID, blockRotate, '/');
}

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate) {
    //Call DrawBlock(), DrawShadow() to display both block and shadow.
    DrawBlock(y, x, blockID, blockRotate, ' ');
    DrawShadow(y, x, blockID, blockRotate);
}
//************************************

//************************************ week7
void MakeList(Node** head, Node* newnode) {
    if (*head == NULL)
        *head = newnode;
    else {
        Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newnode;
    }
}

void createRankList(){
    FILE *fp;
    int i, j;
    
    fp = fopen("rank.txt", "r");
    if (fp == NULL) {
        fp = fopen("rank.txt", "w");
        fprintf(fp, "0\n");
        fclose(fp);
        return;
    }
    else {
        char name[NAMELEN];
        int score;
        Node* new_node;
        
        fscanf(fp, "%d", &score_number);

        for (i = 0; i < score_number; i++) {
            if (fscanf(fp, "%s %d", name, &score) != EOF) {
                new_node = createNode(name, score);
                MakeList(&head, new_node);
            }
            else {
                
            }
        }
        fclose(fp);
    }
}

Node* createNode(char* name, int score) {
    Node *temp = (Node*)malloc(sizeof(Node));
    
    strcpy(temp->name, name);
    temp->score = score;
    temp->next = NULL;
    
    return temp;
}

void rank(){
    int ch;
    clear();

    //print rank menu
    printw("1. list ranks from X to Y\n");
    printw("2. list ranks by a specific name\n");
    printw("3. delete a specific rank\n");

    ch = wgetch(stdscr);

    if (ch == '1') {
        rankXY();
    }

    else if ( ch == '2') { //week7 hw
        searchName();
    }

    else if ( ch == '3') { //week7 hw
        deleteRank();
    }
    
    getch();
}

void rankXY() {
    int X = 1, Y = score_number; //set default
    echo(); //turn on
    printw("X: ");
    scanw("%d", &X);
    printw("Y: ");
    scanw("%d", &Y);
    noecho(); //turn off

    printw("       name      |   score   \n");
    printw("-----------------------------\n");

    if (X > Y) { //range failure
        printw("\nsearch failure : no rank in the list");
        return;
    }

    Node* curr = head;
    int ranking = 1;
    while (curr != NULL) { //print the ranks from X to Y
            if (X <= ranking && ranking <= Y)
                printw(" %-16s | %d\n", curr->name, curr->score);
            else if (ranking > Y)
                break;
            curr = curr->next;
            ranking++;
    }
    return;
}

void searchName() {
    char str[NAMELEN+1]; //name to search
    int check = 0; //If the name is found in the list, check == 1.
    
    //Input a user name.
    echo(); //turn on
    printw("input the name: ");
    scanw("%s", str);
    noecho(); //turn off
    
    printw("       name      |   score   \n");
    printw("-----------------------------\n");
    
    //Search the user name.
    Node* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->name, str) == 0) {
            printw(" %-16s | %d\n", curr->name, curr->score);
            check = 1;
        }
        curr = curr->next;
    }
    
    //If matched name is not found
    if (check == 0) {
        printw("\nsearch failure: no information in the list\n");
    }
    
    return;
}

void deleteRank() {
    int num;
    int count = 0;
    
    //get input rank
    echo(); //turn on
    printw("input the rank: ");
    scanw("%d", &num);
    noecho(); //turn off
    
    //if num is out of range, print failure message
    if (num <= 0 || num > score_number) {
        printw("\nsearch failure: the rank not in the list\n");
        return;
    }
    
    //delete rank
    Node* curr = head;
    Node* temp;
    if (num == 1) { //head node deletion
        head = curr->next;
        free(curr);
    }
    else {
        count++;
        while (count < num - 1) { //curr := (node before the target node)
            count++;
            curr = curr->next;
        }
        temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
    }
    score_number--;
    printw("\nresult: the rank deleted\n");
    writeRankFile();
    return;
}

void writeRankFile(){
//    int sn;
    FILE* fp = fopen("rank.txt","w");
//    fscanf(fp, "%d\n", &sn);

//    if (sn == score_number) {
//        fclose(fp);
//        return;
//    }
//    else {
        fprintf(fp, "%d\n", score_number);
        Node* curr = head;
        while (curr != NULL) {
            fprintf(fp, "%s %d\n", curr->name, curr->score);
            curr = curr->next;
        }
        fclose(fp);
//    }
//    for ( i= 1; i < score_number+1 ; i++) {
//        free(a.rank_name[i]);
//    }
//    free(a.rank_name);
//    free(a.rank_score);
}

void newRank(int score){
    char str[NAMELEN+1];
    int i, j;
    clear();
    
    Node* new_node;

    echo(); //turn on
    printw("your name: ");
    scanw("%s", str);
    noecho(); //turn off

    new_node = createNode(str, score);

    if (head == NULL) { //empty list
        head = new_node;
    }
    else {
        Node* curr = head;
        Node* prev = NULL;

        while (curr != NULL) { //find the position where new > curr
            if (new_node->score < curr->score) {
                prev = curr;
                curr = curr->next;
            }
            else
                break;
        }
        if (prev == NULL) { //new_node should be the head
            head = new_node;
            new_node->next = curr;
        }
        else { //new_node should be inserted after curr
            new_node->next = prev->next;
            prev->next = new_node;
        }
    }
    
    score_number++;
    writeRankFile();
}
//************************************

//************************************ week8
void DrawRecommend(int y, int x, int blockID,int blockRotate){
    // user code
}

int recommend(RecNode *root){
    int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

    // user code

    return max;
}

void recommendedPlay(){
    // user code
}
//************************************
