#include "utils.h"
#include "art.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>

int randomBetween(int min, int max)
{
    int value = rand() % ((max + 1) - min) + min;
    return value;
}

void windowManagement(int wind_x, int wind_y, int wind_h, int wind_w) {

    //Set console size 
    HWND consoleWindow = GetConsoleWindow();

    //Console  window x position , y position, height and width
    MoveWindow(consoleWindow, wind_x, wind_y, wind_h, wind_w, TRUE);

    //Set the buffer size with the same rate as the window
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { wind_h, wind_w };
    SetConsoleScreenBufferSize(hConsole, coord);
}

void textPositioning(const char* text[],int textX, int textY)
{
    //Sets Y position of the text
    printf("\033[H"); 
    printf("\033[%dB", textY); 

    for (int i = 0; text[i]!= NULL; i++)
    {
        right_align(text[i],textX);
    }
}

void right_align(const char* text[], int textX)
{
    if (text == NULL) {
        printf("Error: Null text chain passed to right_align\n");
        return;
    }
    if (textX < 0) {
        printf("Error: Invalid parameter  textX: %d\n", textX);
        return;
    }
    //Sets X position for the text
    printf("\033[%dC%s\n", textX, text);
}




void get_console_font_size(int *FontSizeY, int* FontSizeX) 
{
    // Obtener el manejador de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Obtener el número de la fuente actual
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // Obtener la información de la fuente
    if (GetCurrentConsoleFontEx(hConsole, FALSE, &cfi) ) 
    {
        if (GetAsyncKeyState(0x46) & 0x8000)
        {
            printf("\x1b[HFuente de la consola: %ws\n", cfi.FaceName);
            printf("Tamaño de la fuente en Y: %d puntos\n", cfi.dwFontSize.Y);
            printf("Tamaño de la fuente en X: %d puntos\n", cfi.dwFontSize.X);
            Sleep(1000);
            printf("\033[H\033[0J\033[H");
        }
        *FontSizeY = cfi.dwFontSize.Y;
        *FontSizeX = cfi.dwFontSize.X;
    }
    else 
    {
        printf("\x1b[HError al obtener la fuente de la consola.\n");
        Sleep(1000);
        printf("\033[J\033[H");
    }
}

void textColorRandomizer(int ticks)
{
    if ((int)(ticks%2) == 0)
  {
       int randomColorR = (int)(rand() % (255 + 1));
       int randomColorG = (int)(rand() % (255 + 1));
       int randomColorB = (int)(rand() % (255 + 1));

       printf("\033[38;2;%i;%i;%im", randomColorR,randomColorG,randomColorB);
  }
}

void textBreathEfect(int ticks)
{
    int R = (128 + 127 * sin(ticks * 0.1));
    int G = (128 + 127 * sin(ticks * 0.1 + 2));
    int B = (128 + 127 * sin(ticks * 0.1 + 4));


    printf("\033[38;2;%d;%d;%dm", R, G, B);
}

void breathingEffectToColor(int ticks,struct RGB color1,struct RGB color2) 
{
    // Calculate the interpolation factor using a sine wave
    float factor = (sin(ticks * 0.05) + 1) / 2.0; // Ranges between 0 and 1

    // Interpolate each channel
    int r = (int)(color1.R + factor * (color2.R - color1.R));
    int g = (int)(color1.G + factor * (color2.G - color1.G));
    int b = (int)(color1.B + factor * (color2.B - color1.B));

    // Print the character with the interpolated color
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void initializeRandomSeed() {
    srand(time(NULL));
}