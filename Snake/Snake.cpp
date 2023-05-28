// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameover;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100];

int nTail; //tail length

enum eDirection{ STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup() {

    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;

}

void Draw() {

    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << '#';
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int z = 0; z < nTail; z++) {
                    if (tailX[z] == j && tailY[z] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
           
        }
       cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << '#';
    cout << endl;
    cout <<"Score : " << score << endl;

}

void Logic() {

    int prevX = tailX[0]; //previous tail segment X coordinate
    int prevY = tailY[0]; //previous tail segment Y coordinate
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y; 
    }

    switch (dir) {
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    default:
        break;
    }

   // if (x > width || x< 0 || y>height || y < 0)//death on wall hit
   //     gameover = true;
    if (x >= width) //
        x = 0;// appear from other side on wall hit
    else if (x < 0)//
        x = width - 1;//
    if (y >= height) //
        y = 0;// appear from other side on wall hit
    else if (y < 0)//
        y = height - 1;//
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;
    if (x == fruitX && y == fruitY) {
        score+=10;
        nTail++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    

}

void Input() {

    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'w':
            dir = UP;
            break;
        case 'x':
            gameover = true;
            break;

        }
    }

}


int main()
{
    Setup();

    while (!gameover) {
        Draw();
        Input();
        Logic();
        Sleep(150);
    }



    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
