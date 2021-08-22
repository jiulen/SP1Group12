// This is the main file for the game logic and function
#include "game.h"
#include "Slime.h"
#include "Entity.h"
#include "Framework\console.h"
#include "Inventory.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>      /*  NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  

int test1, test2; // ignore this test is for slime stuff

double  g_dDeltaTime;
double  g_dGameTime; //time spent on levels
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;
Slime slimes;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state
int level_no = 1; //level number, increases when go next level
bool E_KeyPressed = false;

// Console object
Console g_Console(120, 50, "Temple Escape");
int GUI_height = 10;

// Arrays
std::vector<std::vector<std::string>> mapVector;       // Map array for all maps
std::vector<std::vector<std::string>> inventoryVector; // Inventory array
Entity* ePtr[10] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };


// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void) {
    srand((unsigned int) time(NULL));
    // Set precision for floating point output
    g_dGameTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;
    //change values to change where player spawns
    g_sChar.m_cLocation.X = 10;
    g_sChar.m_cLocation.Y = 37;
    g_sChar.hp = 10;
    g_sChar.dmg = 1;
    g_sChar.def = 0;
    g_sChar.weight = 1;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: gameplayKBHandler(keyboardEvent); break; // don't handle anything for the splash screen
    case S_GAME: gameplayKBHandler(keyboardEvent); break; // handle gameplay keyboard event
    case S_END: gameplayKBHandler(keyboardEvent); break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: break; // don't handle anything for the splash screen
    case S_GAME: gameplayMouseHandler(mouseEvent); break; // handle gameplay mouse event
    case S_END: break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case 0x57: key = K_UP; break;
    case 0x53: key = K_DOWN; break;
    case 0x41: key = K_LEFT; break;
    case 0x44: key = K_RIGHT; break;
    case 0x45: key = K_INVENTORY; break;
    case VK_RETURN: key = K_ENTER; break;
    case VK_ESCAPE: key = K_ESCAPE; break;
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dDeltaTime = dt;
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: splashScreenWait(); break; // game logic for the splash screen
    case S_GAME:
        if (E_KeyPressed == false) {
            g_dGameTime += dt; 
        } 
        updateGame(); 
        break; // gameplay logic when we are in the game
    case S_END: endScreenWait(); break;
    }
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_skKeyEvent[K_ENTER].keyReleased) { // wait for user to press enter to switch to game mode, else do nothing
        g_eGameState = S_GAME;
        test1 = (rand() % 60 * 2);
        test2 = (rand() % 40);
        
       
    }
    processUserInput();
}

void updateGame()       // gameplay logic
{
    keyPressed();       // moves the character, collision detection, physics, etc
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
                        // sound can be played here too.
    checkExitReached(); // checks if player reached the exit
    
}

void endScreenWait()
{
    processUserInput();
}

