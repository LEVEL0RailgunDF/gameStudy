// demo01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

enum Object {
    OBJ_SPACE,
    OBJ_WALL,
    OBJ_GOAL,
    OBJ_BLOCK,
    OBJ_BLOCK_ON_GOAL,
    OBJ_MAN,
    OBJ_MAN_ON_GOAL,

    OBJ_UNKNOWN,
};


const char gStageData[] = "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########";

const int gStateWidth = 8;
const int gStateHeight = 5;


void initialize(Object* state,
    int width,
    int height,
    const char* stageData) 
{
    
    const char* d = stageData;
    int x = 0;
    int y = 0;


    while (*d != '\0') {

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
            t = OBJ_BLOCK_ON_GOAL;
            break;
        case 'p':
            t = OBJ_MAN;
            break;
        case 'P':
            t = OBJ_MAN_ON_GOAL;
            break;
        case '.':
            t = OBJ_GOAL;
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
            state[x + width * y] = t;
            x++;
        }


        d++;
    }


}

char getInput() 
{
    char input;
    std::cin >> input;
    return input;
}

void updateGame(Object* state, char input, int width, int height)
{
    int dx = 0;
    int dy = 0;
    switch (input)
    {
    case 'w':
        dy = -1;
        break;
    case 's':
        dy = 1;
        break;
    case 'a':
        dx = -1;
        break;
    case 'd':
        dx = 1;
        break;
    default:
        break;
    }

    int playerPos = 0;
    for (playerPos = 0; playerPos < width * height; playerPos++) {
        if (state[playerPos] == OBJ_MAN || state[playerPos] == OBJ_MAN_ON_GOAL) {
            break;
        }
    }
    
    int px = playerPos % width;
    int py = playerPos / width;

    int tx = px + dx;
    int ty = py + dy;

    int tempPlayerPos = tx + ty * width;
    if (state[tempPlayerPos] == OBJ_SPACE) {
        if (state[playerPos] == OBJ_MAN_ON_GOAL) {
            state[playerPos] = OBJ_GOAL;
            state[tempPlayerPos] = OBJ_MAN;
        }
        else {
            state[playerPos] = OBJ_SPACE;
            state[tempPlayerPos] = OBJ_MAN;
        }
        
    }

    if (state[tempPlayerPos] == OBJ_GOAL) {
        if (state[playerPos] == OBJ_MAN_ON_GOAL) {
            state[playerPos] = OBJ_GOAL;
            state[tempPlayerPos] = OBJ_MAN_ON_GOAL;
        }
        else {
            state[playerPos] = OBJ_SPACE;
            state[tempPlayerPos] = OBJ_MAN_ON_GOAL;

        }
    }

    if (state[tempPlayerPos] == OBJ_BLOCK || state[tempPlayerPos] == OBJ_BLOCK_ON_GOAL) {
        int btx = tx + dx;
        int bty = ty + dy;
        int tempBlockPos = bty * width + btx;
        if (state[tempBlockPos] == OBJ_SPACE || state[tempBlockPos] == OBJ_GOAL) {
            if (state[tempBlockPos] == OBJ_SPACE) {
                if (state[tempPlayerPos] == OBJ_BLOCK) {
                    state[tempPlayerPos] = OBJ_MAN;
                }
                else {
                    state[tempPlayerPos] = OBJ_MAN_ON_GOAL;
                }

                state[tempBlockPos] = OBJ_BLOCK;
            }
            else {
                if (state[tempPlayerPos] == OBJ_BLOCK) {
                    state[tempPlayerPos] = OBJ_MAN;
                }
                else {
                    state[tempPlayerPos] = OBJ_MAN_ON_GOAL;
                }
                state[tempBlockPos] = OBJ_BLOCK_ON_GOAL;

            }


            if (state[playerPos] == OBJ_MAN_ON_GOAL) {
                state[playerPos] = OBJ_GOAL;
            }
            else
            {
                state[playerPos] = OBJ_SPACE;
            }


        }
    }

        
}

void draw(Object* state,int width,int height)
{
    const char font[] = { ' ', '#', '.', 'o', 'O', 'p', 'P' };
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << font[state[y * width + x]];
        }
        std::cout << '\n';
    }

}

bool checkWin(Object* state, int width, int height) {
    bool win = true;

    for (int i = 0; i < width * height; i++) {
        if (state[i] == OBJ_BLOCK) {
            win = false;
            break;
        }
    }

    return win;
}

int main()
{
    Object* state = new Object[gStateWidth * gStateHeight];

    initialize(state, gStateWidth, gStateHeight, gStageData);

    while (true) {

        draw(state, gStateWidth, gStateHeight);

        if (checkWin(state, gStateWidth, gStateHeight)) {
            std::cout << "you win!";
            break;
        }

        char input;
        input = getInput();
        
        updateGame(state,input, gStateWidth, gStateHeight);
        
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
