#include "game.h"
#include "utils.h"
#include "snake.h"
#include "art.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

//Food function (The snake eats my gf cookies ;])
void georginasCookies(snake** segment,snake** segmentPtr, int* x_food, int* y_food, int* points,int* snakeSize, int x_buffer, int y_buffer, int snakesDirection)
{
    //IMPORTANT this if statemnt has 2 parts the second part of the OR || is because i made my snake aeshtetically not common, it has 2 pieces to itself so when vertical needs to compare two spaces
    if (((*segment)->x_pos == *x_food && (*segment)->y_pos == *y_food) || ((snakesDirection == 3 || snakesDirection == 4) && (((*segment)->x_pos+1) == *x_food && (*segment)->y_pos == *y_food)))
    {
        (*points)++;
        pointsDisplay(*points, 130, 10, numbers);
        (*snakeSize)++;
        ////Adds a snake segment

        addSegment(segmentPtr, x_buffer, y_buffer);

        //Randomizes foods location on screen
        *x_food = randomBetween(3, 90);
        *y_food = randomBetween(3, 30);
    }
}



//Waits for the first key to be pressed
bool gameStart(int* snakeDirection)
{
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
    {
        return false;
        *snakeDirection = 1;
    }
    else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)) 
    {
        *snakeDirection = 2;
        return false;
    }
    else if ((GetAsyncKeyState(VK_UP) & 0x8000))
    {
        *snakeDirection = 3;
        return false;
    }
    else if ((GetAsyncKeyState(VK_DOWN) & 0x8000)) 
    {
        *snakeDirection = 4;
        return false;
    }
   

    return true;
}
   
//Forced pause, its useful if you want to check for memory leaks
void forcedPause(bool* pause)
{
    *pause = true;
    while (*pause == true)
    {

        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            *pause = false;
            Sleep(100);
        }
    }
}

void pointsDisplay(int points,int xPos,int yPos,const char ** text[])
{
    int placeValue;
    int currentValue;
    int cycles = 0;
    int divisor = 10;
    do 
    {
        cycles++;
        placeValue = points / divisor;
        printf("%s",ANSI_COLOR_DARK_ORANGE);
        currentValue = round((points % divisor) / (divisor/10));
        textPositioning(text[currentValue], xPos-(7*cycles), yPos);
         divisor *= 10;
    } while (placeValue > 0);
}


// Controls, this includes : Arrow keys movement, game closing via Esc, and game pause via Spacebar.
void controls(snake* segment, int* direction, bool* pause,int xLeftBoundary,int xRightBoundary,int yUpBoundary,int yDownBoundary)
{
    //Arrow keys are observed and whenever one is pressed it changes x and y coordinates of the snakes head accordingly
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000)) {
        *direction = 1;
    }
    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
    {
        *direction = 2;
    }
    if ((GetAsyncKeyState(VK_UP) & 0x8000))
    {
        *direction = 3;
    }
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000))
    {
        *direction = 4;
    }

    //perpetual movement
    if (*direction == 1)
    {
        segment->x_pos--;
        if (segment->x_pos < xLeftBoundary)
        {
            segment->x_pos = xLeftBoundary;
        }
    }
    else if (*direction == 2)
    {
        segment->x_pos++;
        if (segment->x_pos > xRightBoundary)
        {
            segment->x_pos = xRightBoundary;
        }
    }
    else if (*direction == 3)
    {
        segment->y_pos--;
        if (segment->y_pos < yUpBoundary)
        {
            segment->y_pos = yUpBoundary;
        }
    }
    else if (*direction == 4)
    {
        segment->y_pos++;
        if (segment->y_pos > yDownBoundary)
        {
            segment->y_pos = yDownBoundary;
        }
    }

    // Press esc to exit the program
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        printf("Esc pressed, exiting program...");
        exit(0);
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        *pause = true;
        Sleep(100);
    }
    while (*pause == true)
    {

        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            *pause = false;
            Sleep(100);
        }
    }
}



