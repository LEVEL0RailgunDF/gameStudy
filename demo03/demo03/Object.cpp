#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::set(char c)
{
    switch (c)
    {
    case '#':
        mType = OBJ_WALL;
        break;
    case ' ':
        mType = OBJ_SPACE;
        break;
    case 'o':
        mType = OBJ_BLOCK;
        break;
    case 'O':
        mType = OBJ_BLOCK;
        mGoalFlag = true;
        break;
    case 'p':
        mType = OBJ_MAN;
        break;
    case 'P':
        mType = OBJ_MAN;
        mGoalFlag = true;
        break;
    case '.':
        mType = OBJ_GOAL;
        mGoalFlag = true;
        break;
    case '\n':
        mType = OBJ_UNKNOWN;
        break;
    default:
        mType = OBJ_UNKNOWN;
        break;
    }
}

void Object::drawBackgrand(int x, int y, const Image* image) const
{
    ImageID id = Image_ID_SPACE;
    if (mType == OBJ_SPACE)
    {
        id = Image_ID_SPACE;
    }
    else if (mType == OBJ_WALL)
    {
        id = Image_ID_WALL;
    }
    else if (mType == OBJ_GOAL)
    {
        id = Image_ID_GOAL;
    }
    else if (mType == OBJ_BLOCK)
    {
        id = Image_ID_SPACE;
    }
    else if (mType == OBJ_MAN)
    {
        id = Image_ID_SPACE;
    }
    image->drawCell(32 * x , 32 * y , id * 32, 0, 32, 32);
}

void Object::drawForegrand(int x, int y, const Image* image, int moveCount) const
{
    ImageID id = Image_ID_SPACE;
    if (mType == OBJ_BLOCK)
    {
        id = Image_ID_BLOCK;
    }
    else if (mType == OBJ_MAN)
    {
        id = Image_ID_PLAYER;
    }


    if (id != Image_ID_SPACE) {
        int dx = mMoveX * (32 - moveCount);
        int dy = mMoveY * (32 - moveCount);
        image->drawCell(32 * x - dx, 32 * y - dy, id * 32, 0, 32, 32);
    }
    
}

void Object::move(int dx, int dy, Type replaceType)
{
    mMoveX = dx;
    mMoveY = dy;
    mType = replaceType;
}
