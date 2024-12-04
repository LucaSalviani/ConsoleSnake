#include "snake.h"
#include "game.h"
#include "art.h"
#include <stdio.h>
#include <stdlib.h>


//Colision detection function
bool colision(snake* segmentPtr, snake* segment, int snakeSize)
{
    if (segmentPtr == NULL)
    {
        // Base case
        return;
    }
    //Its important that the loop checks for the snakes colision up until the snakes length -2 because that way you can check for colisions in every part of the body but you dont check for for the head colisioning with itself
    for (int i = 0; i < snakeSize-2; i++)
    {
        if (segmentPtr->x_pos == segment->x_pos && segmentPtr->y_pos == segment->y_pos )
        {
            return true;
        }
        segmentPtr = segmentPtr->next;
    }
    return false;
}

//Updates all snakes segments in correlation to the head
void updateSnake(snake* segmentPtr)
{
    // Verifys if the snake is empty or has one node
    if (segmentPtr == NULL || segmentPtr->next == NULL) {
        return;
    }
    snake* current = segmentPtr;

    // Goes through all nodes
    while (current->next != NULL) {
        int next_x = (current->next)->x_pos; //Saves current head position
        int next_y = (current->next)->y_pos;
            current->x_pos = next_x;
            current->y_pos = next_y;
            current = current->next;
    }
}



//Adds a segment to the snake
void addSegment(snake** segmentPtr, int x_buffer, int y_buffer)
{
    snake* newSegment = malloc(sizeof(snake));
    if (newSegment == NULL)
    {
        printf("Theres no space in memory to run the game");
        exit(1);
    }
    newSegment->x_pos = x_buffer;
    newSegment->y_pos = y_buffer;
    newSegment->next = *segmentPtr;
    *segmentPtr = newSegment;
}

//Draws the snake recursively 
void drawSnake(snake* segmentPtr,bool delete)
{
    if (segmentPtr == NULL)
    {
        // Base case
        return;
    }

    // Draws this segment
    printf("%s", ANSI_COLOR_BRIGHT_PINK);
    if (delete != true)
    {
        printf("\x1b[%d;%dH[]", segmentPtr->y_pos, segmentPtr->x_pos);
    }
    else//deletes the snake
    {
        printf("\x1b[%d;%dH  ", segmentPtr->y_pos, segmentPtr->x_pos);
    }

    // Calls the function recursively on itself to draw the snake
    drawSnake(segmentPtr->next,delete);
}

//Frees snake's memory so that there are no memory leaks
void freeSnakesMemory(snake* segmentPtr)
{
    // Base case
    if (segmentPtr == NULL)
    {
        return;  // If NULL return
    }

    // Call the function recursevly 
    freeSnakesMemory(segmentPtr->next);

    // Free actual node
    free(segmentPtr);
}