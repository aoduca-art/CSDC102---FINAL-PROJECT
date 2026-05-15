#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

struct Player
{
 string playerName;
 int score;
 int life;
};

struct Obstacle
{
 int x;
 int y;
 int speed = 1;
 int length;
 int direction;
 char symbol;
};

struct Node
{
 Obstacle obstacle;
 Node *next;
};

struct LeaderboardEntry
{
 string name;
 int score;
};

class Game
{
private:
 char map[20][42];
 Node *head = nullptr;

public:
 Player player;
 int playerX = 19;
 int playerY = 19;
 const char playerSymbol = 'P';

 void gotoXY(int x, int y)
 {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(
   GetStdHandle(STD_OUTPUT_HANDLE),
   coord);
 }

 void setColor(int color)
 {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
 }

 void showMenu(string type){
	if (type == "Logo"){
	// Do not indent or move line 72 - 81, they are string literals. They show as is.
cout << R"(
  ____                 _    ____                   _
 |  _ \ ___   __ _  __| |  / ___|_ __ ___  ___ ___(_)_ __   __ _
 | |_) / _ \ / _` |/ _` | | |   | '__/ _ \/ __/ __| | '_ \ / _` |
 |  _ < (_) | (_| | (_| | | |___| | | (_) \__ \__ \ | | | | (_| |
 |_| \_\___/ \__,_|\__,_|  \____|_|  \___/|___/___/_|_| |_|\__, |
                C h a l l e n g e                          |___/

                Written for CSDC102 | Language: C++

)";
	} else if (type == "Options"){
cout << R"( 	                
                    . . . . . . . . . . . . . . 
                   :                           :
                   :  1. Start game.           :
                   :  2. Leaderboard           :
                   :  3. Exit                  :
                   :                           :
                               )";
	} else if (type == "Instructions"){
cout << R"(
               . . . . . . . . . . . . . . . . . . .
              :                                     :
              :           Instructions:             :
              :                                     :
              :   - Move with WASD or Arrow Keys    :
              :   - Avoid )";  setColor(12); cout << "trucks "; setColor(7); cout << "("; setColor(12); cout << "#";  setColor(7); cout << ")                :";
cout << R"(         
              :   - Ride )";  setColor(11); cout << "logs "; setColor(7); cout << "("; setColor(11); cout << "="; setColor(7); cout << ")                   :";
cout << R"(                                    
              :   - Avoid )";  setColor(9); cout << "water "; setColor(7); cout << "("; setColor(9); cout << "~"; setColor(7); cout << ")                 :";
cout << R"(
              :                                     :                                                                   
                        Enter your name: )";

	} else if (type == "Start"){
		cout << "\n                     Press any key to start...";
	}

}

 void start(){
	    system("cls");
		showMenu("Logo");
		showMenu("Instructions");
		cin >> player.playerName;
		player.life = 3;
		showMenu("Start");
		_getch();
	}

 void end(){
  system("cls");
  cout << endl;
  cout << "Game closing\n";
  _getch();
 }

 void menu(){
		while (true){
			system("cls");
			playMusic(3);
			showMenu("Logo");
			showMenu("Options");
			char input = _getch();
			switch (input){
			case '1':
				player.score = 0;
				playerX = 19;
				playerY = 19;
				start();
				mapSetup();
				clearObstacles();
				gameLoop();
				break;
			case '2':
				leaderboard();
				cout << endl;
				system("pause");
				break;
			case '3':
				end();
				clearObstacles();
				exit(0);
				break;
			}
			stopMusic();
		}
	}

 void leaderboard(){

  system("cls");

  ifstream file("leaderboard.txt");

  if (!file)
  {
   cout << "No leaderboard yet!" << endl;
   return;
  }
  if (file.peek() == ifstream::traits_type::eof())
  {
   cout << "Noones here yet!, Go go go!" << endl;
   return;
  }

  LeaderboardEntry players[100];

  int count = 0;

  while (file >> players[count].name >> players[count].score)
  {
   count++;
   if (count > 4)
    break;
  }

  file.close();

  // SORT HIGHEST SCORE FIRST
  for (int i = 0; i < count - 1; i++)
  {

   for (int j = i + 1; j < count; j++)
   {

    if (players[j].score > players[i].score)
    {

     LeaderboardEntry temp = players[i];
     players[i] = players[j];
     players[j] = temp;
    }
   }
  }

  cout << "========== LEADERBOARD ==========" << endl;
  cout << endl;

  for (int i = 0; i < count; i++)
  {

   string rank;

   if (i == 0)
    rank = "1st";
   else if (i == 1)
    rank = "2nd";
   else if (i == 2)
    rank = "3rd";
   else
    rank = to_string(i + 1) + "th";

   cout << left << setw(10) << rank;
   cout << setw(15) << players[i].name;
   cout << "Score: " << players[i].score << endl;
  }
 }

 void mapSetup()
 {
  for (int y = 0; y < 20; y++)
  {
   for (int x = 0; x < 42; x++)
   {
    if (x == 0 || x == 41)
    {
     map[y][x] = '|';
    }
    else if (y == 0 && x > 0 && x < 41)
    {
     map[y][x] = '=';
    }
    else if (y == 19 && x > 0 && x < 41)
    {
     map[y][x] = ' ';
    }
    else
    {
     map[y][x] = '.';
    }
   }
  }

  for (int x = 1; x < 41; x++)
  {
   map[7][x] = '~';
   map[8][x] = '~';
   map[16][x] = '~';
   map[17][x] = '~';
  }
 }

 void spawnObstacle()
 {

  int lanes[] = {1, 2, 3, 4, 5, 7, 8, 10, 11, 12, 13, 14, 16, 17};

  for (int i = 0; i < 14; i++)
  {
   int lane = lanes[i];

   int chance = rand() % 100;
   if (chance < 8)
   {
    char symbol;
    int length;

    if (lane == 7 || lane == 8 || lane == 16 || lane == 17)
    {
     symbol = '=';
     length = 4;
    }
    else
    {
     symbol = '#';
     length = 5;
    }

    int direction;

    if (lane % 2 == 0)
    {
     direction = 1;
    }
    else
    {
     direction = -1;
    }

    int x;
    if (direction == 1)
    {
     x = -length;
    }
    else
    {
     x = 40;
    }
    if (!laneOccupied(lane, x))
    {
     addObstacle(x, lane, length, direction, symbol);
    }
   }
  }
 }

 bool laneOccupied(int lane, int x)
 {
  Node *temp = head;
  while (temp != nullptr)
  {
   if (temp->obstacle.y == lane)
   {
    if (abs(temp->obstacle.x - x) < temp->obstacle.length + 2)
    {
     return true;
    }
   }
   temp = temp->next;
  }
  return false;
 }

 void moveObstacles()
 {
  Node *temp = head;
  Node *prev = nullptr;

  while (temp != nullptr)
  {
   temp->obstacle.x += temp->obstacle.direction * temp->obstacle.speed;

   bool remove = false;

   if (temp->obstacle.direction == 1 && temp->obstacle.x > 40)
   {
    remove = true;
   }
   else if (temp->obstacle.direction == -1 && temp->obstacle.x + temp->obstacle.length < 0)
   {
    remove = true;
   }

   if (remove)
   {
    Node *toDelete = temp;
    if (prev == nullptr)
    {
     head = temp->next;
     temp = head;
    }
    else
    {
     prev->next = temp->next;
     temp = temp->next;
    }
    delete toDelete;
   }
   else
   {
    prev = temp;
    temp = temp->next;
   }
  }
 }

 void displayMap()
 {

  char mapCopy[20][42];
  for (int y = 0; y < 20; y++)
  {
   for (int x = 0; x < 42; x++)
   {
    mapCopy[y][x] = map[y][x];
   }
  }
  Node *temp = head;

  while (temp != nullptr)
  {
   for (int i = 0; i < temp->obstacle.length; i++)
   {
    int x = temp->obstacle.x + i;
    int y = temp->obstacle.y;
    if (x > 0 && x < 41)
    {
     mapCopy[y][x] = temp->obstacle.symbol;
    }
   }
   temp = temp->next;
  }
  mapCopy[playerY][playerX] = playerSymbol;

  for (int y = 0; y < 20; y++)
  {
   for (int x = 0; x < 42; x++)
   {
    if (mapCopy[y][x] == '=')
    {
     setColor(11);
    }
    else if (mapCopy[y][x] == '#')
    {
     setColor(12);
    }
    else if (mapCopy[y][x] == '~')
    {
     setColor(9);
    }
    else if (mapCopy[y][x] == 'P')
    {
     setColor(10);
    }
    else
    {
     setColor(7);
    }

    cout << mapCopy[y][x];
   }
   cout << endl;
  }

  setColor(7);
 }

 void addObstacle(int x, int y, int length, int direction, char symbol)
 {
  Node *newNode = new Node;
  newNode->obstacle.x = x;
  newNode->obstacle.y = y;
  newNode->obstacle.length = length;
  newNode->obstacle.direction = direction;
  newNode->obstacle.symbol = symbol;
  newNode->next = nullptr;
  if (head == nullptr)
  {
   head = newNode;
  }
  else
  {
   Node *temp = head;
   while (temp->next != nullptr)
   {
    temp = temp->next;
   }
   temp->next = newNode;
  }
 }

 void clearObstacles()
 {
  Node *temp;
  while (head != nullptr)
  {
   temp = head;
   head = head->next;
   delete temp;
  }
 }

 void moveWithLog()
 {

  Node *temp = head;

  while (temp != nullptr)
  {

   if (temp->obstacle.symbol == '=')
   {

    for (int i = 0; i < temp->obstacle.length; i++)
    {

     int x = temp->obstacle.x + i;

     if (x == playerX &&
      temp->obstacle.y == playerY)
     {

      playerX +=
       temp->obstacle.direction *
       temp->obstacle.speed;

      return;
     }
    }
   }

   temp = temp->next;
  }
 }

 bool isPlayerOnLog()
 {

  Node *temp = head;

  while (temp != nullptr)
  {

   if (temp->obstacle.symbol == '=')
   {

    for (int i = 0; i < temp->obstacle.length; i++)
    {

     int x = temp->obstacle.x + i;

     if (x == playerX &&
      temp->obstacle.y == playerY)
     {

      return true;
     }
    }
   }

   temp = temp->next;
  }

  return false;
 }

 void checkCollision()
 {
  Node *temp = head;
  while (temp != nullptr)
  {
   for (int i = 0; i < temp->obstacle.length; i++)
   {
    int x = temp->obstacle.x + i;
    int y = temp->obstacle.y;
    if (x == playerX && y == playerY)
    {
     if (temp->obstacle.symbol == '#')
     {
      player.life--;
      playerX = 19;
      playerY = 19;
      return;
     }
     else if (temp->obstacle.symbol == '=')
     {
      // Riding log, do nothing
     }
    }
   }
   temp = temp->next;
  }
  bool onLog = false;
  temp = head;
  while (temp != nullptr)
  {
   if (temp->obstacle.symbol == '=')
   {
    for (int i = 0; i < temp->obstacle.length; i++)
    {
     int x = temp->obstacle.x + i;
     int y = temp->obstacle.y;
     if (x == playerX && y == playerY)
     {
      onLog = true;
     }
    }
   }
   temp = temp->next;
  }
  if (map[playerY][playerX] == '~' &&
   !isPlayerOnLog())
  {

   player.life--;
   playerX = 19;
   playerY = 19;
   return;
  }
 }

 void movePlayer()
 {
  if (_kbhit())
  {
   int input = _getch();
   if (input == 0 || input == 224)
   {
    input = _getch();
    switch (input)
    {
    case KEY_UP:
     if (playerY > 0)
      playerY--;
     break;
    case KEY_DOWN:
     if (playerY < 19)
      playerY++;
     break;
    case KEY_LEFT:
     if (playerX > 1)
      playerX--;
     break;
    case KEY_RIGHT:
     if (playerX < 40)
      playerX++;
     break;
    }
   }
   else
   {
    switch (input)
    {
    case 'w':
    case 'W':
     if (playerY > 0)
      playerY--;
     break;
    case 's':
    case 'S':
     if (playerY < 19)
      playerY++;
     break;
    case 'a':
    case 'A':
     if (playerX > 1)
      playerX--;
     break;
    case 'd':
    case 'D':
     if (playerX < 40)
      playerX++;
     break;
    }
   }
  }
 }

 void topUI()
 {
  cout << "Player: " << player.playerName;
  cout << " | Lives: " << player.life;
  cout << " | Crossings: "
    << player.score << endl;
 }

 void bottomUI()
 {
  gotoXY(0, 23);
  cout << "Avoid trucks (#) and water (~). Ride logs (=)." << endl;
 }

 void playMusic(int x)
 {

  if (x == 1)
  {
   PlaySound(TEXT("music/DS_backgroundMusic.wav"),
       NULL,
       SND_FILENAME | SND_ASYNC | SND_LOOP);
  }

  else if (x == 2)
  {
   PlaySound(TEXT("music/DS_gameOver.wav"),
       NULL,
       SND_FILENAME | SND_ASYNC);
  }
  else if (x == 3)
  {
   PlaySound(TEXT("music/DS_menuMusic.wav"),
       NULL,
       SND_FILENAME | SND_ASYNC | SND_LOOP);
  }
 }

 void stopMusic()
 {
  PlaySound(0, 0, 0);
 }

 void gameLoop()
 {
  gotoXY(0, 0);
  playMusic(1);
  system("cls");
  while (player.life > 0)
  {
   spawnObstacle();
   movePlayer();

   if (playerY == 0)
   {
    player.score += 1;
    playerX = 19;
    playerY = 19;
   }

   checkCollision();
   moveObstacles();
   moveWithLog();

   gotoXY(0, 0);

   topUI();
   displayMap();
   bottomUI();

   Sleep(120);
  }
  stopMusic();
  if (player.life == 0)
  {
   system("cls");
   playMusic(2);
   cout << "Better luck next time, " << player.playerName << "!" << endl;
   cout << "Game Over!" << endl;
   system("pause");
   _getch();
   stopMusic();
  }

  ofstream file("leaderboard.txt", ios::app);
  file << player.playerName
    << " "
    << player.score
    << endl;
  file << endl;
  file.close();
 }
};

int main()
{
 srand(time(0));
 Game game;
 game.menu();
 return 0;
}
