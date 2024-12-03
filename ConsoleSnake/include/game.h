#ifndef GAME_H
#define GAME_H

#include "snake.h"

// Funciones del juego
void controls(snake* segment, int* direction,bool* pause);
void georginasCookies(snake** segmentPtr, int* x_food, int* y_food, int* points, int* snakeSize, int x_buffer, int y_buffer);
bool gameStart();
void forcedPause(bool* pause);
void pointsDisplay(int points, int xPos, int yPos, const char** text[]);
#endif // GAME_H