/*
void gameTalker(snake* segment,int points,int ticks,int* gameTalkerFase,int* gameTalkerMap,int* internalTimer,int *randText) 
{
    if ((segment->x_pos < 2 || segment->y_pos > 32 || segment->y_pos < 3) && *gameTalkerMap == 0) //MAP EATEN
    {
        if (*randText == 0)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(ouch, 95, 16);
            *gameTalkerMap = 1;

        }
        else if (*randText == 1)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(ouch_variant1, 95, 16);
            *gameTalkerMap = 1;
        }
        else if (*randText == 2)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(ouch_variant2, 95, 16);
            *gameTalkerMap = 1;
        }
    }
    if (points == 2 && *gameTalkerFase == 0 ) // TALKERS FIRST FASE 10 p
    {
        if (*randText == 0)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(huh, 95, 16);
            *gameTalkerFase = 1;
        }
        else if (*randText == 1)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(huh_variant1, 95, 16);
            *gameTalkerFase = 1;
        }
        else if (*randText == 2)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(huh_variant2, 95, 16);
            *gameTalkerFase = 1;
        }
    }
    else if (points == 5 && *gameTalkerFase == 1)// TALKERS 2nd FASE 25 p
    {
        if (*randText == 0)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(not_that_bad, 95, 16);
            *gameTalkerFase = 2;
        }
        else if (*randText == 1)
        {

            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(not_that_bad_variant1, 95, 16);
            *gameTalkerFase = 2;
        }
        else if (*randText == 2)
        {

            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(not_that_bad_variant2, 95, 16);
            *gameTalkerFase = 2;
        }
        
    }
    else if (points == 7 && *gameTalkerFase == 2)  // TALKERS 3rd FASE 50 p
    {
        if (*randText == 0)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(impressed, 95, 16);
            *gameTalkerFase = 3;
        }
        else if (*randText == 1)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(impressed_1, 95, 16);
            *gameTalkerFase = 3;
        }
        else if (*randText == 2)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(impressed_cs50, 95, 16);
            *gameTalkerFase = 3;
        }

    }
    else if (points == 10 && *gameTalkerFase == 3) // TALKERS 4th FASE 95 p
    {

        if (*randText == 0)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(almost_there_comic_1, 95, 16);
            *gameTalkerFase = 4;
        }
        else if (*randText == 1)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(almost_there_comic_2, 95, 16);
            *gameTalkerFase = 4;
        }
        else if (*randText == 2)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            textPositioning(almost_there_comic_3, 95, 16);
            *gameTalkerFase = 4;
        }
    }
    else if ((points == 12 && *gameTalkerFase == 4) || (*gameTalkerFase >= 5 && *gameTalkerFase <= 18)) // TALKERS 5th FASE 100 p
    {

        if (*randText == 0)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            if (*gameTalkerFase == 4) {
                textPositioning(worm1, 95, 16);
                *gameTalkerFase = 5;
            }
            else if (*gameTalkerFase == 6)
            {
                textPositioning(worm2, 95, 16);
            }
            else if (*gameTalkerFase == 7)
            {
                textPositioning(worm3, 95, 16);
            }
            else if (*gameTalkerFase == 8)
            {
                textPositioning(worm2, 95, 16);
            }
            else if (*gameTalkerFase == 9)
            {
                textPositioning(worm3, 95, 16);
            }
            else if (*gameTalkerFase == 10)
            {
                textPositioning(worm2, 95, 16);
            }
            else if (*gameTalkerFase == 11)
            {
                textPositioning(worm3, 95, 16);
            }
            else if (*gameTalkerFase == 11)
            {
                textPositioning(worm2, 95, 16);
            }
            else if (*gameTalkerFase == 12)
            {
                textPositioning(worm3, 95, 16);
            }
            else if (*gameTalkerFase == 13)
            {
                *gameTalkerFase = 18;
            }
        }
        else if (*randText == 1)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            if (*gameTalkerFase == 4) {
                textPositioning(thumbs_up, 95, 16);
                *gameTalkerFase = 5;
            }
            else if (*gameTalkerFase == 6)
            {
                textPositioning(happy_face, 95, 16);
            }
            else if (*gameTalkerFase == 7)
            {
                textPositioning(happy_face_2, 95, 16);
            }
            else if (*gameTalkerFase == 8)
            {
                textPositioning(happy_face, 95, 16);
            }
            else if (*gameTalkerFase == 9)
            {
                textPositioning(happy_face_2, 95, 16);
            }
            else if (*gameTalkerFase == 10)
            {
                textPositioning(happy_face, 95, 16);
            }
            else if (*gameTalkerFase == 11)
            {
                textPositioning(happy_face_2, 95, 16);
            }
            else if (*gameTalkerFase == 12)
            {
                *gameTalkerFase = 18;
            }
        }
        else if (*randText == 2)
        {
            printf("%s", ANSI_COLOR_DARK_ORANGE);
            if (*gameTalkerFase == 4) {
                textPositioning(fireworks_1, 95, 16);
                (*internalTimer) += 20;
                *gameTalkerFase = 5;
            }
            else if (*gameTalkerFase == 5)
            {
                (*internalTimer) += 20;
            }
            else if (*gameTalkerFase == 6)
            {
                (*internalTimer) += 20;
                textPositioning(fireworks_2, 95, 16);
            }
            else if (*gameTalkerFase == 7)
            {
                (*internalTimer) += 20;
                textPositioning(fireworks_3, 95, 16);
            }
            else if (*gameTalkerFase == 8)
            {
                (*internalTimer) += 20;
                textPositioning(fireworks_4, 95, 16);
            }
            else if (*gameTalkerFase == 9)
            {
                (*internalTimer) += 20;
                textPositioning(fireworks_5, 95, 16);
            }
            else if (*gameTalkerFase == 10)
            {
                (*internalTimer) += 20;
                textPositioning(fireworks_6, 95, 16);
            }
            else if (*gameTalkerFase == 11)
            {
                (*internalTimer) += 20;
                textPositioning(fireworks_7, 95, 16);
            }
            else if (*gameTalkerFase == 12)
            {
                (*internalTimer) += 20;

                textPositioning(fireworks_8, 95, 16);
            }
            else if (*gameTalkerFase == 13)
            {
                (*internalTimer) += 20;
                textPositioning(fireworks_9, 95, 16);
            }
            else if (*gameTalkerFase == 14)
            {
                (*internalTimer) += 20;
                textPositioning(fireworks_10, 95, 16);
            }
            else if (*gameTalkerFase == 15)
            {
                (*internalTimer) += 20;
                textPositioning(fireworks_11, 95, 16);
            }
            else if (*gameTalkerFase == 16)
            {
                textPositioning(fireworks_12, 95, 16);
            }
        }
    }
    else if (points > 100 && (ticks % 2000)) //TALKER 6th FASE 100+ p
    {

    }
    if (*internalTimer >= 70) // BLANK
    {

        *gameTalkerMap = 0;
        if (*gameTalkerFase == 5)
        {
            *gameTalkerFase = 6;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 6)
        {
            *gameTalkerFase = 7;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 7)
        {
            *gameTalkerFase = 8;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 8)
        {
            *gameTalkerFase = 9;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 9)
        {
            *gameTalkerFase = 10;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 10)
        {
            *gameTalkerFase = 11;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 11)
        {
            *gameTalkerFase = 12;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 12)
        {
            *gameTalkerFase = 13;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 13)
        {
            *gameTalkerFase = 14;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 14)
        {
            *gameTalkerFase = 15;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 15)
        {
            *gameTalkerFase = 16;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 16)
        {
            *gameTalkerFase = 17;
            *internalTimer = 0;
            return;
        }
        else if (*gameTalkerFase == 17)
        {
            *gameTalkerFase = 18;
            *internalTimer = 0;
            *randText = rand() % 3;
            return;
        }
        textPositioning(blank, 95, 16);
        *internalTimer = 0;
        *randText = rand() % 3;
        *randText = 1;

        return;
    }
 }
 */



