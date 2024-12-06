#ifndef GAME_H
#define GAME_H

#include "snake.h"

// Funciones del juego
void controls(snake* segment, int* direction, bool* pause, int xLeftBoundary, int xRightBoundary, int yUpBoundary, int yDownBoundary);
void georginasCookies(snake** segment, snake** segmentPtr, int* x_food, int* y_food, int* points, int* snakeSize, int x_buffer, int y_buffer, int snakesDirection);
bool gameStart(int* snakeDirection);
void gameTalker(snake* segment, int points, int ticks, int* gameTalkerFase, int* gameTalkerMap, int* internatTimer);
void forcedPause(bool* pause);
void pointsDisplay(int points, int xPos, int yPos, const char** text[]);
#endif // GAME_H