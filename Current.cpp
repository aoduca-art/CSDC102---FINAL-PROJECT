#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <cstdlib>


using namespace std;

struct Obstacle {
    int x;
    int y;
    int speed;
};
struct Node {
    Obstacle obstacle;
    Node* next;
};

struct Player {
    string playerName;
    int score;
    int life;
};

class Game {
private:
    Node* head;

public:
    const char playerSymbol = 'P';
    Player player;
    int playerX = 20;
    int playerY = 19;
    char map[20][40];


    void start() {
        cout << "Welcome to the Game!" << endl;
        cout << "Enter your name: ";
        cin >> player.playerName;
        cout << "Press any key to start..." << endl;
        _getch();
        system("cls");
        cout << "Game Started!" << endl;
    }
    void end() {
        cout << "Game Over!" << endl;
        cout << "Press any key to exit..." << endl;
        _getch();
    }
    void menu() {
        cout << "1. Start Game" << endl;
        cout << "2. Leaderboard" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                start();
                mapSetup();
                gameLoop();
                break;
            case 2:
                leaderboard();
                break;
            case 3:
                end();
                exit(0);
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }
void leaderboard() {
        ifstream file("leaderboard.txt");
        if (file.peek() == EOF) {
            cout << "No scores yet!" << endl;
        }
        else {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
        }
        file.close();
    }

void mapSetup() {
     for (int y = 0; y < 20;y++){
        for (int x = 0; x < 40; x++){
           if (y == 0 && x > 0 && x < 39){
            map[y][x] = '=';
           }
           else if (x == 0 || x == 39){
            map[y][x] = '|';
           }
           else {
            map[y][x] = '.';
           }
        }
     }
    }

void displayMap() {
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 40; x++) {
            if (x == playerX && y == playerY) {
                cout << playerSymbol;
            }
            else {
                cout << map[y][x];
            }
        }
        cout << endl;
    }
}

void movePlayer() {
    if (_kbhit()) {
        char input = _getch();
        switch (input) {
            case 'w':
                if (playerY > 0) playerY--;
                break;
            case 's':
                if (playerY < 19) playerY++;
                break;
            case 'a':
                if (playerX > 1) playerX--;
                break;
            case 'd':
                if (playerX < 38) playerX++;
                break;
        }
    }
}
void gameLoop() {
    while (true) {
        system("cls");
        topUI();
        displayMap();
        movePlayer();
        Sleep(300);
        if (playerY == 0) {
            player.score += 1;
            playerY = 19;
            playerX = 20;
            break;
        }
    }
}

void topUI() {
    
    cout << "Name: " << player.playerName <<  right << setw(12) << "| Score: " << player.score << right << setw(8) << "| ";
    cout << "Life: " << player.life << endl;
}

};

int main(){
    Game game;
    Player player;  
    game.player.life = 3;
    game.player.score = 0;


    game.menu();
    while (game.player.life > 0) {
    game.gameLoop();
        if (game.player.life <= 0) {
            
            game.end();
            ofstream file("leaderboard.txt", ios::app);
            if (file.is_open()) {
                file << game.player.playerName << " - Score: " << game.player.score << endl;
                file.close();
            }
             break;
        }
    }


    return 0;   
}