const char** dialogues[][3] = {
    { ouch ,  ouch_variant1 ,  ouch_variant2 },
    { huh ,  huh_variant1 ,  huh_variant2 },
    { not_that_bad ,  not_that_bad_variant1 ,  not_that_bad_variant2 },
    { impressed ,  impressed_1 ,  impressed_cs50 },
    { almost_there_comic_1 ,  almost_there_comic_2 ,  almost_there_comic_3 }

};

const char** animations[][12] = {
    { worm1 ,  worm2 ,  worm3, worm2  ,worm3, worm2 ,worm3, worm2 ,worm3, worm2 ,worm3, worm2},
    { thumbs_up ,  happy_face ,  happy_face_2,happy_face ,  happy_face_2,happy_face ,  happy_face_2,happy_face ,  happy_face_2,happy_face ,  happy_face_2,happy_face},
    { fireworks_1 ,  fireworks_2 ,  fireworks_3, fireworks_4 ,  fireworks_5 ,  fireworks_6 , fireworks_7 ,  fireworks_8 ,  fireworks_9, fireworks_10 ,  fireworks_11 ,  fireworks_12}
};

void showDialogue(const char* text, int x, int y) {
    printf("%s", ANSI_COLOR_DARK_ORANGE);
    textPositioning(text, x, y);
}

