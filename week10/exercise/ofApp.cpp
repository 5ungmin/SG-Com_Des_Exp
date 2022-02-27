#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255);
    ofSetLineWidth(4);

    draw_flag = 0;
    load_flag = 0;
    waterfall_flag = 0;
    dot_diameter = 20.0f;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown

    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);


    ofSetLineWidth(5);
    if( draw_flag ){
        /* ========== week1 ========== */
        //굵기 5를 가진 선분을 그린다. (ofDrawLine())
        ofSetLineWidth(5);
        for (int i = 0; i < num_of_line; i++) {
            ofDrawLine(lx[i], ly[i], rx[i], ry[i]);
        }

        //loop
        for (int i = 0; i < num_of_dot; i++) {
            //반지름 10 값을 하는 원을 그려서 점을 표현한다. (ofDrawCircle())
            //해당 점이 물이 나오는 곳인가?
            //맞다면
            if (i == water_dot) {
                //빨간색 원을 그린다.
                ofSetColor(255, 0, 0);
                ofDrawCircle(dot_x[i], dot_y[i], 10);
            }
            //아니라면
            else {
                //검정색 원을 그린다.
                ofSetColor(0, 0, 0);
                ofDrawCircle(dot_x[i], dot_y[i], 10);
            }
        }
        //loop end
        /* ========== week1 end ========== */

        /* ========== week2 ========== */
//        ofSetLineWidth(2);
        if (waterfall_flag) {
            ofSetLineWidth(5);

            ofSetColor(0, 0, 255);
            for (int i = 0; i < path_idx-1; i++) {
                ofDrawLine((float)path_x[i], (float)path_y[i], (float)path_x[i+1], (float)path_y[i+1]);
            }
        }
        /* ========== week2 end ========== */
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q'){
        // Reset flags
        draw_flag = 0;
        load_flag = 0;
        waterfall_flag = 0;

        // Free the dynamically allocated memory exits.
        /* ========== week1 ========== */
//        cout << "Dynamically allocated memory has been freed." << endl;
        lx.clear(); ly.clear();
        rx.clear(); ry.clear();
        vector<int>().swap(lx);
        vector<int>().swap(ly);
        vector<int>().swap(rx);
        vector<int>().swap(ry);
        cout << "Memory for line segment has been freed" << endl;
        dot_x.clear(); dot_y.clear();
        vector<int>().swap(dot_x);
        vector<int>().swap(dot_y);
        cout << "Memory for dot has been freed" << endl;
        /* ========== week1 end ========== */

        /* ========== week2 ========== */
        slope.clear();
        vector<double>().swap(slope);
        path_x.clear(); path_y.clear();
        vector<int>().swap(path_x);
        vector<int>().swap(path_y);
        /* ========== week2 end ========== */

        _Exit(0);
    }
    if (key == 'd'){
        if( !load_flag) return;
        /* ========== week1 ========== */
        draw_flag = 1;
        /* ========== week1 end ========== */
    }
    if (key == 's'){
        /* ========== week2 ========== */
        if ( !load_flag) return;
        waterfall_flag = 1;
        /* ========== week2 end ========== */
    }
    if (key == 'e'){
        /* ========== week2 ========== */
        if ( !load_flag) return;
        waterfall_flag = 0;
        /* ========== week2 end ========== */
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if( key == 'l'){
        // Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a only txt for Waterfall");

        // Check whether the user opened a file
        if( openFileResult.bSuccess){
            ofLogVerbose("User selected a file");

            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }

    /* COMSIL1-TODO 4: This is selection dot control part.
     You can select dot in which water starts to flow by left, right direction key (<- , ->).
     */
    /* ========== week1 ========== */
    if (key == OF_KEY_RIGHT){ //->
        if (!waterfall_flag) {
            ofFill();

            ofSetColor(127, 23, 31); //paint it to black
            ofDrawCircle(dot_x[water_dot], dot_y[water_dot], 10);

            water_dot++;
            if (water_dot >= num_of_dot) {
                water_dot = 0;
            }

            ofSetColor(255, 0, 0); //paint it to red
            ofDrawCircle(dot_x[water_dot], dot_y[water_dot], 10);

            cout << "Selcted Dot Coordinate is (" << dot_x[water_dot] << ", " << dot_y[water_dot] << ")" << endl;
            initializeWaterLines();
        }
    }
    if (key == OF_KEY_LEFT){ //<-
        if (!waterfall_flag) {
            ofFill();

            ofSetColor(127, 23, 31); //paint it to black
            ofDrawCircle(dot_x[water_dot], dot_y[water_dot], 10);

            water_dot--;
            if (water_dot < 0) {
                water_dot = num_of_dot - 1;
            }

            ofSetColor(255, 0, 0); //paint it to red
            ofDrawCircle(dot_x[water_dot], dot_y[water_dot], 10);

            cout << "Selcted Dot Coordinate is (" << dot_x[water_dot] << ", " << dot_y[water_dot] << ")" << endl;
            initializeWaterLines();
        }
    }
    /* ========== week1 end ========== */
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
    //Path to the comma delimited file
    //string fileName = "input.txt";

    string fileName = openFileResult.getName();
    ofFile file(fileName);

    if( !file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;

    ofBuffer buffer(file);

    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0;


    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */
    int line_count = 0;

    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;

        // Split line into strings
        vector<string> words = ofSplitString(line, " ");

        if( words.size() == 1){
            if( input_type == 0){ // Input for the number of lines.
                num_of_line = atoi(words[0].c_str());
                cout << "The number of line is: " << num_of_line << endl;
            }
            else{ // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str());
                cout << "The number of dot is: " << num_of_dot << endl;
            }
        }
        else if (words.size() >= 2){
            int x1,y1,x2,y2;
            if( input_type == 0){ // Input for actual information of lines
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                x2 = atoi(words[2].c_str());
                y2 = atoi(words[3].c_str());
                /* ========== week1 ========== */
                if (0 <= x1 && x1 <= 1024 && 40 <= y1 && y1 <= 728 &&
                    0 <= x2 && x2 <= 1024 && 40 <= y2 && y1 <= 728) {
                    lx.push_back(x1);
                    ly.push_back(y1);
                    rx.push_back(x2);
                    ry.push_back(y2);
                    
                    slope.push_back(((double)y1 - (double)y2) / ((double)x1 - (double)x2)); //save the slope
                    
                    line_count++;
                }
                else
                    num_of_line--;

                if (line_count == num_of_line)
                    input_type = 1;
                /* ========== week1 end ========== */
            }
            else{ // Input for actual information of dots.
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                /* ========== week1 ========== */
                if (0 <= x1 && x1 <= 1024 && 40 <= y1 && y1 <= 728) {
                    dot_x.push_back(x1);
                    dot_y.push_back(y1);
                }
                else
                    num_of_dot--;
                /* ========== week1 end ========== */
            }
        } // End of else if.
    } // End of for-loop (Read file line by line).
    
    
    initializeWaterLines();
    
}

//--------------------------------------------------------------
void ofApp::initializeWaterLines() {
    path_idx = 0;
    path_x.clear();
    path_y.clear();
    
    //x, y를 water dot의 (x, y)로 set
    //water dot의 (x, y)를 path에 push
    int x = dot_x[water_dot];
    int y = dot_y[water_dot];
    path_x.push_back(x);
    path_y.push_back(y);
    
    
    while (y < ofGetHeight() - 50) {
        int select_line = -1;
        
        //next destination
        int dest_x = x;
        int dest_y = ofGetHeight() - 50;
        
        //모든 선반에 대해 알아본다.
        for (int i = 0; i < num_of_line; i++) {
            // lx < x < rx 라면
            if (lx[i] < x && x < rx[i]) {
                int drop_pointY = slope[i] * (x - lx[i]) + ly[i]; //떨어지는 물줄기와 선반이 만나는 y좌표를 구한다.
                if (drop_pointY < y) //선반이 water dot보다 위에 있다면 다음 선반으로 넘어간다.
                    continue;
                if (dest_y > drop_pointY) { //선반이 water dot보다 아래에 있다면 떨어뜨려줘야 한다.
                    dest_y = drop_pointY; //계산한 y좌표를 다음으로 갈 y좌표로 저장
                    select_line = i; //그 선반으로 떨어질 것임을 저장
                }
            }
        }
        
        //물줄기가 떨어질 곳의 path를 저장
        path_x.push_back(dest_x);
        path_y.push_back(dest_y);
        
        if (select_line != -1) { //물줄기가 떨어질 선반이 있다면 떨어진 이후 선반을 따라 흘러내려보내줘야 함
            //그 선반의 양쪽 y좌표를 비교해서 더 큰 y좌표를 가지는 쪽을 다음 path로 저장
            if (ly[select_line] > ry[select_line]) {
                dest_x = lx[select_line];
                dest_y = ly[select_line];
            }
            else {
                dest_x = rx[select_line];
                dest_y = ry[select_line];
            }
            path_x.push_back(dest_x);
            path_y.push_back(dest_y);
        }
        //다음 path를 찾는다.
        x = dest_x;
        y = dest_y;
    }
    
    
    path_idx = path_x.size();
}