void keyPressed()
{
    // Updating the location of the character based on the key release
    // 
    // [NOTE]: PLAYER CAN ONLY MOVE AFTER THE MAP 1 ARRAY IS DONE LOADING
    if (E_KeyPressed == false)
    {
        if ((g_skKeyEvent[K_UP].keyDown) && (g_sChar.m_cLocation.Y > 0) && (mapVector.size() == 2400) && ((mapVector[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X / 2] == "0") || (mapVector[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X / 2] == "7") || (mapVector[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X / 2] == "8")))
        {
            g_sChar.m_cLocation.Y--;
        }
        if ((g_skKeyEvent[K_LEFT].keyDown) && (g_sChar.m_cLocation.X > 1) && (mapVector.size() == 2400) && ((mapVector[g_sChar.m_cLocation.Y][(g_sChar.m_cLocation.X / 2) - 1] == "0") || (mapVector[g_sChar.m_cLocation.Y][(g_sChar.m_cLocation.X / 2) - 1] == "7") || (mapVector[g_sChar.m_cLocation.Y][(g_sChar.m_cLocation.X / 2) - 1] == "8")))
        {
            g_sChar.m_cLocation.X -= 2;
        }
        if ((g_skKeyEvent[K_DOWN].keyDown) && (g_sChar.m_cLocation.Y < (g_Console.getConsoleSize().Y - 1 - GUI_height)) && (mapVector.size() == 2400) && ((mapVector[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X / 2] == "0") || (mapVector[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X / 2] == "7") || (mapVector[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X / 2] == "8")))
        {
            g_sChar.m_cLocation.Y++;
        }
        if ((g_skKeyEvent[K_RIGHT].keyDown) && (g_sChar.m_cLocation.X < (g_Console.getConsoleSize().X - 2)) && (mapVector.size() == 2400) && ((mapVector[g_sChar.m_cLocation.Y][(g_sChar.m_cLocation.X / 2) + 1] == "0") || (mapVector[g_sChar.m_cLocation.Y][(g_sChar.m_cLocation.X / 2) + 1] == "7") || (mapVector[g_sChar.m_cLocation.Y][(g_sChar.m_cLocation.X / 2) + 1] == "8")))
        {
            g_sChar.m_cLocation.X += 2;
        }
        if (g_skKeyEvent[K_INTERACTIVE].keyReleased) // we don't want player to spam
        {

        }
    }
    if (g_skKeyEvent[K_INVENTORY].keyReleased) // we don't want player to spam
    {
        if (E_KeyPressed == false) { E_KeyPressed = true; }
        else { E_KeyPressed = false; }
    }
}

void processUserInput()
{
    if (g_skKeyEvent[K_ESCAPE].keyReleased) { // quits the game if player hits the escape key
        g_bQuitGame = true;
    }
}

void checkExitReached()
{
    if ((mapVector.size() == 2400) && (mapVector[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X / 2] == "7"))
    {
        if (level_no < 5) { mapVector.clear(); level_no++; }

        switch (level_no)
        {
        case 2: g_sChar.m_cLocation.X = 6; g_sChar.m_cLocation.Y = 36; break;
        case 3: g_sChar.m_cLocation.X = 2; g_sChar.m_cLocation.Y = 2; break;
        case 4: g_sChar.m_cLocation.X = 2; g_sChar.m_cLocation.Y = 20; break;
        case 5: g_sChar.m_cLocation.X = 2; g_sChar.m_cLocation.Y = 21; break;
        }
    }
    if ((mapVector.size() == 2400) && (mapVector[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X / 2] == "8"))
    {
        // Ending scene
        g_eGameState = S_END;
    }
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render() {
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen(); break;
    case S_GAME: renderFramerate(); renderGame(); break;
    case S_END: renderEndScreen(); break;
    }
    //renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen() {
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0xF0);
}

