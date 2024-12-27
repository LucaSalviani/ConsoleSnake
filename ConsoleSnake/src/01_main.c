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
    int scroll = 0;
    int registryAmount = 0;

    //Windows size, everything will be based on it
    const int consoleWidth = 1064;//1100
    const int consoleHeight = 576;//574

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
   
    windowManagement(410, 240, consoleHeight, consoleWidth);//Manages console position and size
    SetConsoleTitleA("SNAKE");
    disableResize();
    disableMaximize();
    disableQuickEditMode();

    ///////////////CREATES A PLAYER
    Player* playerPtr = NULL;

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

        printf("\x1b[13;1H \x1b[22m  %s %s", ANSI_COLOR_DARK_ORANGE,SNAKE_LOGO);//Title
        printf("\033[35;110H%sCreator:Luca Salviani ",ANSI_COLOR_GREY);//Signature
        printf("\033[35;90H%sConsole_snake: 1.0", ANSI_COLOR_GREY);//Version
        textPositioning(controls_text,27, 3);//Controls
        printf("%s", ANSI_COLOR_DARK_RED);
        textPositioning(game_keys, 70, 1);
        printf("\033[11;75H MOVEMENT     PAUSE GAME");
        
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
    textPositioning(bigBlank, 1, 1);
    printf("%s", ANSI_COLOR_DARK_ORANGE);
    textPositioning(arenaPiece1, 1, 1);
    textPositioning(arenaPiece3, 1, 3);
    textPositioning(arenaPiece2, 1, 34);
    textPositioning(arenaPiece4, 93, 1);

    textPositioning(points_art, 97, 3);//Prints the points text.
    ticks = 0; //Resets game ticks.
    ////////////////GAME
    while (1)
    {
        if (ticks % 300 == 0)
        {
            textPositioning(arenaPiece1, 1, 1);
            textPositioning(arenaPiece3, 1, 3);
            textPositioning(arenaPiece2, 1, 34);
        }
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

        controls(segment, &snakeDirection,&pause,1,91,1,35);

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
    textPositioning(arenaPiece1, 1, 1);
    textPositioning(arenaPiece3, 1, 3);
    textPositioning(arenaPiece2, 1, 34);
    freeSnakesMemory(segmentPtr);
    float factor = 0;
    int gameOverEffect = rand()%2;  //Randomizes which game over effect will be used
    char name[16] = { 0 };
    bool recordSaved = false;
    textPositioning(blank, 95, 16);



    /////////////////GAME OVER
    while (1)
    {
        
        factor = (sin(ticks * 0.03) + 1) / 1.5; // Is the rate at which the movement effect is added for the game over
        breathingEffectToColor(ticks, pink, white); // Adds the breathing effect to the game over 

        // Random Option 1 for the game over Vertical movement one
        if (gameOverEffect == 1)
        {
            textPositioning(game_over, 20, (30 * factor / 2) + 3);
        }
        // Random Option 2 for the game over Horizontal movement one
        else if (gameOverEffect == 0) 
        {
            textPositioning(game_over, (29 * factor) + 3, 10);
        }
        // Asks the user if he/she wants to add a record to the records files
        if (recordSaved == false)
        {
            printf("\033[16;95H\033[38;2;105;105;105mPress enter to submit a score.");
            printf("\033[17;95H%sPLAYER:_______________ SCORE:%4i", ANSI_COLOR_DARK_RED, points);
        }

        /*Checks for record inputs->adds player if input determines so->sorts the player LL made from the players record file earlier in the execution of the program including the new input->saves the LL into the
        players record file->displays the file using a scrolling mechanism->sets the recordSaved variable to true so that the user cant save more than 1 record*/

        if (GetAsyncKeyState(VK_RETURN) & 0x8000 && recordSaved == false)
        {
            readInputWithLimit(name,15);
            addPlayer(&playerPtr, name, points);
            mergeSort(&playerPtr);
            saveRecord(recordsTxt, playerPtr,&registryAmount);                  
            displayRecords(recordsTxt,&scroll,registryAmount,ticks);  
            recordSaved = true;
        }

        // Constant display after saving a record
        if (recordSaved == true)
        {
            displayRecords(recordsTxt,&scroll,registryAmount,ticks);
        }

        //Augments ticks
        ticks++;

        //Sleep function so that the program dosent execute on constant time and the user has aa nicer experience/computer dosent explode
        Sleep(10);
    }
    return 0;
}
