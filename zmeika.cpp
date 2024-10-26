#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int width = 20;
int height = 10;
bool GameOver = false;
bool GameWin = false;
int foodX, foodY;
int metka = 0;

struct SnakeNode {
    int x, y;
    SnakeNode* next;
    SnakeNode(int startX, int startY) : x(startX), y(startY), next(nullptr) {}
};

class Snake {
public:
    SnakeNode* head = nullptr;
    char direction = 'd';

    Snake(int startX, int startY) {
        head = new SnakeNode(startX, startY);
    }
    void genFood() {
        srand(time(0));
        bool isOnSnake;

        do {
            foodX = rand() % (width - 2) + 1; 
            foodY = rand() % (height - 2) + 1;
            isOnSnake = false;

            
            SnakeNode* current = head;
            while (current != nullptr) {
                if (current->x == foodX && current->y == foodY) {
                    isOnSnake = true;
                    break;
                }
                current = current->next;
            }
        } while (isOnSnake);
    }
    void move() {
        int newX = head->x;
        int newY = head->y;
        if (_kbhit()) {
            int key = _getch();
            if (key == 87 || key == 119)
            {
                if (direction != 's')
                {
                    direction = 'w';
                }
                
            }
            else if (key == 65 || key == 97)
            { 
                if (direction != 'd')
                {
                    direction = 'a';
                }
            }
            else if (key == 83 || key == 115)
            {
                if (direction != 'w')
                {
                    direction = 's';
                }
            }
            else if (key == 68 || key == 100) 
            { 
                if(direction!='a')
                {
                    direction = 'd';
                }
                
            
            }
        }

        
        switch (direction) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        }

        
        if (Game(newX, newY)) {
            GameOver = true;
            return;
        }

        
        if (newX == foodX && newY == foodY) {
            SnakeNode* newHead = new SnakeNode(newX, newY);
            newHead->next = head;
            head = newHead;
            metka++;

            if (metka == 100) {
                GameWin = true;
                return;
            }
            genFood();
        }
        else {
            
            SnakeNode* newHead = new SnakeNode(newX, newY);
            newHead->next = head;
            head = newHead;
            SnakeNode* temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }
    bool Game(int x, int y) { 
        if (x < 1 || x >= width - 1 || y < 1 || y >= height - 1) {
            GameOver = true;
            return true;
        }

        SnakeNode* current = head;
        while (current != nullptr) {
            if (current->x == x && current->y == y) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void draw() {
        system("cls");
        for (int i = 0; i < width; ++i) cout << '/';
        cout << endl;
        for (int i = 1; i < height-1; ++i) {
            for (int j = 0; j < width; ++j) {
                if (j == 0 || j == width - 1) {
                    cout << '/';
                }
                else if (i == head->y && j == head->x) {
                    cout << '#';
                }
                else if (i == foodY && j == foodX) {
                    cout << 'O';
                }
                else {
                    bool isBodyPart = false;
                    SnakeNode* current = head->next;
                    while (current != nullptr) {
                        if (current->x == j && current->y == i) {
                            cout << '*';
                            isBodyPart = true;
                            break;
                        }
                        current = current->next;
                    }
                    if (!isBodyPart) cout << ' ';
                }
            }
            cout << endl;
        }
        for (int i = 0; i < width; ++i) cout << '#';
        cout << "X:" << foodX << ",Y:" << foodY;
        cout << endl;
    }
};

int main() {
    setlocale(0, "rus");
    
   Snake snake(width / 2, height / 2);
    snake.genFood();

    while (!GameOver && !GameWin) {

        snake.move();
        snake.draw();
        Sleep(300);
        
    }

    if (GameWin) {
        cout << "Game Win!";
    }
    else {
        cout << "Game Over!";
    }

    return 0;
}
//struct Snake {
//    int x, y;
//    Snake* next;
//};
//
//void input();
//void generateFood(Snake* head);
//void drawField(Snake* head);
//bool gameOver(Snake* head);
//void moveSnake(Snake*& head, Snake*& tail);
//bool foodTaken(Snake* head);
//
//const int width = 20;
//const int height = 10;
//
//int foodX;
//int foodY;
//int score;
//
//enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
//Direction dir;
//
//int main() {
//    Snake* head = new Snake();
//    head->x = width / 2;
//    head->y = height / 2;
//    head->next = nullptr;
//    Snake* tail = head;
//
//    score = 0;
//    dir = RIGHT;
//    generateFood(head);
//
//    while (dir != STOP) {
//        drawField(head);
//        input();
//        moveSnake(head, tail);
//        if (gameOver(head)) {
//            cout << "Game over!" << endl;
//            Sleep(10000);
//            break;
//        }
//        Sleep(300);
//    }
//
//    return 0;
//}
//
//void input() {
//    if (_kbhit()) {
//        switch (_getch()) {
//        case 'a': dir = LEFT; break;
//        case 'd': dir = RIGHT; break;
//        case 'w': dir = UP; break;
//        case 's': dir = DOWN; break;
//        case '0': dir = STOP; break;
//        }
//    }
//}
//
//void generateFood(Snake* head) {
//    bool foodOnSnake;
//    do {
//        foodX = rand() % width;
//        foodY = rand() % height;
//        foodOnSnake = false;
//        Snake* temp = head;
//        while (temp != nullptr) {
//            if (temp->x == foodX && temp->y == foodY) {
//                foodOnSnake = true;
//                break;
//            }
//            temp = temp->next;
//        }
//    } while (foodOnSnake);
//}
//
//void drawField(Snake* head) {
//    system("cls");
//    for (int i = 0; i < width + 2; i++) cout << "#";
//    cout << endl;
//
//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {
//            if (j == 0) cout << "#";
//            bool isBodyPart = false;
//            Snake* temp = head;
//
//            while (temp != nullptr) {
//                if (temp->x == j && temp->y == i) {
//                    cout << "O";
//                    isBodyPart = true;
//                }
//                temp = temp->next;
//            }
//
//            if (!isBodyPart) {
//                if (foodX == j && foodY == i) cout << "F";
//                else cout << " ";
//            }
//
//            if (j == width - 1) cout << "#";
//        }
//        cout << endl;
//    }
//
//    for (int i = 0; i < width + 2; i++) cout << "#";
//    cout << endl;
//
//    cout << "Score: " << score << endl;
//}
//
//bool gameOver(Snake* head) {
//    if (head->x < 0 || head->x >= width || head->y < 0 || head->y >= height)
//        return true;
//
//    Snake* temp = head->next;
//    while (temp != nullptr) {
//        if (temp->x == head->x && temp->y == head->y)
//            return true;
//        temp = temp->next;
//    }
//
//    return false;
//}
//
//void moveSnake(Snake*& head, Snake*& tail) {
//    int prevX = head->x;
//    int prevY = head->y;
//    int tempX, tempY;
//
//    switch (dir) {
//    case LEFT: head->x--; break;
//    case RIGHT: head->x++; break;
//    case UP: head->y--; break;
//    case DOWN: head->y++; break;
//    default: break;
//    }
//
//    if (foodTaken(head)) {
//        Snake* newSnake = new Snake();
//        newSnake->x = prevX;
//        newSnake->y = prevY;
//        newSnake->next = nullptr;
//        tail->next = newSnake;
//        tail = newSnake;
//        generateFood(head);
//    }
//    else {
//        Snake* temp = head->next;
//        while (temp != nullptr) {
//            tempX = temp->x;
//            tempY = temp->y;
//
//            temp->x = prevX;
//            temp->y = prevY;
//
//            prevX = tempX;
//            prevY = tempY;
//            temp = temp->next;
//        }
//    }
//}
//
//bool foodTaken(Snake* head) {
//    if (head->x == foodX && head->y == foodY) {
//        score += 10;
//        return true;
//    }
//    return false;
//}