#pragma once

#include "ofMain.h"
#include <stack>
#include <queue>

struct Line{
    float startX;   /* x coordinate of the line's starting point */
    float startY;   /* y coordinate of the line's starting point */
    float endX;     /* x coordinate of the line's end point */
    float endY;     /* y coordinate of the line's end point */
};

enum Direction{     /* refers to neighboring cells */
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
    Direction parent;
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
            
        /* Open .maz file, save maze information.
           Call processImage() to save information of each cell. */
        bool readFile(ofFileDialogResult openFileResult);
    
        /* Initialize the information of each cell. */
        void processImage();
    
        /* Free dynamically allocated memories. */
        void freeMemory();
    
        /* Draw menu bar containing FILE, DFS, BFS, PLAY, QUIT. */
        void drawMenu();
    
        /* DFS */
        bool DFS();
    
        /* BFS */
        bool BFS();
    
        /* Draw the path found by DFS. */
        void drawDFS();
    
        /* Draw the path found by BFS. */
        void drawBFS();
    
        /* Used during DFS/BFS to save the searched paths. */
        void getSearchedPath(Vertex* curr);
    
        /* After DFS/BFS, find and save the shortest path. */
        void getShortestPath();
    
        /* After specific direction key is pressed,
           operates according to the corresponding key. */
        void PLAY(Direction way);
    
        /* Draw the path as the user progressed. */
        void drawPLAY();
        
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
        vector<Line> shortest_path;     /* Shortest path */
            
        int isOpen;                     /* File opened(1) or not(0). */
        
        ofRectangle FILEbutton;         /* FILE button */
        int FILEbuttonClicked;          /* FILE button clicked(1) or not(0). */
        
        ofRectangle DFSbutton;          /* DFS button */
        int isDFS;                      /* DFS on(1) or off(0). */

        ofRectangle BFSbutton;          /* BFS button */
        int isBFS;                      /* BFS on(1) or off(0). */
        
        ofRectangle QUITbutton;         /* QUIT button */
    
        ofRectangle PLAYbutton;         /* PLAY button */
        int isPLAY;                     /* PLAY on(1) or off(0). */
    
        vector<Line> play_path;         /* Path searched by user */
        float time;                     /* Time spent after play */
        bool reached;                   /* Flag: reached destination or not */
        int currX;                      /* User's current x position */
        int currY;                      /* User's current y position */
    
};
