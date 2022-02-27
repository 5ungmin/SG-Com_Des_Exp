#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /* Set the app name on the title bar. */
    ofSetWindowTitle("Maze Example");
    
    ofSetFrameRate(15);
    ofBackground(255, 255, 255);
    
    /* Reset flag */
    isOpen = 0;
    
    ofSetLineWidth(5);
    
    /* Set button position and reset flag. */
    FILEbutton.set(10, 10, 50, 20);
    FILEbuttonClicked = 0;
    
    DFSbutton.set(70, 10, 50, 20);
    isDFS = 0;
    
    BFSbutton.set(130, 10, 50, 20);
    isDFS = 0;
    
    PLAYbutton.set(190, 10, 50, 20);
    isPLAY = 0;
    
    QUITbutton.set(250, 10, 50, 20);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(100);
    ofSetLineWidth(5);
    
    /* Draw shape for menu bar */
    ofDrawRectangle(0, 0, 1024, 40);
    
    /* Draw maze. */
    if (isOpen) {
        ofSetColor(100);
        for(int i = 0; i < walls.size(); i++) {
            ofDrawLine(20 * walls[i].startX, 50 + 20 * walls[i].startY, 20 * walls[i].endX, 50 + 20 * walls[i].endY);
        }
        
        /* Starting point */
        ofRectangle startRect;
        startRect.x = 22.5;
        startRect.y = 62.5;
        startRect.width = 35;
        startRect.height = 35;
        ofSetColor(ofColor::lightPink);
        ofDrawRectangle(startRect);
        
        /* End point */
        ofRectangle endRect;
        endRect.x = 40 * mazeWIDTH - 17.5;
        endRect.y = 40 * mazeHEIGHT + 22.5;
        endRect.width = 35;
        endRect.height = 35;
        ofSetColor(ofColor::lightGreen);
        ofDrawRectangle(endRect);
    }
    
    /* DFS */
    if (isDFS) {
        if (isOpen) {
            ofSetLineWidth(5);
            drawDFS();
        }
        else
            cout << "You must open file first" << endl;
    }
    
    /* BFS */
    if (isBFS) {
        if (isOpen) {
            ofSetLineWidth(5);
            drawBFS();
        }
        else
            cout << "You must open file first" << endl;
    }
    
    /* PLAY */
    if (isPLAY) {
        if (isOpen) {
            drawPLAY(); //Draw the path as the user progressed.
        }
        else
            cout << "You must open file first" << endl;
    }
    
    /* Buttons and Message */
    drawMenu();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'q') {
        /* Reset flags. */
        isOpen = 0;
        isDFS = 0;
        isBFS = 0;
        isPLAY = 0;
        
        /* Deallocation. */
        freeMemory();
        
        /* Finish program. */
        _Exit(0);
    }
    if (key == OF_KEY_RIGHT) {
        if (isPLAY && !reached) {
            if (maze[currY][currX].right) {
                Direction tmp = RIGHT;
                PLAY(tmp);
            }
        }
    }
    if (key == OF_KEY_LEFT) {
        if (isPLAY && !reached) {
            if (maze[currY][currX].left) {
                Direction tmp = LEFT;
                PLAY(tmp);
            }
        }
    }
    if (key == OF_KEY_UP) {
        if (isPLAY && !reached) {
            if (maze[currY][currX].up) {
                Direction tmp = UP;
                PLAY(tmp);
            }
        }
    }
    if (key == OF_KEY_DOWN) {
        if (isPLAY && !reached) {
            if (maze[currY][currX].down) {
                Direction tmp = DOWN;
                PLAY(tmp);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    /* FILE button clicked */
    if (FILEbutton.inside(x, y)) {
        FILEbuttonClicked = 1;
        isDFS = isBFS = isPLAY = 0;
        reached = false;
    }
    
    /* DFS button clicked */
    if (DFSbutton.inside(x, y)) {
        if (isOpen) {
            if (isBFS) {
                cout << "Please turn off BFS first." << endl;
            }
            else if (isPLAY) {
                cout << "Please turn off PLAY first." << endl;
            }
            else {
                isDFS = !isDFS; //toggle DFS
                if (isDFS) DFS();
            }
        }
        else
            cout << "You must open file first" << endl;
    }
    
    /* BFS button clicked */
    if (BFSbutton.inside(x, y)) {
        if (isOpen) {
            if (isDFS) {
                cout << "Please turn off DFS first." << endl;
            }
            else if (isPLAY) {
                cout << "Please turn off PLAY first." << endl;
            }
            else {
                isBFS = !isBFS; //toggle BFS
                if (isBFS) BFS();
            }
        }
        else
            cout << "You must open file first" << endl;
    }
    
    /* PLAY button clicked */
    if (PLAYbutton.inside(x, y)) {
        if (isOpen) {
            if (isDFS || isBFS) {
                cout << "Please turn off DFS/BFS first." << endl;
            }
            else {
                isPLAY = !isPLAY; //toggle PLAY
                if (isPLAY) {
                    /* Initialize status */
                    reached = false;
                    currX = currY = 0;
                    
                    /* Initialize path */
                    play_path.clear();
                    
                    /* Mark all nodes as not visited. */
                    int i, j;
                    for (i = 0; i < mazeHEIGHT; i++) {
                        for (j = 0; j < mazeWIDTH; j++) {
                            maze[i][j].visited = false;
                        }
                    }
                    
                    /* Starting point is always visited.  */
                    maze[0][0].visited = true;
                    
                    /* timer start */
                    ofResetElapsedTimeCounter();
                }
            }
        }
        else
            cout << "You must open file first" << endl;
    }
    
    /* QUIT button clicked */
    if (QUITbutton.inside(x, y)) {
        /* Reset flags. */
        isOpen = 0;
        isDFS = 0;
        isBFS = 0;
        isPLAY = 0;
        reached = false;
        
        /* Deallocation. */
        freeMemory();
        
        /* Finish program. */
        _Exit(0);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (FILEbutton.inside(x, y)) {
        /* Deallocate prior maze memory. */
        freeMemory();
        
        /* Open the Open File Dialog */
        ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only maz for Maze");
        
        /* Check whether the user opened a file */
        if (openFileResult.bSuccess) {
            ofLogVerbose("User selected a file");
            
            /* We have a file, so let's check it and process it. */
            if (readFile(openFileResult)) isOpen = 1;
            else isOpen = 0;
        }
        
        FILEbuttonClicked = 0;
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::PLAY(Direction way){
    Line tmp;
    
    switch(way) {
        case UP:
            /* 돌아가는 길이라면 경로를 지운다. */
            if (maze[currY-1][currX].visited) {
                play_path.pop_back();
                maze[currY][currX].visited = false;
            }
            /* 새로운 길이라면 경로를 추가한다. */
            else {
                tmp.startX = 40 * currX + 40;
                tmp.startY = 40 * currY + 80;
                tmp.endX = 40 * currX + 40;
                tmp.endY = 40 * (currY - 1) + 80;
                play_path.push_back(tmp);
                maze[currY-1][currX].visited = true;
            }
            currY--;
            break;
            
        case DOWN:
            /* 돌아가는 길이라면 경로를 지운다. */
            if (maze[currY+1][currX].visited) {
                play_path.pop_back();
                maze[currY][currX].visited = false;
            }
            /* 새로운 길이라면 경로를 추가한다. */
            else {
                tmp.startX = 40 * currX + 40;
                tmp.startY = 40 * currY + 80;
                tmp.endX = 40 * currX + 40;
                tmp.endY = 40 * (currY + 1) + 80;
                play_path.push_back(tmp);
                maze[currY+1][currX].visited = true;
            }
            currY++;
            break;
            
        case LEFT:
            /* 돌아가는 길이라면 경로를 지운다. */
            if (maze[currY][currX-1].visited) {
                play_path.pop_back();
                maze[currY][currX].visited = false;
            }
            /* 새로운 길이라면 경로를 추가한다. */
            else {
                tmp.startX = 40 * currX + 40;
                tmp.startY = 40 * currY + 80;
                tmp.endX = 40 * (currX - 1) + 40;
                tmp.endY = 40 * currY + 80;
                play_path.push_back(tmp);
                maze[currY][currX-1].visited = true;
            }
            currX--;
            break;
            
        case RIGHT:
            /* 돌아가는 길이라면 경로를 지운다. */
            if (maze[currY][currX+1].visited) {
                play_path.pop_back();
                maze[currY][currX].visited = false;
            }
            /* 새로운 길이라면 경로를 추가한다. */
            else {
                tmp.startX = 40 * currX + 40;
                tmp.startY = 40 * currY + 80;
                tmp.endX = 40 * (currX + 1) + 40;
                tmp.endY = 40 * currY + 80;
                play_path.push_back(tmp);
                maze[currY][currX+1].visited = true;
            }
            currX++;
            break;
            
        default:
            ;
    }
    
    /* reached end point */
    if (currX == (mazeWIDTH-1) && currY == (mazeHEIGHT-1)) {
        reached = true;
    }
}

//--------------------------------------------------------------
void ofApp::drawPLAY(){
    if (reached) {
        ofSetColor(ofColor::lightGreen);
        ofDrawBitmapString(to_string(time), 320, 25);
    }
    else {
        time = ofGetElapsedTimef();
        ofSetColor(ofColor::lightGreen);
        ofDrawBitmapString(to_string(time), 320, 25);
    }
    
    ofSetColor(ofColor::black);
    for(int i = 0; i < play_path.size(); i++) {
        ofDrawLine(play_path[i].startX, play_path[i].startY, play_path[i].endX, play_path[i].endY);
    }
}

//--------------------------------------------------------------
bool ofApp::readFile(ofFileDialogResult openFileResult){
    //string fileName = openFileResult.getName();
    string filePath = openFileResult.getPath();
    size_t pos = filePath.find_last_of(".");
    
    if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {
        /* Open */
        ifstream input_file;
        input_file.open(filePath);
        
        if (!input_file.is_open()) {
            cout << "Failed to open target file." << endl;
            return false;
        }
        
        cout << "We found the target file." << endl;
        
        /* Read file line by line. */
        string line;
        string::iterator iter;
        int i = 0;
        int j;

        /* Save maze */
        while (getline(input_file, line)) {
            image.push_back(vector<char>());
            for (iter = line.begin(); iter != line.end(); iter++) {
                image[i].push_back(*iter);
            }
            i++;
        }
        
        /* Save WIDTH */
        imageWIDTH = image[0].size();
        
        /* Save HEIGHT */
        imageHEIGHT = i;
                
        /* Close */
        input_file.close();
        
        /* Save maze size */
        mazeWIDTH = (imageWIDTH - 1) / 2;
        mazeHEIGHT = (imageHEIGHT - 1) / 2;

        /* Save maze information */
        processImage();
        
        /* Save coordinate information */
        Line tmp;
   
        for (i = 0; i < imageHEIGHT; i++) {
            for (j = 0; j < imageWIDTH; j++) {
                switch (image[i][j])
                {
                    case '|':
                        tmp.startX = j + 1;
                        tmp.startY = i - 0.5;
                        tmp.endX = j + 1;
                        tmp.endY = i + 1.5;
                        walls.push_back(tmp);
                        break;
                    case '-':
                        tmp.startX = j;
                        tmp.startY = i + 0.5;
                        tmp.endX = j + 2;
                        tmp.endY = i + 0.5;
                        walls.push_back(tmp);
                        break;
                    default:
                        ;
                }
            }
        }
        
        return true;
    }
    else {
        cout << "Needs a '.maz' extension." << endl;
        return false;
    }
        
}

//--------------------------------------------------------------
bool ofApp::DFS(){
    /* Initialize path */
    searched_path.clear();
    shortest_path.clear();
    
    /* 모든 노드를 방문하지 않은 노드로 표시 */
    int i, j;
    for (i = 0; i < mazeHEIGHT; i++) {
        for (j = 0; j < mazeWIDTH; j++) {
            maze[i][j].visited = false;
            maze[i][j].parent = NONE;
        }
    }
    
    Vertex* curr;
    i = 0; j = 0;
    curr = &maze[i][j];
    curr->visited = true; //start_node.visited = 1
    DFS_stack.push(curr); //stack.append(start_node)
    
    bool has_unvisited;
    /* while (stack is not empty) */
    while (!DFS_stack.empty()) {
        
        curr = DFS_stack.top();
        
        getSearchedPath(curr);
        
        /* Destination reached */
        if ((curr->x == mazeWIDTH - 1) && (curr->y == mazeHEIGHT - 1)) {
            
//            cout << "DFS success!!!" << endl;
            
            getShortestPath();
            
            return true;
        }
        
        //if (S.top has an unvisited adjacent node)
        has_unvisited = false;
        i = curr->y; j = curr->x;
        if (curr->up && !maze[i-1][j].visited) {
            maze[i-1][j].visited = true;
            maze[i-1][j].parent = DOWN;
            DFS_stack.push(&maze[i-1][j]);
            has_unvisited = true;
        }
        if (curr->down && !maze[i+1][j].visited) {
            maze[i+1][j].visited = true;
            maze[i+1][j].parent = UP;
            DFS_stack.push(&maze[i+1][j]);
            has_unvisited = true;
        }
        if (curr->left && !maze[i][j-1].visited) {
            maze[i][j-1].visited = true;
            maze[i][j-1].parent = RIGHT;
            DFS_stack.push(&maze[i][j-1]);
            has_unvisited = true;
        }
        if (curr->right && !maze[i][j+1].visited) {
            maze[i][j+1].visited = true;
            maze[i][j+1].parent = LEFT;
            DFS_stack.push(&maze[i][j+1]);
            has_unvisited = true;
        }
        
        /* 더 이상 갈 곳이 없음 */
        if (!has_unvisited) {
            DFS_stack.pop();
        }
        
    }
    
    return false;
}

//--------------------------------------------------------------
bool ofApp::BFS(){
    /* Initialize path */
    searched_path.clear();
    shortest_path.clear();
    
    /* 모든 노드를 방문하지 않은 노드로 표시 */
    int i, j;
    for (i = 0; i < mazeHEIGHT; i++) {
        for (j = 0; j < mazeWIDTH; j++) {
            maze[i][j].visited = false;
            maze[i][j].parent = NONE;
        }
    }
    
    Vertex* curr;
    i = 0; j = 0;
    curr = &maze[i][j];
    curr->visited = true; //start_node.visited = True
    BFS_queue.push(curr); //queue.append(start_node)
    
    /* while (queue is not empty) */
    while (!BFS_queue.empty()) {
        
        //curr_node = queue.popleft()
        curr = BFS_queue.front();
        getSearchedPath(curr);
        BFS_queue.pop();
        
        /* Destination reached */
        if ((curr->x == mazeWIDTH - 1) && (curr->y == mazeHEIGHT - 1)) {
            
//            cout << "BFS success!!!" << endl;
            
            getShortestPath();
            
            return true;
        }
        
        i = curr->y; j = curr->x;
        
        if (curr->up && !maze[i-1][j].visited) {
            maze[i-1][j].visited = true;
            maze[i-1][j].parent = DOWN;
            BFS_queue.push(&maze[i-1][j]);
        }
        if (curr->down && !maze[i+1][j].visited) {
            maze[i+1][j].visited = true;
            maze[i+1][j].parent = UP;
            BFS_queue.push(&maze[i+1][j]);
        }
        if (curr->left && !maze[i][j-1].visited) {
            maze[i][j-1].visited = true;
            maze[i][j-1].parent = RIGHT;
            BFS_queue.push(&maze[i][j-1]);
        }
        if (curr->right && !maze[i][j+1].visited) {
            maze[i][j+1].visited = true;
            maze[i][j+1].parent = LEFT;
            BFS_queue.push(&maze[i][j+1]);
        }
        
        
        
    }
    
    return false;
}

//--------------------------------------------------------------
void ofApp::getSearchedPath(Vertex* curr){
    
    Line tmp;
    
    switch (curr->parent) {
        case UP:
            tmp.startX = 40 * curr->x + 40;
            tmp.startY = 40 * (curr->y - 1) + 80;
            tmp.endX = 40 * curr->x + 40;
            tmp.endY = 40 * curr->y + 80;
            searched_path.push_back(tmp);
            break;
        case DOWN:
            tmp.startX = 40 * curr->x + 40;
            tmp.startY = 40 * (curr->y + 1) + 80;
            tmp.endX = 40 * curr->x + 40;
            tmp.endY = 40 * curr->y + 80;
            searched_path.push_back(tmp);
            break;
        case LEFT:
            tmp.startX = 40 * (curr->x - 1) + 40;
            tmp.startY = 40 * curr->y + 80;
            tmp.endX = 40 * curr->x + 40;
            tmp.endY = 40 * curr->y + 80;
            searched_path.push_back(tmp);
            break;
        case RIGHT:
            tmp.startX = 40 * (curr->x + 1) + 40;
            tmp.startY = 40 * curr->y + 80;
            tmp.endX = 40 * curr->x + 40;
            tmp.endY = 40 * curr->y + 80;
            searched_path.push_back(tmp);
            break;
        default:
            ;
    }
    
}

//--------------------------------------------------------------
void ofApp::getShortestPath(){
    
    Vertex* curr;
    Line tmp;
    int i = mazeHEIGHT-1;
    int j = mazeWIDTH-1;
    
    while (!(i == 0 && j == 0)) {
        curr = &maze[i][j];
        
        /* 부모 노드로 올라가기 */
        switch(curr->parent) {
            case UP:
                tmp.startX = 40 * curr->x + 40;
                tmp.startY = 40 * curr->y + 80;
                tmp.endX = 40 * curr->x + 40;
                tmp.endY = 40 * (curr->y - 1) + 80;
                shortest_path.push_back(tmp);
                i--;
                break;
                
            case DOWN:
                tmp.startX = 40 * curr->x + 40;
                tmp.startY = 40 * curr->y + 80;
                tmp.endX = 40 * curr->x + 40;
                tmp.endY = 40 * (curr->y + 1) + 80;
                shortest_path.push_back(tmp);
                i++;
                break;
                
            case LEFT:
                tmp.startX = 40 * curr->x + 40;
                tmp.startY = 40 * curr->y + 80;
                tmp.endX = 40 * (curr->x - 1) + 40;
                tmp.endY = 40 * curr->y + 80;
                shortest_path.push_back(tmp);
                j--;
                break;
                
            case RIGHT:
                tmp.startX = 40 * curr->x + 40;
                tmp.startY = 40 * curr->y + 80;
                tmp.endX = 40 * (curr->x + 1) + 40;
                tmp.endY = 40 * curr->y + 80;
                shortest_path.push_back(tmp);
                j++;
                break;
                
            default:
                ;
        }
    }
    
}


//--------------------------------------------------------------
void ofApp::processImage(){
    int i, j, x, y;
    Vertex tmp;
    
    /* Initialize maze */
    for (y = 0; y < mazeHEIGHT; y++) {
        maze.push_back(vector<Vertex>());
        for (x = 0; x < mazeWIDTH; x++) {
            tmp.visited = false;
            tmp.x = x;
            tmp.y = y;
            tmp.parent = NONE;
            maze[y].push_back(tmp);
        }
    }
    
    /* From image, make maze. */
    /* 홀수 인덱스마다 칸이 있음 */
    for (i = 1; i < imageHEIGHT; i += 2) {
        y = (i - 1) / 2;
        for (j = 1; j < imageWIDTH; j += 2) {
            x = (j - 1) / 2;
            /* up */
            maze[y][x].up = (image[i-1][j] == ' ') ? true : false;
            /* down */
            maze[y][x].down = (image[i+1][j] == ' ') ? true : false;
            /* left */
            maze[y][x].left = (image[i][j-1] == ' ') ? true : false;
            /* right */
            maze[y][x].right = (image[i][j+1] == ' ') ? true : false;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::drawDFS(){
    int i;
    
    /* searched path */
    ofSetColor(ofColor::red);
    for (i = 0; i < searched_path.size(); i++)
        ofDrawLine(searched_path[i].startX, searched_path[i].startY, searched_path[i].endX, searched_path[i].endY);
    
    /* shortest path */
    ofSetColor(ofColor::green);
    for (i = 0; i < shortest_path.size(); i++)
        ofDrawLine(shortest_path[i].startX, shortest_path[i].startY, shortest_path[i].endX, shortest_path[i].endY);
}

//--------------------------------------------------------------
void ofApp::drawBFS(){
    int i;
    
    /* searched path */
    ofSetColor(ofColor::red);
    for (i = 0; i < searched_path.size(); i++)
        ofDrawLine(searched_path[i].startX, searched_path[i].startY, searched_path[i].endX, searched_path[i].endY);
    
    /* shortest path */
    ofSetColor(ofColor::green);
    for (i = 0; i < shortest_path.size(); i++)
        ofDrawLine(shortest_path[i].startX, shortest_path[i].startY, shortest_path[i].endX, shortest_path[i].endY);
}

//--------------------------------------------------------------
void ofApp::drawMenu(){
    /* FILE button */
    if (FILEbuttonClicked)
        ofSetColor(ofColor::lightBlue);
    else
        ofSetColor(ofColor::beige);
    ofDrawRectangle(FILEbutton);
    
    /* DFS button */
    if (isDFS)
        ofSetColor(ofColor::lightBlue);
    else
        ofSetColor(ofColor::beige);
    ofDrawRectangle(DFSbutton);
    
    /* BFS button */
    if (isBFS)
        ofSetColor(ofColor::lightBlue);
    else
        ofSetColor(ofColor::beige);
    ofDrawRectangle(BFSbutton);
    
    /* PLAY button */
    if (isPLAY)
        ofSetColor(ofColor::lightBlue);
    else
        ofSetColor(ofColor::beige);
    ofDrawRectangle(PLAYbutton);
    
    /* QUIT button */
    ofSetColor(ofColor::beige);
    ofDrawRectangle(QUITbutton);
    
    /* Menu Text */
    ofSetColor(ofColor::black);
    ofDrawBitmapString("FILE", 20, 25);
    ofDrawBitmapString("DFS", 80, 25);
    ofDrawBitmapString("BFS", 140, 25);
    ofDrawBitmapString("PLAY", 200, 25);
    ofDrawBitmapString("QUIT", 260, 25);
    ofSetColor(ofColor::white);
    //ofDrawBitmapString("Click [QUIT] or press 'q' to exit.", 260, 25);
}

//--------------------------------------------------------------
void ofApp::freeMemory(){
    
    /* Deallocation */
    int i;
    
    /* image */
    for (i = 0; i < imageHEIGHT; i++) {
        image[i].clear();
    }
    for (i = 0; i < imageHEIGHT; i++) {
        vector<char>().swap(image[i]);
    }
    image.clear();
    vector<vector<char>>().swap(image);
    
    /* maze */
    for (i = 0; i < mazeHEIGHT; i++) {
        maze[i].clear();
    }
    for (i = 0; i < mazeHEIGHT; i++) {
        vector<Vertex>().swap(maze[i]);
    }
    maze.clear();
    vector<vector<Vertex>>().swap(maze);
    
    /* walls */
    walls.clear();
    vector<Line>().swap(walls);
    
    /* DFS */
    while (!DFS_stack.empty())
        DFS_stack.pop();
    
    /* BFS */
    while (!BFS_queue.empty())
        BFS_queue.pop();
    
    /* path */
    searched_path.clear();
    vector<Line>().swap(searched_path);
    shortest_path.clear();
    vector<Line>().swap(shortest_path);
    play_path.clear();
    vector<Line>().swap(play_path);
}
