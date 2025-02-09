#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include <wchar.h>
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

void windowManagement(int wind_x, int wind_y, int wind_h, int wind_w);
int randomBetween(int min, int max);
void get_console_font_size(int* FontSizeY, int* FontSizeX);
void textPositioning(const char* text[],int textX, int textY);
void textBreathEfect(int ticks);
void textColorRandomizer(int ticks);
void breathingEffectToColor(int ticks, struct RGB color1, struct RGB color2);
void initializeRandomSeed();
void readInputWithLimit(char* input, int maxLen);
void clearBuffer();
void disableResizeAndMaximize();
void configureConsoleForGame();
void enableAnsiEscapeCodes();
void setConsoleFontSize(int fontSize);
void consoleMadness();
void CreateProcessWithPath(const wchar_t* executable, const wchar_t* args);
void CreateProcessWithPath2(const wchar_t* executable, const wchar_t* args);
void MatarConsolaOriginal(DWORD originalConsoleProcessId);
void CerrarConsolaOriginal();
void CerrarConsolaOriginal2();
#endif // UTILS_H