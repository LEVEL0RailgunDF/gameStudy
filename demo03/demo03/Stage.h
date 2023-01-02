#pragma once
#include "Array2D.h"
#include "Image.h"
#include "Object.h"
class Stage
{

public:
    //enum Object {
    //    OBJ_SPACE,
    //    OBJ_WALL,
    //    OBJ_GOAL,
    //    OBJ_BLOCK,
    //    OBJ_MAN,

    //    OBJ_UNKNOWN,
    //};

    int MAX_MOVE_COUNT = 32;

private:
    int stageWidth = 0;
    int stageHeight = 0;

    int mMoveCount = 0;
    Array2D <Object> mObjects;
    Array2D <bool> mGoalFlags;

    Image img;


    bool gPrevInputsW = false;
    bool gPrevInputsA = false;
    bool gPrevInputsS = false;
    bool gPrevInputsD = false;

    int gPreviousTime[10];

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

