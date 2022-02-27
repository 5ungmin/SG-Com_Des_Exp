#include "tetris.h"

static struct sigaction act, oact;

int main(){
    int exit=0;

    initscr();
    noecho();
    keypad(stdscr, TRUE);

    srand((unsigned int)time(NULL));

    while(!exit){
        clear();
        switch(menu()){
            case MENU_PLAY: play(); break;
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
    blockRotate=0;
    blockY=-1;
    blockX=WIDTH/2-2;
    score=0;
    gameOver=0;
    timed_out=0;

    DrawOutline();
    DrawField();
    DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
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

    /* score를 보여주는 공간의 태두리를 그린다.*/
    move(9,WIDTH+10);
    printw("SCORE");
    DrawBox(10,WIDTH+10,1,8);
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
    move(11,WIDTH+11);
    printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
    int i, j;
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

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX) {
    //Determine whether the block can move according to the command.
    //Return 1 if the block can move, 0 if not.
    int i, j, x, y;
    
    for(i = 0; i < BLOCK_HEIGHT; i++) {
        for(j = 0; j < BLOCK_WIDTH; j++) {
            //According to the shape of the block, the x-coordinate and y-coordinate of the position to be moved are obtained.
            if(block[currentBlock][blockRotate][i][j] == 1) {
                y = blockY + i;
                x = blockX + j;
                
                //If the position to be moved is out of range, return zero.
                if (y < 0 || y >= HEIGHT || x < 0 || x >= WIDTH)
                    return 0;
                //If there is already a block, return zero.
                if (f[y][x] == 1)
                    return 0;
            }
        }
    }
    
    return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
    //Redraw the moved or rotated block according to the command. (Erase the old block and draw a new block.)
    
    int oldRotate = blockRotate;
    int oldY = blockY;
    int oldX = blockX;
    
    int i, j;

    //Save the information of the old block.
    switch (command)
    {
        case KEY_UP:
            oldRotate = (blockRotate + 3) % 4;
            break;
        case KEY_DOWN:
            oldY -= 1;
            break;
        case KEY_LEFT:
            oldX += 1;
            break;
        case KEY_RIGHT:
            oldX -= 1;
            break;
    }

    //Erase the old block.
    for (i = 0; i < BLOCK_HEIGHT; i++) {
        for (j = 0; j < BLOCK_WIDTH; j++) {
            //according to the shape of the block, erase the block at the previous location.
            if (block[currentBlock][oldRotate][i][j] == 1) {
                //move cursor to (i + oldY + 1, j + oldX + 1) and print "."
                move(oldY + i + 1, oldX + j + 1);
                printw(".");
            }
        }
    }
    
    //Draw the new block.
    DrawBlock(blockY, blockX, currentBlock, blockRotate, ' ');
}

void BlockDown(int sig){
    //If the block can go down, then move the block.
    if (CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX)) {
        blockY++;
        DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
    }
    
    //If the block can not go down.
    else {
        //If the block cannot go down at all, it means that there is no space to place the block in the field, so game over.
        if (blockY == -1) gameOver = 1;

        //Stack the block in the field.
        AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
        
        //Check if there is a full line, delete it, and calculate the score.
        score += DeleteLine(field);
        
        //Set the current block and the next block.
        nextBlock[0] = nextBlock[1];
        nextBlock[1] = rand() % 7;
        
        //Initialize the position of the block.
        blockY = -1;
        blockX = WIDTH/2 - 2;
        blockRotate = 0;
        
        //Display the next block.
        DrawNextBlock(nextBlock);
        
        //Display the score.
        PrintScore(score);
        
        DrawField();
    }
    
    //Initialize timed_out to zero.
    timed_out = 0;
}

void AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
    //Stack the current block in the field according to the corresponding coordinates.
    
    int i, j, x, y;
    
    for (i = 0; i < BLOCK_HEIGHT; i++) {
        for (j = 0; j < BLOCK_WIDTH; j++) {
            //According to the shape of the block, change the field value of the added area.
            if (block[currentBlock][blockRotate][i][j] == 1) {
                y = blockY + i;
                x = blockX + j;
                f[y][x] = 1;
            }
        }
    }
}

int DeleteLine(char f[HEIGHT][WIDTH]){
    //Find and erase the full line, calculate the score according to the number of erased lines.
    //Return: score

    //1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
    //2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
    int i, j, x, y;
    int count = 0;
    bool filled_flag;
    
    //Scan the field from top to bottom.
    for (i = 0; i < HEIGHT; i++) {
        //Find a line that is completely filled with 1.
        for (j = 0; j < WIDTH; j++) {
            //If there's zero (meaning it's not full) set the flag to false.
            if (f[i][j] == 0) {
                filled_flag = false;
                break;
            }
            //If there's no zero (meaning it is full) set the flag to true.
            else
                filled_flag = true;
        }
        
        //If the line is full
        if (filled_flag) {
            //Increase the number of lines erased to calculate the score.
            count++;
            
            //Just above the erased line to the top, lower the field.
            for (y = i; y >= 0; y--) {
                for (x = 0; x < WIDTH; x++) {
                    f[y][x] = f[y-1][x];
                }
            }
            for (x = 0; x < WIDTH; x++) { //The top row is new, so set to zero.
                f[0][x] = 0;
            }
            //Since one line is erased and the rest of the field is lowered, i--
            i--;
        }
    }
    
    //return the score
    return count * count * 100;
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID,int blockRotate){
    // user code
}

void createRankList(){
    // user code
}

void rank(){
    // user code
}

void writeRankFile(){
    // user code
}

void newRank(int score){
    // user code
}

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
