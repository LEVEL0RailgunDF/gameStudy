#include "Stage.h"

Stage::Stage() {

}

Stage::Stage(char* stageData, int size, const char* imaFile)
{
	initialize(stageData, size, imaFile);
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

        switch (*d)
        {
        case '#':
            t = OBJ_WALL;
            break;
        case ' ':
            t = OBJ_SPACE;
            break;
        case 'o':
            t = OBJ_BLOCK;
            break;
        case 'O':
            t = OBJ_BLOCK;
            isGoal = true;
            break;
        case 'p':
            t = OBJ_MAN;
            break;
        case 'P':
            t = OBJ_MAN;
            isGoal = true;
            break;
        case '.':
            t = OBJ_GOAL;
            isGoal = true;
            break;
        case '\n':
            t = OBJ_UNKNOWN;
            x = 0;
            y++;
            break;
        default:
            t = OBJ_UNKNOWN;
            break;
        }

        if (t != OBJ_UNKNOWN) {
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
            img.drawCell(32 * x, 32 * y, 0, 0, 32, 32);
            unsigned color = 0x000000;
            switch (mObjects(x,y))
            {
            case OBJ_SPACE:
                img.drawCell(32 * x, 32 * y, 0, 0, 32, 32);
                break;
            case OBJ_WALL:
                img.drawCell(32 * x, 32 * y, 32, 0, 32, 32);
                break;
            case OBJ_GOAL:
                img.drawCell(32 * x, 32 * y, 64, 0, 32, 32);
                break;
            case OBJ_BLOCK:
                img.drawCell(32 * x, 32 * y, 96, 0, 32, 32);
                break;
            case OBJ_MAN:
                img.drawCell(32 * x, 32 * y, 128, 0, 32, 32);
                break;
            default:
                break;
            }
        }
    }
}

bool Stage::checkClear()
{
    for (int y = 0; y < stageHeight; y++) {
        for (int x = 0; x < stageWidth; x++) {
            if (mObjects(x, y) == OBJ_BLOCK && mGoalFlags(x,y) == false) {
                return false;
            }
        }
    }
    return true;
}

void Stage::update()
{
    int dx = 0;
    int dy = 0;
    bool InputW = false;
    bool InputA = false;
    bool InputS = false;
    bool InputD = false;

    Framework f = Framework::instance();
    if (f.isKeyOn('W')) {
        cout << "WWW" << endl;
        InputW = true;
    }
    if (f.isKeyOn('A')) {
        cout << "AAA" << endl;
        InputA = true;
    }
    if (f.isKeyOn('S')) {
        cout << "SSS" << endl;
        InputS = true;
    }
    if (f.isKeyOn('D')) {
        cout << "DDD" << endl;
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
            if (mObjects(px, py) == OBJ_MAN) {
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

    if (mObjects(tx, ty) == OBJ_SPACE) {
        if (mGoalFlags(px, py) == true) {
            mObjects(px, py) = OBJ_GOAL;
        }
        else {
            mObjects(px, py) = OBJ_SPACE;
        }
        mObjects(tx, ty) = OBJ_MAN;

    }

    if (mObjects(tx, ty) == OBJ_GOAL) {
        if (mGoalFlags(px, py) == true) {
            mObjects(px, py) = OBJ_GOAL;
        }
        else {
            mObjects(px, py) = OBJ_SPACE;
        }
        mObjects(tx, ty) = OBJ_MAN;
    }

    if (mObjects(tx, ty) == OBJ_BLOCK) {
        int btx = tx + dx;
        int bty = ty + dy;

        if (mObjects(btx, bty) == OBJ_SPACE || mObjects(btx, bty) == OBJ_GOAL) {
            mObjects(tx, ty) = OBJ_MAN;
            mObjects(btx, bty) = OBJ_BLOCK;

            if (mGoalFlags(px, py) == true) {
                mObjects(px, py) = OBJ_GOAL;
            }
            else
            {
                mObjects(px, py) = OBJ_SPACE;
            }
        }
    }

}