void menuScreen(COORD& c)
{
    std::ostringstream title;
    title << char(244) << "  " << char(205) << char(205) << char(203) << char(205) << char(205) << " " << char(201) << char(205) << char(205) << char(205) << char(205) << " " << char(201) << char(205) << char(205) << char(203) << char(205) << char(205) << char(187) << " " << char(201) << char(205) << char(205) << char(205) << char(187) << " " << char(210) << "     " << char(201) << char(205) << char(205) << char(205) << char(205) << "  " << char(244);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str(""); c.Y += 1;
    title << char(245) << "    " << char(186) << "   " << char(186) << "     " << char(186) << "  " << char(208) << "  " << char(186) << " " << char(186) << "   " << char(186) << " " << char(186) << "     " << char(186) << "      " << char(245);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str(""); c.Y += 1;
    title << char(244) << "    " << char(186) << "   " << char(204) << char(205) << char(205) << char(205) << char(205) << " " << char(186) << "     " << char(186) << " " << char(204) << char(205) << char(205) << char(205) << char(188) << " " << char(186) << "     " << char(204) << char(205) << char(205) << char(205) << char(205) << "  " << char(244);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str(""); c.Y += 1;
    title << char(245) << "    " << char(186) << "   " << char(186) << "     " << char(186) << "     " << char(186) << " " << char(186) << "     " << char(186) << "     " << char(186) << "      " << char(245);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str(""); c.Y += 1;
    title << char(244) << "    " << char(208) << "   " << char(200) << char(205) << char(205) << char(205) << char(205) << " " << char(208) << "     " << char(208) << " " << char(208) << "     " << char(200) << char(205) << char(205) << char(205) << char(181) << " " << char(200) << char(205) << char(205) << char(205) << char(205) << "  " << char(244);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str(""); c.Y += 1;
    title << char(245) << "   " << char(201) << char(205) << char(205) << char(205) << char(205) << " " << char(201) << char(205) << char(205) << char(205) << char(181) << " " << char(201) << char(205) << char(205) << char(205) << char(181) << " " << char(201) << char(205) << char(205) << char(205) << char(187) << " " << char(201) << char(205) << char(205) << char(205) << char(187) << " " << char(201) << char(205) << char(205) << char(205) << char(205) << "   " << char(245);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str(""); c.Y += 1;
    title << char(244) << "   " << char(186) << "     " << char(186) << "     " << char(186) << "     " << char(186) << "   " << char(186) << " " << char(186) << "   " << char(186) << " " << char(186) << "       " << char(244);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str(""); c.Y += 1;
    title << char(245) << "   " << char(204) << char(205) << char(205) << char(205) << char(205) << " " << char(200) << char(205) << char(205) << char(205) << char(187) << " " << char(186) << "     " << char(204) << char(205) << char(205) << char(205) << char(185) << " " << char(204) << char(205) << char(205) << char(205) << char(188) << " " << char(204) << char(205) << char(205) << char(205) << char(205) << "   " << char(245);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str(""); c.Y += 1;
    title << char(244) << "   " << char(186) << "         " << char(186) << " " << char(186) << "     " << char(186) << "   " << char(186) << " " << char(186) << "     " << char(186) << "       " << char(244);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str(""); c.Y += 1;
    title << char(245) << "   " << char(200) << char(205) << char(205) << char(205) << char(205) << " " << char(198) << char(205) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(205) << char(205) << char(188) << " " << char(208) << "   " << char(208) << " " << char(208) << "     " << char(200) << char(205) << char(205) << char(205) << char(205) << "   " << char(245);
    g_Console.writeToBuffer(c, title.str(), 0xF0); title.str("");
}

void renderSplashScreen() {             // renders the splash screen aka menu screen
    COORD c = g_Console.getConsoleSize();
    c.Y = 11; c.X = c.X / 2 - 21;
    menuScreen(c);
    c = g_Console.getConsoleSize();
    c.Y = 40;
    c.X = c.X / 2 - 11;
    g_Console.writeToBuffer(c, "Press 'Enter' to start", 0xF0);
    c.Y++;
    c.X = g_Console.getConsoleSize().X / 2 - 16;
    g_Console.writeToBuffer(c, "Press 'W, A, S, D' to move around", 0xF0);
    c.Y++;
    c.X = g_Console.getConsoleSize().X / 2 - 14;
    g_Console.writeToBuffer(c, "Press 'Left Click' to attack", 0xF0);
    c.Y++;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0xF0);
}

void renderGame() {
    if (mapVector.size() < 2400) { initMapVector(); }; renderMap(); // init map vector, then renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
    renderSlime();
    if (E_KeyPressed == true) { if (inventoryVector.size() < 1008) { initInventoryVector(); }; updateInventory(); renderInventory();  } // init inventory vector, after that update inventory (health, items etc), then render inventory (This is to ensure that players do not see the change when they press 'e' key)
}

void initMapVector()
{
    std::ifstream map;
    switch (level_no)
    {
    case 1: map = std::ifstream("Map1.csv"); break; //opens map
    case 2: map = std::ifstream("Map2.csv"); break; //opens map
    case 3: map = std::ifstream("Map3.csv"); break; //opens map
    case 4: map = std::ifstream("Map4.csv"); break; //opens map
    case 5: map = std::ifstream("Map5.csv"); break; //opens map
    }
    std::string row;

    while (std::getline(map, row))
    {
        std::stringstream rowStream(row);
        std::string(cell);
        std::vector<std::string> rowVector;

        while (std::getline(rowStream, cell, ',')) { rowVector.push_back(cell); }

        mapVector.push_back(rowVector);
    }

    map.close();
}

