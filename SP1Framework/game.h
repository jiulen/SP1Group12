#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <string>

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// struct to store keyboard events
// a small subset of KEY_EVENT_RECORD
struct SKeyEvent
{
    bool keyDown;
    bool keyReleased;
};

// struct to store mouse events
// a small subset of MOUSE_EVENT_RECORD
struct SMouseEvent
{
    COORD mousePosition;
    DWORD buttonState;
    DWORD eventFlags;
};

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP, K_DOWN, K_LEFT, K_RIGHT,
    K_ATK_UP, K_ATK_DOWN, K_ATK_LEFT, K_ATK_RIGHT,
    K_ENTER, K_ESCAPE,
    K_INTERACTIVE, K_INVENTORY,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_GAME,
    S_INVENTORY,
    S_MENU,
    S_END,
    S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    int hp, dmg, def, weight;
    char dir; //U,D,L,R,N
};

void init(void);        // initialize your variables, allocate memory, etc
void getInput(void);        // get input from player
void update(double);   // update the game and the state of the game
void render(void);        // renders the current state of the game to the console
void shutdown(void);        // do clean up, free memory

void splashScreenWait();        // waits for time to pass in splash screen
void updateGame(double);        // gameplay logic
void endScreenWait();           // wait for 5 seconds after end scene then quitting game

void initCSVector(int);
void renderCS();
void keyPressed();              // moves the character, collision detection, physics, etc
void playerAttack();            // player attacks
void processUserInput();        // checks if you should change states or do something else with the game, e.g. pause, exit
void checkPosition();           // checks if player reached the exit
void updateStats();             // update player's char stats
void mouseClicked();       // checks if player left clicked
void clearScreen();             // clears the current screen and draw from scratch 
void renderSplashScreen();      // renders the splash screen
void renderGame();              // renders the game stuff
void initMapVector();           // init map vector
void renderMap();               // renders the map to the buffer first
void createEnemies();           // creates slime objects
void deleteEnemies();           // deletes slime objects
void renderEnemies();           // renders slime and golem
void renderCharacter();         // renders the character into the buffer
void renderHurtCharacter();
void renderPlayerAttack();      // renders the player's attack
void changeDialogue(unsigned);  // change dialogues
void renderDialogues();         // renders the dialogue into the buffer
void enemyMovement();           // moves slime and golem
void enemyMeleeAttack();        // contact damage dealt by slime and golem
void golemRadiusAttack();       // radius damage dealt by golem
void rendergolemRadiusAttack(); // show radius damage of golem
void TouchSpikeTrap();          // damages player when he steps on spike trap
void initInventoryVector();     // init inventory vector
void updateInventory();         // update inventory
void renderInventory();         // renders the inventory into the buffer
void renderItemInfos();         // renders the infos for each item in inventory
void renderFramerate();         // renders debug information, frame rate, elapsed time, etc
void renderEndScreen();         // renders ending and credit screen
void renderToScreen();          // dump the contents of the buffer to the screen, one frame worth of game

// keyboard and mouse input event managers
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent);  // define this function for the console to call when there are keyboard events
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent);      // define this function for the console to call when there are mouse events

void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent);   // handles keyboard events for gameplay 
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent); // handles mouse events for gameplay 


#endif // _GAME_H