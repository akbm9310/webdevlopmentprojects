#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
vector<pair<int, int>> snake;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    snake.clear();
    snake.push_back({x, y});
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";

            bool printed = false;
            if (i == y && j == x) {
                cout << "O"; // Head
                printed = true;
            } else if (i == fruitY && j == fruitX) {
                cout << "*"; // Fruit
                printed = true;
            } else {
                for (int k = 1; k < snake.size(); k++) {
                    if (snake[k].first == j && snake[k].second == i) {
                        cout << "o"; // Body
                        printed = true;
                    }
                }
            }

            if (!printed) cout << " ";

            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\nScore: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = x;
    int prevY = y;

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    // Move body
    for (int i = snake.size() - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0] = {x, y};

    // Collision with wall
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // Collision with self
    for (int i = 1; i < snake.size(); i++) {
        if (snake[i].first == x && snake[i].second == y)
            gameOver = true;
    }

    // Fruit eating
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        snake.push_back({-1, -1}); // add a new segment
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Slow down game speed
    }
    cout << "Game Over!" << endl;
    return 0;
}
