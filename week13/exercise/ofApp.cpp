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
    
    QUITbutton.set(190, 10, 50, 20);
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
            //drawBFS();
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
        
        /* Deallocation. */
        freeMemory();
        
        /* Finish program. */
        _Exit(0);
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
    if (FILEbutton.inside(x, y)) {
        FILEbuttonClicked = 1;
        isDFS = isBFS = 0;
    }
    
    /* DFS button clicked */
    if (DFSbutton.inside(x, y)) {
        isBFS = 0; //turn off BFS
        isDFS = !isDFS; //toggle DFS
        if (isDFS) DFS();
    }
    
    /* BFS button clicked */
    if (BFSbutton.inside(x, y)) {
        isDFS = 0; //turn off DFS
        isBFS = !isBFS; //toggle BFS
        if (isBFS) BFS();
    }
    
    /* QUIT button clicked */
    if (QUITbutton.inside(x, y)) {
        /* Reset flags. */
        isOpen = 0;
        isDFS = 0;
        isBFS = 0;
        
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

        processImage();
        
        /* Save coordinate information */
        Line tmp;
   
        for (i = 0; i < imageHEIGHT; i++) {
            for (j = 0; j < imageWIDTH; j++) {
                switch (image[i][j])
                {
                    case '|':
                        tmp.startX = j + 0.5;
                        tmp.startY = i - 0.5;
                        tmp.endX = j + 0.5;
                        tmp.endY = i + 1.5;
                        walls.push_back(tmp);
                        break;
                    case '-':
                        tmp.startX = j - 0.5;
                        tmp.startY = i + 0.5;
                        tmp.endX = j + 1.5;
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
    
    return false;
}

//--------------------------------------------------------------
void ofApp::getSearchedPath(Vertex* curr){
    
    Line tmp;
    
    switch (curr->parent) {
        case UP:
            tmp.startX = 40 * curr->x + 30;
            tmp.startY = 40 * (curr->y - 1) + 80;
            tmp.endX = 40 * curr->x + 30;
            tmp.endY = 40 * curr->y + 80;
            searched_path.push_back(tmp);
            break;
        case DOWN:
            tmp.startX = 40 * curr->x + 30;
            tmp.startY = 40 * (curr->y + 1) + 80;
            tmp.endX = 40 * curr->x + 30;
            tmp.endY = 40 * curr->y + 80;
            searched_path.push_back(tmp);
            break;
        case LEFT:
            tmp.startX = 40 * (curr->x - 1) + 30;
            tmp.startY = 40 * curr->y + 80;
            tmp.endX = 40 * curr->x + 30;
            tmp.endY = 40 * curr->y + 80;
            searched_path.push_back(tmp);
            break;
        case RIGHT:
            tmp.startX = 40 * (curr->x + 1) + 30;
            tmp.startY = 40 * curr->y + 80;
            tmp.endX = 40 * curr->x + 30;
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
                tmp.startX = 40 * curr->x + 30;
                tmp.startY = 40 * curr->y + 80;
                tmp.endX = 40 * curr->x + 30;
                tmp.endY = 40 * (curr->y - 1) + 80;
                shortest_path.push_back(tmp);
                i--;
                break;
                
            case DOWN:
                tmp.startX = 40 * curr->x + 30;
                tmp.startY = 40 * curr->y + 80;
                tmp.endX = 40 * curr->x + 30;
                tmp.endY = 40 * (curr->y + 1) + 80;
                shortest_path.push_back(tmp);
                i++;
                break;
                
            case LEFT:
                tmp.startX = 40 * curr->x + 30;
                tmp.startY = 40 * curr->y + 80;
                tmp.endX = 40 * (curr->x - 1) + 30;
                tmp.endY = 40 * curr->y + 80;
                shortest_path.push_back(tmp);
                j--;
                break;
                
            case RIGHT:
                tmp.startX = 40 * curr->x + 30;
                tmp.startY = 40 * curr->y + 80;
                tmp.endX = 40 * (curr->x + 1) + 30;
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
    
    /* QUIT button */
    ofSetColor(ofColor::beige);
    ofDrawRectangle(QUITbutton);
    
    /* Menu Text */
    ofSetColor(ofColor::black);
    ofDrawBitmapString("FILE", 20, 25);
    ofDrawBitmapString("DFS", 80, 25);
    ofDrawBitmapString("BFS", 140, 25);
    ofDrawBitmapString("QUIT", 200, 25);
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Click [QUIT] or press 'q' to exit.", 260, 25);
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
    
}