void renderMap() {
    for (unsigned y = 0; y < 40; y++)
    {
        for (unsigned x = 0; x < 60; x++)
        {
            WORD map_colour = 0x00;
            switch (stoi(mapVector[y][x]))
            {
            case 0: map_colour = 0x60; break; //path
            case 1: map_colour = 0x00; break; //wall            
            case 2: map_colour = 0x50; break; //dead body     
            case 3: map_colour = 0xD0; break; //special dead body  
            case 4: map_colour = 0xE0; break; //chest
            case 5: map_colour = 0x80; break; //fake chest    
            case 6: map_colour = 0x30; break; //prisoner
            case 7: map_colour = 0x10; break; //exit     
            }
            g_Console.writeToBuffer(x * 2, y, "  ", map_colour);
        }
    }
}

void renderCharacter() {
    // Draw the location of the character
    std::ostringstream playerChar;
    playerChar << static_cast<char>(1) << static_cast<char>(1);
    g_Console.writeToBuffer(g_sChar.m_cLocation, playerChar.str(), 0x01);
}

void createSlimeObj() { ePtr[0] = new Slime; } // The creation of slime object MUST be inside a FUNCTION

void renderSlime() {
    // draw location of slimes
    createSlimeObj();
    std::ostringstream slimeChar;
    slimeChar << static_cast<char>(5) << static_cast<char>(5);
    ePtr[0]->EntityPos.setPosition(test1, test2);
    if (level_no == 1) {
         g_Console.writeToBuffer(ePtr[0]->get_posX(), ePtr[0]->get_posY(), slimeChar.str(), 0xFD);
    }
}

void initInventoryVector()
{
    std::ifstream inventory("Inventory.csv");
    std::string row;

    while (std::getline(inventory, row))
    {
        std::stringstream rowStream(row);
        std::string(cell);
        std::vector<std::string> rowVector;

        while (std::getline(rowStream, cell, ',')) { rowVector.push_back(cell); }

        inventoryVector.push_back(rowVector);
    }

    inventory.close();
}

void updateInventoryHealth()
{
    g_sChar.hp = 4; // for testing
    for (unsigned r = 3; r < 8; r++)
    {
        for (unsigned c = 25; c < 31; c++)
        {
            switch (g_sChar.hp)
            {
            case 0: ( (c < 29) ? ( ((c == 26 || c == 27) && (r >= 4 && r <= 6)) ? (inventoryVector[r][c] = "1") : (inventoryVector[r][c] = "0") ) : (inventoryVector[r][c] = "1") ); break;
            case 1: ( (c == 25) ? (inventoryVector[r][c] = "0") : (inventoryVector[r][c] = "1") ); break;
            case 2: ( (c < 28) ? ( ((r == 4 && c != 27) || (r == 6 && c != 25)) ? (inventoryVector[r][c] = "1") : (inventoryVector[r][c] = "0") ) : (inventoryVector[r][c] = "1") ); break;
            case 3: ( (c < 28) ? ( (((r == 4 || r == 6) && c != 27 )) ? (inventoryVector[r][c] = "1") : (inventoryVector[r][c] = "0") ) : (inventoryVector[r][c] = "1") ); break;
            case 4: ( (c < 29) ? ( (((c == 25 && r <= 5) || (c == 27) || ((c == 26 || c == 28) && r == 5))) ? (inventoryVector[r][c] = "0") : (inventoryVector[r][c] = "1") ) : (inventoryVector[r][c] = "1") ); break;
            case 5: break;
            case 6: break;
            case 7: break;
            case 8: break;
            case 9: break;
            case 10: break;
            }
        }
    }
}

void updateInventoryItems()
{

}

void updateInventory()
{
    updateInventoryHealth();
    updateInventoryItems();
}