void advancePhase(int* phase, int* timer) {
    (*phase)++;
    *timer = 0;
}

void gameTalker(snake* segment, int points, int ticks, int* gameTalkerFase, int* gameTalkerMap, int* internalTimer, int* randText) {
    //printf("\033[H internalTimer: %i ",*internalTimer,*randText);

    // MAP boundaries condition
    if ((segment->x_pos < 2 || segment->y_pos > 32 || segment->y_pos < 3) && *gameTalkerMap == 0) {
        showDialogue(dialogues[0][*randText], 95, 16);
        *gameTalkerMap = 1;
    }
    
    // Dialogue phases based on points
    if (*gameTalkerFase < 5) {
        int thresholds[] = { 2, 5, 7, 10 }; //This are the points you have to reach in order for a threshhold to be reached
        for (int i = 0; i < 4; i++) {
            if (points == thresholds[i] && *gameTalkerFase == i) {
                showDialogue(dialogues[i + 1][*randText], 95, 16);
                *gameTalkerFase = i + 1;
                break;
            }
        }
    }
    if (points == 12 && *gameTalkerFase == 4) 
    {
        *gameTalkerFase = 5;
        *randText = 2;
    }
    
    // Special cases for phases 5-17
    if (*gameTalkerFase >= 5 && *gameTalkerFase < 17) {
        int index = (*gameTalkerFase - 5);
        showDialogue(animations[*randText][index], 95, 16);
        *internalTimer += 5; // Add Anidatade Ifs to control the speed of each animation.
    }
    

    // Reset conditions based on internal timer
    if (*internalTimer >= 100) {
        printf("\033[H internalTimer: %i  gameTalkerFase: %i", *internalTimer, *gameTalkerFase);

        if (*gameTalkerFase >= 5 && *gameTalkerFase < 17)
        {
            advancePhase(gameTalkerFase, internalTimer);
            if (*gameTalkerFase == 17)
            {
                textPositioning(blank, 95, 16);
                return;
            }
            return;
        }
        
        *internalTimer = 0;
        *randText = rand() % 3;
        textPositioning(blank, 95, 16);
        *gameTalkerMap = 0;
        return;
    }
}
