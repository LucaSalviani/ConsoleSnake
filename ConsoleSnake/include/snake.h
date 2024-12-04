#ifndef SNAKE_H
#define SNAKE_H
#include <stdbool.h>

typedef struct snake {
    int x_pos;
    int y_pos;
    struct snake* next;
} snake;

// Snake manipulation functions
void addSegment(snake** segmentPtr, int x_buffer, int y_buffer);
void drawSnake(snake* segmentPtr, bool delete);
void updateSnake(snake* segmentPtr);
bool colision(snake* segmentPtr, snake* segment, int snakeSize);
void freeSnakesMemory(snake* segmentPtr);

#endif // SNAKE_H