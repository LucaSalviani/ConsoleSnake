#include "snake.h"
#include "game.h"
#include "utils.h"
#include "art.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>


int main() {
    ///////////// VARIABLES INITILAZATION
    int points = 0;
    int snakeSize = 0;
    int snakeDirection = 0;
    int ticks = 0;
    int gameTalkerFase = 0;
    int talkerFaseBuffer = 0;
    int gameTalkerMap = 0;
    int internalTimer = 0;
    int randText = rand() % 3;

    //Windows size, everything will be based on it
    const int consoleWidth = 1100;
    const int consoleHeight = 600;

    //Font size, set them up at the standard but will later be checked by a handle
    int FontSizeX = 8;
    int FontSizeY = 16;

    //A position buffer that will go behind the snakes head
    int x_buffer = 0;
    int y_buffer = 0;

    // Random food position
    int x_food = randomBetween(3, 47);
    int y_food = randomBetween(3, 27);
    bool pause = false;

    //Starts random seed
    initializeRandomSeed();

    printf("\033[?25l");//Hides cursor
    windowManagement(710, 290, consoleWidth, consoleHeight);//Manages console position and size



    ///////////////CREATES A PLAYER

    Player* playerPtr = NULL;
    //Player* player = malloc(sizeof(Player));
    //if (player == NULL)
    //{
    //    printf("Theres no space in memory to run the game");
    //    return 1;
    //}
    //playerPtr = player; // Stores the head of the list in a ptr

    char* recordsTxt = "records.txt";

    readRecord(recordsTxt,&playerPtr);//Reads the players records base

    ////////////CREATES SNAKES HEAD SEGMENT AND A POINTER TO IT:
    snake* segmentPtr = NULL;
    snake* segment = malloc(sizeof(snake));
    if (segment == NULL)
    {
        printf("Theres no space in memory to run the game");
        return 1;
    }
      //Declares the position of the head of the snake 
    segment->x_pos = 20;
    segment->y_pos = 20;
    segment->next = NULL;
      //We get a head pointer
    segmentPtr = segment;
    snakeSize++;
    


    /////////////GAME FRONT PAGE
    while (gameStart(&snakeDirection))
    {
        printf("\x1b[13;0H \x1b[22m  %s %s", ANSI_COLOR_DARK_ORANGE,SNAKE_LOGO);//Title
        printf("\033[0;109H\033[38;2;105;105;105m |_ Luca Salviani _|");//Signature

        //Controls
        textPositioning(controls_text,7, 3);
        textPositioning(game_keys, 50, 0);
        printf("\033[11;56H MOVEMENT     PAUSE GAME");
        
        printf("\x1b[23;55H%s Hold the arrows to play %s",ANSI_COLOR_DARK_ORANGE,ANSI_RESET_STYLE);//Start buttons
        Sleep(300);
        printf("\x1b[1G \x1b[0K");//Restarts cursor position
        Sleep(300);

        //This gives us the font size of the console, good for debugging it actives by pressing F.
        get_console_font_size(&FontSizeY,&FontSizeX);
        ticks++;
    }



   ///////////////GAME SETUP
    titleErasser();
    printf("\x1b[H %s %s", ANSI_COLOR_DARK_ORANGE, ARENA2);//Prints the arena.
    textPositioning(points_art, 97, 2);//Prints the points text.
    ticks = 0; //Resets game ticks.

    ////////////////GAME
    while (1)
    {
        //The buffer follows the snakes head
        x_buffer = segmentPtr->x_pos;
        y_buffer = segmentPtr->y_pos;

        //Creates 4 snake segments at the beggining of the run automatically, you can change the snakes starting size by changing the while condition 
        while (snakeSize <= 4)
        {
            addSegment(&segmentPtr, x_buffer, y_buffer);
            snakeSize++;
        }

        printf("\x1b[%d;%dH  ", y_buffer, x_buffer);        //Clears snake trail

        controls(segment, &snakeDirection,&pause,0,91,0,34);

        georginasCookies(&segment,&segmentPtr, &x_food, &y_food, &points,&snakeSize, x_buffer, y_buffer,snakeDirection);

        // GAME TALKER :
        if (gameTalkerMap == 1 || gameTalkerFase > talkerFaseBuffer) // activates when map is eaten or when gameTalkerFase changes
        {
            internalTimer++;
        }
        if (internalTimer == 100) 
        {
            talkerFaseBuffer = gameTalkerFase;
        }
          gameTalker(segment, points, ticks, &gameTalkerFase, &gameTalkerMap, &internalTimer,&randText);


        updateSnake(segmentPtr);
  
        drawSnake(segmentPtr,false);

        Sleep(35);  // Controls how often game ticks happen

        //Gives 5 ticks head start before activating collision so that the snake can unroll itself
        if (ticks > 6)
        {
            if (colision(segmentPtr, segment, snakeSize))
            {
                break;
            }
        }
        ticks++;    //Counts game ticks

        textBreathEfect(ticks);// Gives the food the Breathe colors effect
        
        printf("\x1b[%d;%dHG", y_food, x_food); //Prints food


    }
   


    ///////////////GAME OVER SETUP
    printf("\x1b[%d;%dH ", y_food, x_food);     //Deletes the food
    drawSnake(segmentPtr, true);    //Deletes the snake by giving it a true value
    freeSnakesMemory(segmentPtr);
    float factor = 0;
    int gameOverEffect = rand()%2;  //Randomizes which game over effect will be used
    char name[16] = { 0 };
    bool recordSaved = false;
    textPositioning(blank, 95, 16);
    /////////////////GAME OVER
    while (1)
    {
        factor = (sin(ticks * 0.03) + 1) / 1.5;
        breathingEffectToColor(ticks, pink, white);
        if (gameOverEffect == 1)
        {
            textPositioning(game_over, 20, (30 * factor / 2) + 3);
        }
        else if (gameOverEffect == 0)
        {
            textPositioning(game_over, (29 * factor) + 2, 10);
        }
        ticks++;
        printf("\033[16;95H\033[38;2;105;105;105mPress enter to submit a score.");
        printf("\033[17;95H%sPLAYER:_______________ SCORE:%4i", ANSI_COLOR_DARK_RED,points);


        if (GetAsyncKeyState(VK_RETURN) & 0x8000 && recordSaved == false)
        {
            readInputWithLimit(name,15);
            addPlayer(&playerPtr, name, points);
            mergeSort(&playerPtr);
            saveRecord(recordsTxt, playerPtr);                  
            displayRecords(recordsTxt);  
            recordSaved = true;
        }
        Sleep(10);
    }
    return 0;
}
