#ifndef GAME_H
#define GAME_H
#define _CRT_SECURE_NO_WARNINGS

#include "snake.h"

typedef struct PLayer{
    char name[16];
    int points;
    struct Player* next;
} Player;


// Funciones del juego
void controls(snake* segment, int* direction, bool* pause, int xLeftBoundary, int xRightBoundary, int yUpBoundary, int yDownBoundary);
void georginasCookies(snake** segment, snake** segmentPtr, int* x_food, int* y_food, int* points, int* snakeSize, int x_buffer, int y_buffer, int snakesDirection);
bool gameStart(int* snakeDirection);
void gameTalker(snake* segment, int points, int ticks, int* gameTalkerFase, int* gameTalkerMap, int* internatTimer,int* randText);
void forcedPause(bool* pause);
void pointsDisplay(int points, int xPos, int yPos, const char** text[]);
void displayRecords(const char* filename);
void readRecord(const char* recordsTxt, Player** playerPtr);
void saveRecord(const char* recordsTxt, Player* playerPtr);
void padString(char* str, int totalLength, char padChar);
void addPlayer(Player** playerPtr, char nameRead[16], int pointsFinal);
void padStringIzq(char* str, int totalLength, char padChar);


#endif // GAME_H