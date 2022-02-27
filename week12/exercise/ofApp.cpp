#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /* Set the app name on the title bar. */
    ofSetWindowTitle("Maze Example");
    
    ofSetFrameRate(15);
    ofBackground(255, 255, 255);
    
    /* Reset flags. */
    isOpen = 0;
//    isDFS = 0;
    
    ofSetLineWidth(5);
    
    FILEbutton.set(10, 10, 50, 20);
    FILEbuttonClicked = 0;
    
    DFSbutton.set(70, 10, 50, 20);
    isDFS = 0;
    
    BFSbutton.set(130, 10, 50, 20);
    isDFS = 0;
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
//    if (isDFS) {
//        if (isOpen) {
//            ofSetColor(200);
//            ofSetLineWidth(5);
//            dfsDraw();
//        }
//        else
//            cout << "You must open file first" << endl;
//    }
    
    /* BFS */
//    if (isBFS) {
//        if (isOpen) {
//            ofSetColor(200);
//            ofSetLineWidth(5);
//            bfsDraw();
//        }
//        else
//            cout << "You must open file first" << endl;
//    }
    
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
    
    /* Menu Text */
    ofSetColor(ofColor::black);
    ofDrawBitmapString("FILE", 20, 25);
    ofDrawBitmapString("DFS", 80, 25);
    ofDrawBitmapString("BFS", 140, 25);
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Press 'q' to exit.", 200, 25);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'q') {
        /* Reset flags. */
        isOpen = 0;
        isDFS = 0;
        
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
//        cout << "[DEBUG] FILEbuttonClicked = " << FILEbuttonClicked << endl;
    }
    
    /* DFS button clicked */
    if (DFSbutton.inside(x, y)) {
        isDFS = !isDFS;
        if (isBFS) isBFS = 0;
//        cout << "[DEBUG] isDFS = " << isDFS << endl;
//        cout << "[DEBUG] isBFS = " << isBFS << endl;
    }
    
    /* BFS button clicked */
    if (BFSbutton.inside(x, y)) {
        isBFS = !isBFS;
        if (isDFS) isDFS = 0;
//        cout << "[DEBUG] isDFS = " << isDFS << endl;
//        cout << "[DEBUG] isBFS = " << isBFS << endl;
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
//        cout << "[DEBUG] FILEbuttonClicked = " << FILEbuttonClicked << endl;
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
            maze.push_back(vector<char>());
            for (iter = line.begin(); iter != line.end(); iter++) {
                maze[i].push_back(*iter);
            }
            i++;
        }
        
        /* Save WIDTH */
        imageWIDTH = maze[0].size();
        
        /* Save HEIGHT */
        imageHEIGHT = i; //i starts from 0
        
//        cout << "[DEBUG] imageWIDTH = " << imageWIDTH << endl;
//        cout << "[DEBUG] imageHEIGHT = " << imageHEIGHT << endl;
        
        /* Close */
        input_file.close();
        
        /* Save maze size */
        mazeWIDTH = (imageWIDTH - 1) / 2;
        mazeHEIGHT = (imageHEIGHT - 1) / 2;
//        cout << "[DEBUG] mazeWIDTH = " << mazeWIDTH << endl;
//        cout << "[DEBUG] mazeHEIGHT = " << mazeHEIGHT << endl;
        
        /* Save coordinate information */
        MazeWall tmp;
   
        for (i = 0; i < imageHEIGHT; i++) {
            for (j = 0; j < imageWIDTH; j++) {
                switch (maze[i][j])
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
void ofApp::freeMemory(){
    /* Reset flags */
    isOpen = 0;
    isDFS = 0;
    isBFS = 0;
    
    /* Deallocation */
    int i;
    for (i = 0; i < imageHEIGHT; i++) {
        maze[i].clear();
    }
    for (i = 0; i < imageHEIGHT; i++) {
        vector<char>().swap(maze[i]);
    }
    maze.clear();
    vector<vector<char>>().swap(maze);
    walls.clear();
    vector<MazeWall>().swap(walls);
}

//--------------------------------------------------------------
bool ofApp::DFS(){
    
}

//--------------------------------------------------------------
void ofApp::dfsDraw(){
    
}
