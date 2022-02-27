#pragma once

#include "ofMain.h"

struct MazeWall{
    float startX;
    float startY;
    float endX;
    float endY;
};

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
            
    bool readFile(ofFileDialogResult openFileResult);
    void freeMemory();
    bool DFS();
    void dfsDraw();
    
    int imageHEIGHT;                /* Total HEIGHT */
    int imageWIDTH;                 /* Total WIDTH */
        
    int mazeHEIGHT;                 /* Maze HEIGHT */
    int mazeWIDTH;                  /* Maze WIDTH */
    
    vector<vector<char>> maze;      /* Saves all information from the text file. */
    vector<MazeWall> walls;         /* Saves wall information */

    int** visited;                  /* Saves visited or not. */
    
    int maze_col;                   /* Index for column. */
    int maze_row;                   /* Index for row. */
    
    int k;
    
    int isOpen;                     /* File opened(1) or not(0). */
    
    ofRectangle FILEbutton;         /* FILE button */
    int FILEbuttonClicked;          /* FILE button clicked(1) or not(0). */
    
    ofRectangle DFSbutton;          /* DFS button */
    int isDFS;                      /* DFS on(1) or off(0). */

    ofRectangle BFSbutton;          /* BFS button */
    int isBFS;                      /* BFS on(1) or off(0). */
};
