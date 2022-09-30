#pragma once
#include "Array2D.h"
#include "Image.h"

class Stage
{

public:
    enum Object {
        OBJ_SPACE,
        OBJ_WALL,
        OBJ_GOAL,
        OBJ_BLOCK,
        OBJ_MAN,

        OBJ_UNKNOWN,
    };
private:
    int stageWidth = 0;
    int stageHeight = 0;
    Array2D <int> mObjects;
    Array2D <bool> mGoalFlags;

    Image img;


    bool gPrevInputsW = false;
    bool gPrevInputsA = false;
    bool gPrevInputsS = false;
    bool gPrevInputsD = false;
public:
    Stage();
    Stage(char* stageData, int size, const char* imaFile);

    ~Stage();
    void setSize(char* stageData, int size);
    void initialize(char* stageData, int size, const char* imaFile);
    void update();
    bool checkClear();
    void draw();


private:
};
