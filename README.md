# CSDC102---FINAL-PROJECT
Road Crossing Challenge


- This is a simple terminal-based road survival game using C++.\
The game simulate a player crossing a road filled with moving obstacles and also a river.

# Table of contents
* [Documentation](#Documentation)
* [Installation](#Installation)
* [Workflow](#Workflow)

### Documentation
- One-page report
![Report](https://github.com/aoduca-art/CSDC102---FINAL-PROJECT/blob/main/Documentation/Documentation.pdf)
- Titlescreen
![Titlescreen](https://github.com/aoduca-art/CSDC102---FINAL-PROJECT/blob/main/Documentation/titlescreen.png)
- Gameplay
![Gameplay](https://github.com/aoduca-art/CSDC102---FINAL-PROJECT/blob/main/Documentation/gameplay.mp4)
- Leaderboard
![Leaderboard](https://github.com/aoduca-art/CSDC102---FINAL-PROJECT/blob/main/Documentation/leaderboard.png)
## Installation 
1. Options for install:  
 A.  Click the green code, [download ZIP](https://github.com/aoduca-art/CSDC102---FINAL-PROJECT/archive/refs/heads/main.zip) and extract \
 B. Use [git clone](https://git-scm.com/) and type:
```
git https://github.com/aoduca-art/CSDC102---FINAL-PROJECT.git
```

2. Open roadCrossing.cpp file and open terminal, build with:
> [!WARNING]
> The last line "-lwinmm" is important for the code to work.
```
g++ roadCrossing.cpp -o game.exe -lwinmm
```

3. Double click or open "game.exe"

---
# Workflow
- added titleScreen();
- removed titleScreen();
- replace with showMenu();
- made Current.cpp to roadCrossing.cpp
---
### Done 
\- 5/15
- [x] top 5 leaderboard
- [x] fix arrow movements
- [x] improve titleScreen()
--- 
### Done 
\- 5/14

- [x] Generating Obstacle 
- [x] cleaner refresh rate 
- [x] arrow keys movement (tho using ASWD and ARROW keys give you +2 movement)
- [x] background music,
 
> Compile with `"g++ roadCrossing.cpp -o game.exe -lwinmm"` -lwimm is the most important

---
### Currently working
\- 5/12 - 5/13

- [x] made struct player 
- [x] made class game 
  - void start()
  - void end()
  - void menu()
  - void leaderboard()
  - void mapSetup()
  - void displayMap()
  - void movePlayer()
  - void gameLoop()
- 5/14
  - void gotoXY();
  - void playMusic()
  - void stopMusic()
  - void topUI()
  - void bottomUI()
  - void checkCollision()
  - bool isPlayeronLog()
  - void moveWithLog()
  - void clearObstacles()
  - void topUI()
  - void Obstacles()
  - remade displayMap()
  - void moveObstacles()
- 5/15
  - void showMenu();
  - bool landOccupied()
  - void spawnObstacle()
