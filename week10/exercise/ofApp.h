#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

    /* WaterFall-related member variables Regions */

    // flag variables
    int draw_flag;
    int load_flag;
    int waterfall_flag;

    // Line segment and dot related variables
    int num_of_line, num_of_dot;
    float dot_diameter;
    
    /* ========== week1 ========== */
    vector<int> lx, ly, rx, ry;
    vector<int> dot_x, dot_y;
    int water_dot = 0;
    /* ========== week1 end ========== */
    
    /* ========== week2 ========== */
    vector<double> slope;
    vector<int> path_x, path_y;
    int path_idx = 0;
    /* ========== week2 end ========== */

    /* WaterFall-related member functions */

    void processOpenFileSelection(ofFileDialogResult openFileResult);
    void initializeWaterLines();

};