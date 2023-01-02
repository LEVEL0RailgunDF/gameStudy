#include "Stage.h"

Stage::Stage() {

}

Stage::Stage(char* stageData, int size, const char* imaFile)
{
	initialize(stageData, size, imaFile);

    for (int i = 0; i < 10 ; i++) {
        gPreviousTime[i] = 0;
    }
}

Stage::~Stage()
{
}

void Stage::setSize(char* stageData, int size)
{
    char* d = stageData;
    int x = 0;
    int y = 0;

    while (*d != '\0') {
        

        switch (*d)
        {
        case '#':
        case ' ':
        case 'o':
        case 'O':
        case 'p':
        case 'P':
        case '.':
            x ++;
            break;
        case '\n':
            y++;
            stageWidth = (stageWidth > x) ? stageWidth : x;
            stageHeight = (stageHeight > y) ? stageHeight : y;
            x = 0;
            break;
        default:
            break;
        }
        d++;
    }


    mObjects.setSize(stageWidth, stageHeight);
    mGoalFlags.setSize(stageWidth, stageHeight);
}


void Stage::initialize(char* stageData, int size, const  char* imaFile) {
    setSize(stageData,size );

    char* d = stageData;
    int x = 0;
    int y = 0;

    while (*d != '\0') {
        bool isGoal = false;
        Object t;
        t.set(*d);

        switch (*d)
        {
        case '\n':
            x = 0;
            y++;
            break;
        }


        if (t.mType != Object::OBJ_UNKNOWN) {
            mObjects(x,y) = t;
            mGoalFlags(x,y) = isGoal;
            x++;
        }


        d++;
    }

    img.load(imaFile);
}

void Stage::draw() {
    for (int y = 0; y < stageHeight; y++) {
        for (int x = 0; x <stageWidth; x++) {
            mObjects(x, y).drawBackgrand(x,y,&img);
        }
    }
    for (int y = 0; y < stageHeight; y++) {
        for (int x = 0; x < stageWidth; x++) {
            mObjects(x, y).drawForegrand(x, y, &img, mMoveCount);
        }
    }
   
}

bool Stage::checkClear()
{
    for (int y = 0; y < stageHeight; y++) {
        for (int x = 0; x < stageWidth; x++) {
            if (mObjects(x, y).mType == Object::OBJ_BLOCK && mObjects(x, y).mGoalFlag == false) {
                return false;
            }
        }
    }
    return true;
}

void Stage::update()
{
    Framework f = Framework::instance();
    
    int currentTime = f.time();

    int frameTime10 = currentTime - gPreviousTime[0];

    for (int i = 0; i < 10 - 1 ; i++) {
        gPreviousTime[i] = gPreviousTime[i + 1];
    }
    gPreviousTime[9] = currentTime;


    int frameRate = 1000 *10/ frameTime10;
    cout << frameRate<<endl;


    if (mMoveCount >= MAX_MOVE_COUNT) {
        mMoveCount = 0;
        for (int y = 0; y < stageHeight; y++) {
            for (int x = 0; x < stageWidth; x++) {
                mObjects(x, y).mMoveX = 0;
                mObjects(x, y).mMoveY = 0;
            }
        }
    }

    if (mMoveCount > 0) {
        mMoveCount ++;
        return;
    }


    int dx = 0;
    int dy = 0;
    bool InputW = false;
    bool InputA = false;
    bool InputS = false;
    bool InputD = false;

   
    if (f.isKeyOn('W')) {
        InputW = true;
    }
    if (f.isKeyOn('A')) {
        InputA = true;
    }
    if (f.isKeyOn('S')) {
        InputS = true;
    }
    if (f.isKeyOn('D')) {
        InputD = true;
    }

    if (InputW && (!gPrevInputsW)) {
        dy = -1;
    }
    else if (InputA && (!gPrevInputsA)) {
        dx = -1;
    }
    else if (InputS && (!gPrevInputsS)) {
        dy = 1;
    }
    else if (InputD && (!gPrevInputsD)) {
        dx = 1;
    }

    gPrevInputsW = InputW;
    gPrevInputsA = InputA;
    gPrevInputsS = InputS;
    gPrevInputsD = InputD;


    int px = 0;
    int py = 0;

    bool isPlayer = false;
    for (py = 0; py < stageHeight; py++) {
        for (px = 0; px < stageWidth; px++) {
            if (mObjects(px, py).mType == Object::OBJ_MAN) {
                isPlayer = true;
                break;
            }
        }

        if (isPlayer) {
            break;
        }
    }


    int tx = px + dx;
    int ty = py + dy;

    if (mObjects(tx, ty).mType == Object::OBJ_SPACE) {
        mObjects(tx, ty).move(dx, dy, Object::OBJ_MAN);
        if (mObjects(px, py).mGoalFlag) {
            mObjects(px, py).move(dx, dy, Object::OBJ_GOAL);
        }
        else {
            mObjects(px, py).move(dx, dy, Object::OBJ_SPACE);
        }
        mMoveCount = 1;
    }
    
    if (mObjects(tx, ty).mType == Object::OBJ_GOAL) {
        mObjects(tx, ty).move(dx, dy, Object::OBJ_MAN);
        if (mObjects(px, py).mGoalFlag) {
            mObjects(px, py).move(dx, dy, Object::OBJ_GOAL);
        }
        else {
            mObjects(px, py).move(dx, dy, Object::OBJ_SPACE);
        }
        mMoveCount = 1;
    }
    
    if (mObjects(tx, ty).mType == Object::OBJ_BLOCK) {
            int btx = tx + dx;
            int bty = ty + dy;

            if (mObjects(btx, bty).mType == Object::OBJ_SPACE || mObjects(btx, bty).mType == Object::OBJ_GOAL) {
                mObjects(btx, bty).move(dx, dy, Object::OBJ_BLOCK);
                mObjects(tx, ty).move(dx, dy, Object::OBJ_MAN);

                if (mObjects(px, py).mGoalFlag == true) {
                    mObjects(px, py).move(dx, dy, Object::OBJ_GOAL);
                }
                else
                {
                    mObjects(px, py).move(dx, dy, Object::OBJ_SPACE);
                }
                mMoveCount = 1;
            }
        }

}