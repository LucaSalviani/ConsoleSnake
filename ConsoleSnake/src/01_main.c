#include "snake.h"
#include "game.h"
#include "utils.h"
#include "art.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>


int main() {
    // variables initialization
    int points = 0;
    int snakeSize = 0;
    int snakeDirection = 0;
    int ticks = 0;
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
    srand(time(NULL));

    //Manages console position and size
    windowManagement(710, 290, consoleWidth, consoleHeight);

    //Hides cursor
    printf("\033[?25l");
    //forcedPause(&pause);

    //CREATES SNAKES HEAD SEGMENT AND A POINTER TO IT:
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
    
    while (gameStart())
    {
        printf("\x1b[10;0H \x1b[22m %s  %s", ANSI_COLOR_DARK_ORANGE, SNAKE_LOGO);
        printf("\x1b[20;55H Hold the arrows to play %s", ANSI_RESET_STYLE);
        Sleep(300);
        printf("\x1b[1G \x1b[0K");
        Sleep(300);
        get_console_font_size(&FontSizeY,&FontSizeX);
    }


    printf("\x1b[H %s %s", ANSI_COLOR_DARK_ORANGE, ARENA2);

    textPositioning(points_art, 97, 2);

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

        //Clears snake trail
        printf("\x1b[%d;%dH  ", y_buffer, x_buffer);

        controls(segment, &snakeDirection,&pause);

        georginasCookies(&segment,&segmentPtr, &x_food, &y_food, &points,&snakeSize, x_buffer, y_buffer,snakeDirection);

        updateSnake(segmentPtr);
  
        drawSnake(segmentPtr);

        // Controls how often game ticks happen
        Sleep(35);

        //Gives 5 ticks head start before activating collision so that the snake can unroll itself
        if (ticks > 6)
        {
            if (colision(segmentPtr, segment, snakeSize))
            {
                break;
            }
        }

        //Counts game ticks
        ticks++;
        textBreathEfect(ticks);
    
        //Prints food
        printf("\x1b[%d;%dHG", y_food, x_food);

    }

    //Need to change this
    printf("You loose!");
    freeSnakesMemory(segmentPtr);
    while (1)
    {

    }
    return 0;
}
