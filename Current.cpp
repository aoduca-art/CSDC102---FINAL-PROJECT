#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>

// Music, only accepts .WAV file
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

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
        while (true) {
            system("cls");
        cout << "1. Start Game" << endl;
        cout << "2. Leaderboard" << endl;
        cout << "3. Exit" << endl;

        char input = _getch();
        switch (input) {
            case '1':
                start();
                mapSetup();
                gameLoop();
                break;
            case '2':
                leaderboard();
                Sleep(1000);
                break;
            case '3':
                end();
                exit(0);
                break;
            default:
                cout << "Invalid choice!" << endl;
                Sleep(1000);
                break;
        }
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
        char input = _getch();
        switch (input) {
            // ASWD
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
            // Arrow keys
            case KEY_UP:
                if (playerY > 0) playerY--;
                break;
            case KEY_DOWN:
                if (playerY < 19) playerY++;
                break;
            case KEY_LEFT:
                if (playerX > 1) playerX--;
                break;
            case KEY_RIGHT:
                if (playerX < 38) playerX++;
                break;
        }
}

// Music

void playMusic(){
    /* NOTES for Music Player: 
    1. Only accepts .wav 
    2. Doesn't accept invalid characters like foreign languages, use English as filename
    */ 
    PlaySound(TEXT("DS_backgroundMusic.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
void endMusic(){
    PlaySound(0, 0, 0);
}

void gameLoop() {
    playMusic();
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
            ofstream file("leaderboard.txt");
            if (file.is_open()) {
                file << game.player.playerName << " - Score: " << game.player.score << endl;
                file.close();
            }
             break;
        }
    }


    return 0;   
}
