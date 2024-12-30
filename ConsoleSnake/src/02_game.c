#include "game.h"
#include "utils.h"
#include "snake.h"
#include "art.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <string.h>

//Food function (The snake eats my gf cookies ;])
void georginasCookies(snake** segment,snake** segmentPtr, int* x_food, int* y_food, int* points,int* snakeSize, int x_buffer, int y_buffer, int snakesDirection)
{
    //IMPORTANT this if statemnt has 2 parts the second part of the OR || is because i made my snake aeshtetically not common, it has 2 pieces to itself so when vertical needs to compare two spaces
    if (((*segment)->x_pos == *x_food && (*segment)->y_pos == *y_food) || ((snakesDirection == 3 || snakesDirection == 4) && (((*segment)->x_pos+1) == *x_food && (*segment)->y_pos == *y_food)))
    {
        (*points)++;
        pointsDisplay(*points, 130, 9, numbers);
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
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('a') & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
    {
        return false;
        *snakeDirection = 1;
    }
    else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
    {
        *snakeDirection = 2;
        return false;
    }
    else if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
    {
        *snakeDirection = 3;
        return false;
    }
    else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
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
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('a') & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
    {
        *direction = 1;
    }
    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
    {
        *direction = 2;
    }
    if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
    {
        *direction = 3;
    }
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
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

// All the dialogues are indexed in an array
const char** dialogues[][3] = {
    { ouch ,  ouch_variant1 ,  ouch_variant2 },
    { huh ,  huh_variant1 ,  huh_variant2 },
    { not_that_bad ,  not_that_bad_variant1 ,  not_that_bad_variant2 },
    { impressed ,  impressed_1 ,  impressed_cs50 },
    { almost_there_comic_1 ,  almost_there_comic_2 ,  almost_there_comic_3 }

};

// All animations are indexed in an array
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

    // MAP boundaries condition
    if ((segment->x_pos < 2 || segment->y_pos > 33 || segment->y_pos < 3) && *gameTalkerMap == 0) {
        showDialogue(dialogues[0][*randText], 95, 16);
        *gameTalkerMap = 1;
    }
    
    // Dialogue phases based on points
    if (*gameTalkerFase < 5) {
        int thresholds[] = { 10, 25, 50, 90 }; //This are the points you have to reach in order for a threshhold to be reached 10 25 50 90
        for (int i = 0; i < 4; i++) {
            if (points == thresholds[i] && *gameTalkerFase == i) {
                showDialogue(dialogues[i + 1][*randText], 95, 16);
                *gameTalkerFase = i + 1;
                break;
            }
        }
    }
    if (points == 100 && *gameTalkerFase == 4) 
    {
        *gameTalkerFase = 5;
    }

    //This are all for animations
    if (*gameTalkerFase >= 5 && *gameTalkerFase < 17) {
        int index = (*gameTalkerFase - 5);
        showDialogue(animations[*randText][index], 96, 18);

        //You have different speeds depending on the animation
        if (*randText == 0 || *randText == 1) 
        {
            *internalTimer += (*gameTalkerFase != 5) ? 5 : 2; //terniary operator, it decides between 5 or 2 depending on the actual phase
        }
        else if (*randText == 2)
        {
            if (*gameTalkerFase != 16)
            {
                *internalTimer += 20;
            }
        }
    }
    
    // Reset conditions based on internal timer
    if (*internalTimer >= 100) {

        //This are for the animations
        if (*gameTalkerFase >= 5 && *gameTalkerFase < 17)
        {
            advancePhase(gameTalkerFase, internalTimer);
            if (*gameTalkerFase == 17)
            {
                textPositioning(blank, 96, 18);
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


/////////////////// FROM DOWN HERE ITS ALL RELATED TO THE PLAYERS DATA FILE

// Reads the record from the data file into a linked list of 2 elements, name and points
void readRecord(const char* recordsTxt, Player** playerPtr)
{
    FILE* file = fopen(recordsTxt, "r");
    if (file == NULL)
    {
        return;
    }

    char nameRead[16] = { 0 };
    char pointsString[5] = { 0 };
    int pointsFinal = 0;
    int c;
    int readingCycle = 0;
    int characterPos = 0;
    char* target = NULL;

    while ((c = fgetc(file)) != EOF) // Reads until end of file
    {
        if (c == ':')
        {
            if (readingCycle == 0) // Starts reading the name
            {
                readingCycle = 1;
                characterPos = 0;
            }
            else if (readingCycle == 3) // Starts reading the points
            {
                readingCycle = 2;
                characterPos = 0;
            }
        }
        else if (c == '|' || c == '\n')
        {
            if (readingCycle == 1) // End of the name
            {
                nameRead[characterPos] = '\0';
                readingCycle = 3; // changes the state of point reading
            }
            else if (readingCycle == 2) // Ends of the points
            {
                pointsString[characterPos] = '\0';
                pointsFinal = atoi(pointsString); // Converts points into int
                addPlayer(playerPtr, nameRead, pointsFinal); // Adds to the list
                readingCycle = 0; // Cycle restarts
            }
            characterPos = 0;
        }
        else
        {
            // Determines the destination buffer with a terniary operation
            target = (readingCycle == 1) ? nameRead : (readingCycle == 2) ? pointsString : NULL;
            if (target != NULL && characterPos < ((readingCycle == 1) ? sizeof(nameRead) - 1 : sizeof(pointsString) - 1)) // checks to avoid crashes
            {
                target[characterPos++] = c;
            }
        }
    }

    fclose(file);
}

////// Adds a player to the linked list
void addPlayer(Player** playerPtr, char nameRead[16], int pointsFinal)
{
    Player* newPlayer = malloc(sizeof(Player));
    if (newPlayer == NULL)
    {
        printf("Theres no space in memory to run the game");
        exit(1);
    }
    //asigns values to this lists node
    strncpy_s(newPlayer->name, sizeof(newPlayer->name), nameRead, _TRUNCATE);
    newPlayer->points = pointsFinal;
    newPlayer->next = *playerPtr;
    *playerPtr = newPlayer;
}

// Recursive merge sorting algorithm that works with the linked list and does not use brute force (An array)
void mergeSort(Player **playerPtr)
{
     Player* head = *playerPtr;
     Player* a;
     Player* b;

    // Base case 
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    // Split head 
    FrontBackSplit(head, &a, &b);

    // Recursively sort the sublists 
    mergeSort(&a);
    mergeSort(&b);

    *playerPtr = SortedMerge(a, b);

}

// Merges two sorted lists
struct Player* SortedMerge( Player* a,  Player* b)
{
     Player* result = NULL;

    // Base cases 
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    // Pick either a or b, and recur 
    if (a->points >= b->points)
    {
        result = a;
        result->next =
            SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}



void FrontBackSplit( Player* source,  Player** frontRef,  Player** backRef)
{
     Player* fast;
     Player* slow;
    slow = source;
    fast = source->next;

    // Advance 'fast' two nodes, and advance 'slow' one node   
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' is before the midpoint in the list, so split it in two at that point.
         
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}



// Frees players linked list
void freePlayerList(Player * playerPtr)
{
    // Base case
    if (playerPtr == NULL)
    {
        return;  // If NULL return
    }

    // Call the function recursevly 
    freePlayerList(playerPtr->next);

    // Free actual node
    free(playerPtr);


}


///////////// Rewrites the players file with the new list
void saveRecord(const char* recordsTxt, Player* playerPtr,int *registryAmount)
{
    FILE* file = fopen(recordsTxt, "w"); // We want to everwrite the previous file with the new ordered linked list
    if (file == NULL)
    {
        perror("Error while opening file");
        return;
    }

    while (playerPtr != NULL)
    {
        char nameBuffer[16] = { 0 };
        // Copy and fill the name
        if(playerPtr->name != NULL)
        { 
            if (strncpy_s(nameBuffer, sizeof(nameBuffer), playerPtr->name, _TRUNCATE) != 0)
            {
                fprintf(stderr, "Error while copying the players name\n");
                fclose(file);
                return;
            }
        }

        padString(nameBuffer, 15, ' ');
        // Right registry into file
        (*registryAmount)++;
        fprintf(file, "PLAYER:%s|SCORE:%4d\n", nameBuffer, playerPtr->points);

        playerPtr = playerPtr->next;
    }
    // Close file
    fclose(file);
    freePlayerList(playerPtr);
}


/////// Gives the names string padding
void padString(char* str, int totalLength, char padChar) 
{
    int len = strlen(str);

    if (len < totalLength) {
        // Fill with padChar until the string has the desired length 
        for (int i = len; i < totalLength; i++) {
            str[i] = padChar;
        }
        str[totalLength] = '\0';  // Makes sure that the chain is terminated in a null
    }
}


///////// Gives the names string padding to the left
void padStringIzq(char* str, int totalLength, char padChar)
{
    int len = strlen(str);

    if (len < totalLength) {
        int padding = totalLength - len;

        for (int i = len; i >= 0; i--) {
            str[i + padding] = str[i];
        }

        for (int i = 0; i < padding; i++) {
            str[i] = padChar;
        }
    }
}


///////// Displays the records file 
void displayRecords(const char* recordsTxt,int* scroll,int registryAmount,int ticks)
{
    // Open the file in read mode
    FILE* file = fopen(recordsTxt, "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    // Presentation, Records title and blank space in case theres text from the game talker
    char line[256];
    printf("\033[16;95H%s              RECORDS           ",ANSI_COLOR_DARK_RED);
    printf("\033[17;95H                                  ");

    // This only happens if you have a big enough file, it controls the scroll down effect, including the scroll bar and  the scroll rate. In this case it activates at a file with 15 registrys since thats the display space
    if (registryAmount > 15)
    {
        float scrollRate = (registryAmount ) / 15;
        int integralPart = round(scrollRate); // i could also calculate the integer rest of the division and use that as a parameter so that the scroll is more exact, but it is a lot of work for very little reward, maybe some day(?
        if (scroll != NULL ) 
        {
            // Detect keys up for scroll and shift its all based on the scroll rate setted up the space where you will print the files records ( in this case 15) and the file size
            bool isUpPressed = (GetAsyncKeyState(VK_UP) & 0x8000)
                || (GetAsyncKeyState('w') & 0x8000)
                || (GetAsyncKeyState('W') & 0x8000);

            if (isUpPressed && ((*scroll) > 0)) {
                if ((ticks % 4 == 0) || ((GetAsyncKeyState(VK_SHIFT) & 0x8000) && (ticks % 1 == 0))) {
                    (*scroll)--;

                    // Calcula cuánto mover la rueda de desplazamiento
                    int scrolledAmount = (*scroll) / integralPart;

                    // Imprime la rueda de desplazamiento
                    printf("\033[%d;130H  ", 18 + scrolledAmount);
                    printf("\033[%d;130H||", 17 + scrolledAmount);
                }
            }


            // Detect keys down for the scroll and shift, its all based on a scroll rate and the files size
            bool isDownPressed = (GetAsyncKeyState(VK_DOWN) & 0x8000)
                || (GetAsyncKeyState('s') & 0x8000)
                || (GetAsyncKeyState('S') & 0x8000);

            if (isDownPressed && ((*scroll) < (registryAmount - 15))) {
                if ((ticks % 4 == 0) || ((GetAsyncKeyState(VK_SHIFT) & 0x8000) && (ticks % 1 == 0))) {
                    (*scroll)++;
                        //prints the scroll wheel
                        int scrolledAmount = (*scroll) / integralPart;
                        printf("\033[%d;130H  ", 16 + scrolledAmount);
                        printf("\033[%d;130H||", 17 + scrolledAmount);
                }
            }

            //Prints a letter at the top explaining how the file navigation controls work
           //printf("\033[3;71H%s|%s Arrows for scrolling", ANSI_COLOR_DARK_ORANGE, ANSI_COLOR_LIGHT_GREY);
           //printf("\033[4;71H%s|%s+SHIFT fast scrolling",ANSI_COLOR_DARK_ORANGE,ANSI_COLOR_LIGHT_GREY);
           // printf("\033[5;72H%s---------------------",ANSI_COLOR_DARK_ORANGE);
            printf("\033[32;71H Arrows for scrolling");
            printf("\033[33;71H+SHIFT fast scrolling");
            skipLines(file, *scroll); // puts the file cursor where it needs to be so that the next 15 file lines are read apropatlly
        }
    }
    

    // Prints the file lines dessired either by amount (15) or availabilty (less than 15 file registrys)
  
    for (int i = 0; i < 15 && fgets(line, sizeof(line), file) ; i++)
    {
            //This is for the Top 3 records
            if (i < (3 - *scroll))
            { 
                breathingEffectToColor(ticks, red, white);
                if (i == 0)
                {
                    if (*scroll == 0) // This is ONLY for the top 1 to distinguish it from the rest
                    {
                        printf("%s",ANSI_TEXT_BACKGROUND_INVERSION);
                    }
                    textPositioning(top, 81, 18 + i); //Prints some etiquetes for the top players and specially the first visible top considering the scroll
                    printf("\033[%i;86H%i ====>", 18 + i, i + 1 + *scroll);

                    printf("%s",ANSI_TEXT_BACKGROUND_REVERSION);
                }
                else
                {
                    textPositioning(top, 86, 18 + i); // for every other top player thats not first visible considering the scroll
                    printf("\033[%i;92H%i", 18 + i, i + 1 + *scroll);
                }
            }
            else if (i < 5) // deletes the top etiquetes based on the scroll so that it only show apropiettly
            {
                printf("\033[%i;79H              ", 18 + i);
                printf("%s", ANSI_COLOR_DARK_RED);
            }
            if (*scroll == 0 && i == 0) //resets background inversion
            {
                printf("%s", ANSI_TEXT_BACKGROUND_INVERSION);
            }
            //THIS PRINTS THE RECORDS, the actual records everything above is visual effects for the top 3
            printf("\033[%i;95H%s", 18 + i, line);
            printf("%s", ANSI_TEXT_BACKGROUND_REVERSION);
    }
 
    // Close the file
    fclose(file);
}

// Skips lines in the file so that the file cursor is where it is expected based on the scroll rate, if you scrolled 5 postions down it will skip 5 positions
void skipLines(FILE* file, int linesToSkip) 
{
    char buffer[256];  // buffer for the lines 

    for (int i = 0; i < linesToSkip; i++) 
    {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("\033[HReached end of file before skipping lines\n");
            break;
        }
    }
}