void renderInventory()
{
    for (unsigned y = 0; y < 24; y++)
    {
        for (unsigned x = 0; x < 42; x++)
        {
            WORD inventory_colour = 0x00;
            switch (stoi(inventoryVector[y][x]))
            {
            case 0: inventory_colour = 0x00; break;  // boarder
            case 1: inventory_colour = 0xF0; break;  // gui background
            case 2: inventory_colour = 0x40; break;  // heart icon
            case 3: inventory_colour = 0x60; break;  // char hair  
            case 4: inventory_colour = 0x80; break;  // char face     
            case 5: inventory_colour = 0xB0; break;  // char upper body
            case 6: inventory_colour = 0x30; break;  // char lower body
            case 7: inventory_colour = 0x70; break;  // char hand
            case 8: inventory_colour = 0xA0; break;  // items background
            case 9: inventory_colour = 0x80; break;  // default icon background
            case 10: inventory_colour = 0x70; break; // default center icon
            case 11: inventory_colour = 0x60; break; // sword handle
            case 12: inventory_colour = 0x70; break; // sword part
            case 13: inventory_colour = 0x20; break; // chestplate
            case 14: inventory_colour = 0x30; break; // boot
            case 15: inventory_colour = 0xD0; break; // potion
            }
            g_Console.writeToBuffer((x + 9) * 2, y + 8, "  ", inventory_colour);
        }
    }
}

void renderEndScreen() {
    COORD c;
    c.X = 1;
    c.Y = 1;
    g_Console.writeToBuffer(c, "Created by Group 12: Winston, Jun Hou, Jiu Len and Darius", 0xF0);
    c.Y += 1;
    g_Console.writeToBuffer(c, "YOU WIN!!!", 0xF0);
    //add more things later? -> dmg taken, dmg dealt, dmg healed, kills, time taken
}

void renderFramerate() {
    COORD c;
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << 1.0 / g_dDeltaTime << " fps";         // displays the framerate
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 40;
    g_Console.writeToBuffer(c, ss.str(), 0xF0);
    ss.str("");
    ss << g_dGameTime << "secs";             // displays the elapsed time
    c.X = 0;
    c.Y = 40;
    g_Console.writeToBuffer(c, ss.str(), 0xF0);
    std::ostringstream hb;              // displays the player's health
    hb << "HP: " << std::string(g_sChar.hp, (char)3); // (char)3 is heart symbol
    c.X = 10;
    c.Y = 40;
    g_Console.writeToBuffer(c, hb.str(), 0xF4); //white background, red text
}

void renderToScreen() {
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

// this is an example of how you would use the input events
void renderInputEvents() {
    // keyboard events
    COORD startPos = { 50, 2 };
    std::ostringstream ss;
    std::string key;
    for (unsigned i = 0; i < K_COUNT; ++i) {
        ss.str("");
        switch (i) {
        case K_UP: key = "UP"; break;
        case K_DOWN: key = "DOWN"; break;
        case K_LEFT: key = "LEFT"; break;
        case K_RIGHT: key = "RIGHT"; break;
        default: continue;
        }
        /*if (g_skKeyEvent[i].keyDown)
            ss << key << " pressed";
        else if (g_skKeyEvent[i].keyReleased)
            ss << key << " released";
        else
            ss << key << " not pressed";
        */
        COORD c = { startPos.X, startPos.Y + i };
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }

    // mouse events    
    /*ss.str("");
    ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
    ss.str("");
    switch (g_mouseEvent.eventFlags) {
    case 0:
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            ss.str("Left Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
        }
        else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
        {
            ss.str("Right Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
        }
        else
        {
            ss.str("Some Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
        }
        break;
    case DOUBLE_CLICK:
        ss.str("Double Clicked");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
        break;
    case MOUSE_WHEELED:
        if (g_mouseEvent.buttonState & 0xFF000000)
           ss.str("Mouse wheeled down");
        else
           ss.str("Mouse wheeled up");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
        break;
    default:
        break;
    }*/
}