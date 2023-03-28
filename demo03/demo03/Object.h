#pragma once
#include "Image.h"

class Object
{
public:
    enum Type {
        OBJ_SPACE,
        OBJ_WALL,
        OBJ_GOAL,
        OBJ_BLOCK,
        OBJ_MAN,

        OBJ_UNKNOWN,
    };

    enum ImageID
    {
        Image_ID_SPACE,
        Image_ID_WALL,
        Image_ID_GOAL,
        Image_ID_BLOCK,
        Image_ID_PLAYER,

    };

    Type mType;
    bool mGoalFlag = false;
    int mMoveX = 0 ;
    int mMoveY = 0 ;


public:
    Object();
    ~Object();

    void set(char c);
    void drawBackgrand(int x ,int y,const Image* image) const;
    void drawForegrand(int x, int y, const Image* image ,int moveCount) const;
    void move(int dx, int dy, Type replaceType);

};

