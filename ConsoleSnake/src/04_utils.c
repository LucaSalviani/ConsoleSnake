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

void windowManagement(int wind_x, int wind_y, int wind_h, int wind_w) 
{
    //Obtains console handle
    HWND consoleWindow = GetConsoleWindow();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //This gives the console its position and its absolute size, the absolute size is determined in pixels
    MoveWindow(consoleWindow, wind_x, wind_y, wind_w, wind_h, TRUE);




    // Defines the consoles buffer, its determined in characters
    COORD bufferSize;
    bufferSize.X = (wind_w/8);  //133 Width of the console in characters, it has to be the same as the translation from pixels to characters so that there are no scroll bars
    bufferSize.Y = (wind_h/16)-1;  //35 Height of the console in characters, it has to be the same as the translation from pixels to characters so that there are no scroll bars

    // Sets the consoles buffer to the handle
    SetConsoleScreenBufferSize(hConsole, bufferSize);


    // This sets the VISIBLE not absolute size of the console window, and it makes the scroll bar area to disapear
    SMALL_RECT windowSize = { 0, 0, (wind_w/8)-1, (wind_h/16)-2};  //132 34 Defines visible window size, its defines in characters not pixels, it has to be 1 less than the buffer
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize); // Sets the visible window size

}

void disableQuickEditMode() 
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;

    // Obtiene el modo actual
    GetConsoleMode(hInput, &prevMode);

    // Desactiva QUICK_EDIT_MODE y habilita INPUT_MODE est�ndar
    SetConsoleMode(hInput, prevMode & ~ENABLE_QUICK_EDIT_MODE);
}

void disableSelection() 
{
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hConsole, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  // Desactivar Quick Edit Mode
    SetConsoleMode(hConsole, mode);
}


void disableMaximize() 
{
    HWND hWndConsole = GetConsoleWindow();

    // Obtener los estilos actuales de la ventana
    LONG style = GetWindowLong(hWndConsole, GWL_STYLE);

    // Quitar la opci�n de maximizar
    style &= ~WS_MAXIMIZEBOX;

    // Actualizar los estilos de la ventana
    SetWindowLong(hWndConsole, GWL_STYLE, style);

    // Forzar una actualizaci�n de la ventana para aplicar los cambios
    SetWindowPos(hWndConsole, NULL, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

void disableResize() 
{
    HWND hWndConsole = GetConsoleWindow();

    // Deshabilitar la opci�n de redimensionar
    LONG style = GetWindowLong(hWndConsole, GWL_STYLE);
    style &= ~WS_SIZEBOX; // Quitar el estilo que permite redimensionar
    SetWindowLong(hWndConsole, GWL_STYLE, style);

    // Forzar una actualizaci�n de la ventana para aplicar los cambios
    SetWindowPos(hWndConsole, NULL, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

void textPositioning(const char* text[],int textX, int textY)
{
    for (int i = 0; text[i]!= NULL; i++)
    {
        printf("\033[%i;%iH%s", textY+i, textX, text[i]);
    }
}


void get_console_font_size(int *FontSizeY, int* FontSizeX) 
{
    // Obtener el manejador de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Obtener el n�mero de la fuente actual
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // Obtener la informaci�n de la fuente
    if (GetCurrentConsoleFontEx(hConsole, FALSE, &cfi) ) 
    {
        if (GetAsyncKeyState(0x46) & 0x8000)
        {
            printf("\x1b[HFuente de la consola: %ws\n", cfi.FaceName);
            printf("Tama�o de la fuente en Y: %d puntos\n", cfi.dwFontSize.Y);
            printf("Tama�o de la fuente en X: %d puntos\n", cfi.dwFontSize.X);
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
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);  // Obtains current console handle
    DWORD modeOriginal, modeSinEco;
    int i = 0;
    memset(input, 0, maxLen);
    // Saves current console mode
    GetConsoleMode(hInput, &modeOriginal);

    // Configures the console the disenable the eco and the in line input
    modeSinEco = modeOriginal & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(hInput, modeSinEco);

    // Reads characters without eco, later on i will show them one by one with my own criteria
    while (1) {
        INPUT_RECORD inputRecord;
        DWORD eventsRead;

        // Reads console input
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);

        // Only process keyboard events
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
            else if (confirm == false && (isalnum(c) || c == '_' || c == ' ' || c == '-' || c == '+' || c == '\\' || c == '/' || c == '?' || c == '>' || c == '<' || c == '.' || c == '@' || c == '#' || c == '$' || c == '&' || c == '*' || c == '^' || c == '!' || c == '~' || c == '(' || c == ')' || c == '[' || c == ']' || c == ';' || c == '\'' || c == '"' || c == '%') && i < maxLen) {  // Other charactrers inside the limit
                input[i] = c;
                putchar(c);  // Shows character
                i++;
            }
        }
    }
    input[i] = '\0';  // Adds null terminator

    // Restores console original mode
    SetConsoleMode(hInput, modeOriginal);
}


void clearBuffer() // IT ONLY WORKS FOR WINDOWS
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);  // Obtains the hanlde for input standard
    FlushConsoleInputBuffer(hInput);                // Cleans input buffer
}
