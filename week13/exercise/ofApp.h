#pragma once

#include "ofMain.h"
#include <stack>
#include <queue>

struct Line{
    float startX;
    float startY;
    float endX;
    float endY;
};

enum Parent{
    UP, DOWN, LEFT, RIGHT, NONE
};

struct Vertex{
    /* Can or cannot go ... */
    bool up;
    bool down;
    bool left;
    bool right;
    /* Position of this vertex */
    int x;
    int y;
    /* This vertex is visited or not */
    bool visited;
    /* Parent position */
    Parent parent;
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
        bool BFS();
        void processImage();
        void drawMenu();
        void drawDFS();
        void drawBFS();
        void getSearchedPath(Vertex* curr);
        void getShortestPath();
        
        int imageHEIGHT;                /* Total HEIGHT */
        int imageWIDTH;                 /* Total WIDTH */
            
        int mazeHEIGHT;                 /* Maze HEIGHT */
        int mazeWIDTH;                  /* Maze WIDTH */
        
        vector<vector<char>> image;     /* Saves all information from the text file. */
        vector<Line> walls;             /* Saves wall information */
        vector<vector<Vertex>> maze;    /* Saves maze cell information */
        
        stack<Vertex*> DFS_stack;       /* DFS stack */
        queue<Vertex*> BFS_queue;       /* BFS stack */
        
        vector<Line> searched_path;     /* All path searched by algorithm */
        vector<Line> shortest_path;     /* Shortes path */
            
        int isOpen;                     /* File opened(1) or not(0). */
        
        ofRectangle FILEbutton;         /* FILE button */
        int FILEbuttonClicked;          /* FILE button clicked(1) or not(0). */
        
        ofRectangle DFSbutton;          /* DFS button */
        int isDFS;                      /* DFS on(1) or off(0). */

        ofRectangle BFSbutton;          /* BFS button */
        int isBFS;                      /* BFS on(1) or off(0). */
        
        ofRectangle QUITbutton;         /* QUIT button */
};
