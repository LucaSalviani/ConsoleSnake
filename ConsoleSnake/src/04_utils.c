#include "utils.h"
#include "art.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

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


void readInputWithLimit(char* input, int maxLen) 
{
    bool confirm = false;
    printf("\033[17;102H"); // THIS SETS THE CURSOR WRITING POSITION
    clearBuffer();
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);  // Obtén el manejador de la entrada estándar
    DWORD modeOriginal, modeSinEco;
    int i = 0;
    memset(input, 0, maxLen);
    // Guarda el modo actual de la consola
    GetConsoleMode(hInput, &modeOriginal);

    // Configura la consola para deshabilitar el eco y la entrada en modo línea
    modeSinEco = modeOriginal & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(hInput, modeSinEco);

    // Lee los caracteres sin eco
    while (1) {
        INPUT_RECORD inputRecord;
        DWORD eventsRead;

        // Lee la entrada de la consola
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);

        // Procesa solo eventos de teclado
        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
            char c = inputRecord.Event.KeyEvent.uChar.AsciiChar;
            
            if (c == '\r' || confirm == true) {  // Enter
                printf("\033[18;102H\033[38;2;105;105;105mConfirm submission [y/n]: ");
                confirm = true;
                if (c == 'y')
                {
                    break;
                }
                else if (c == 'n')
                {
                printf("\033[18;102H                          "); // deletes the confirm submision text

                    confirm = false;
                    printf("\033[17;102H%s_______________", ANSI_COLOR_DARK_RED);  //deltes the user name eco
                    printf("\033[17;102H%s", ANSI_COLOR_DARK_RED); //sets the cursor so that the user can write freely
                    c = '\b';
                    i = 0;
                }
            }

            if (c == '\b' && i > 0) {  // Backspace
                printf("\b_\b");
                i--;
            }
            else if (confirm == false && (isalnum(c) || c == '_' || c == ' ' || c == '-' || c == '+' || c == '\\' || c == '/' || c == '?' || c == '>' || c == '<' || c == '.' || c == '@' || c == '#' || c == '$' || c == '&' || c == '*' || c == '^' || c == '!' || c == '~' || c == '(' || c == ')' || c == '[' || c == ']' || c == ';' || c == '\'' || c == '"' || c == '%') && i < maxLen) {  // Otros caracteres dentro del límite
                input[i] = c;
                putchar(c);  // Muestra el carácter
                //printf("%c", input[i]);
                i++;
            }
        }
    }
    input[i] = '\0';  // Agregar terminador nulo

    // Restaura el modo original de la consola
    SetConsoleMode(hInput, modeOriginal);
}


void clearBuffer() // IT ONLY WORKS FOR WINDOWS
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);  // Obtén el manejador de entrada estándar
    FlushConsoleInputBuffer(hInput);                // Limpia el buffer de entrada
}
