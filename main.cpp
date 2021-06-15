#include <bits/stdc++.h>
#include <random>
#include <windows.h>
#include <conio.h>
using namespace std;

char Map[20][20];

void gotoxy(short x, short y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Snake {
private: 
    bool dead;
    int dir;
    int delta[4] = {1, -1, 0, 0};
    struct SnakeNode {
        int x, y;
        SnakeNode *next, *pre;
        SnakeNode():next(nullptr), pre(nullptr) {}
        SnakeNode(int _x, int _y): x(_x), y(_y), next(nullptr), pre(nullptr) {}
    };
public: 
    SnakeNode *head, *tail;
    Snake():dir(3) {
        head = new SnakeNode(1, 2);
        tail = new SnakeNode(1, 1);
        head->next = tail;
        tail->pre = head;
        init();
    }
    ~Snake() {
        for(SnakeNode *p=head;p;p=p->next) {
            delete p;
        }
    }
    bool isDead() const {
        return dead;
    }
    void move() {
        //check next if wall or body
        int dx = delta[dir], dy = delta[3 - dir];
        int newX = head->x + dx, newY = head->y + dy;
        if(Map[newX][newY] == ' ') {
        	int lstX = tail->x, lstY = tail->y;
            SnakeNode *newTail = tail->pre;
            newTail->next = nullptr;
            tail->pre = nullptr;
            tail->next = head;
            head->pre = tail;
            head = tail;
            tail = newTail;
            tail->next = nullptr;
            
            head->x = newX;
            head->y = newY;
            Map[lstX][lstY] = ' ';
            gotoxy(lstY, lstX);
            cout << ' ';
            Map[newX][newY] = 'X'; 
            gotoxy(newY, newX); 
            cout << 'X';
        } else if(Map[newX][newY] == 'O') {
            SnakeNode *newHead = new SnakeNode(newX, newY);
            newHead->next = head;
            head->pre = newHead;
            head = newHead;
        	generateNewApple();
        	Map[newX][newY] = 'X'; 
            gotoxy(newY, newX);
            cout << 'X';
        } else {
            dead = true;
            return;
        }
    }
    void printMap() {
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 20; j++) {
                putchar(Map[i][j]);
            }
            putchar('\n');
        }
    }
    void generateNewApple() {
        mt19937 rnd(time(0));
        int x = rnd() % 18 + 1, y = rnd() % 18 + 1;
        while(Map[x][y] != ' ') {
            x = rnd() % 18 + 1, y = rnd() % 18 + 1;
        }
        Map[x][y] = 'O';
        gotoxy(y, x);
        cout << 'O';
    }
    void init() {
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 20; j++) {
                if(Map[i][j] != 'O')
                Map[i][j] = ' ';
            }
        }
        for(int i = 0; i < 20; i++) {
            Map[i][0] = '#';
            Map[0][i] = '#';
            Map[i][19] = '#';
            Map[19][i] = '#';
        }
    }
    void turn() {
        if(kbhit()) {
            char c = getch();
            c = getch();
            switch(c) {
            case 77:
                if(dir != 2)
                dir = 3;
                break;
            case 72:
            if(dir != 0)
                dir = 1;
                break;
            case 75:
            if(dir != 3)
                dir = 2;
                break;
            case 80:
            if(dir != 1)
                dir = 0;
                break;
            }
        }
    }
};

int main() {
    Snake game;
    game.printMap();
    game.generateNewApple();
    while(!game.isDead()) {
        
        game.turn();
        game.move();
        Sleep(100);
    }
    return 0;
}
