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
    ShowWindow(consoleWindow, SW_RESTORE);
   
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    // Changes the background color of the console itself for older consoles like powershell
    WORD color = (0x00 << 4) | (csbi.wAttributes & 0x0F);
    //This gives the console its position and its absolute size, the absolute size is determined in pixels
    MoveWindow(consoleWindow, wind_x, wind_y, wind_w, wind_h, TRUE);


    // Defines the consoles buffer, its determined in characters
    COORD bufferSize;
    bufferSize.X = (wind_w / 8);  //133 Width of the console in characters, it has to be the same as the translation from pixels to characters so that there are no scroll bars
    bufferSize.Y = (wind_h / 16) - 1;  //35 Height of the console in characters, it has to be the same as the translation from pixels to characters so that there are no scroll bars

    // Sets the consoles buffer to the handle
    SetConsoleScreenBufferSize(hConsole, bufferSize);


    // This sets the VISIBLE not absolute size of the console window, and it makes the scroll bar area to disapear
    SMALL_RECT windowSize = { 0, 0, (wind_w / 8) - 1, (wind_h / 16) - 2 };  //132 34 Defines visible window size, its defines in characters not pixels, it has to be 1 less than the buffer
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize); // Sets the visible window size

}


void enableAnsiEscapeCodes() 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode;

    // Obtener el modo actual
    GetConsoleMode(hConsole, &dwMode);

    // Habilitar el soporte para escape de caracteres ANSI
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, dwMode);
}


void disableResizeAndMaximize() 
{
    HWND hWndConsole = GetConsoleWindow();
    LONG style;

    // Obtains windows details
    style = GetWindowLong(hWndConsole, GWL_STYLE);

    // Disables resize
    style &= ~WS_SIZEBOX; 

    // Disables maximize
    style &= ~WS_MAXIMIZEBOX; 

    // Establishes new styles
    if (SetWindowLong(hWndConsole, GWL_STYLE, style) == 0) {
        // Error management
        fprintf(stderr, "Error while modifing styles.\n");
        return;
    }

    // Forces a window update to apply changes
    if (SetWindowPos(hWndConsole, NULL, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED) == 0) {
        // Error management
        fprintf(stderr, "Error when updating console.\n");
        return;
    }
}


void configureConsoleForGame() 
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;

   
    if (!GetConsoleMode(hInput, &mode)) {
        fprintf(stderr, "Error trying to obtain console mode.\n");
        return;
    }

    // Disables quick edit mode and puts the console on Raw mode
    mode &= ~ENABLE_QUICK_EDIT_MODE;          
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT); 

    // Establishes new input mode
    if (!SetConsoleMode(hInput, mode)) {
        fprintf(stderr, "Error at stablishing new console input mode.\n");
        return;
    }
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
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Obtains current font size
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // Obtains font info
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

void setConsoleFontSize(int fontSize)
{
    // Obtener el handle de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error al obtener el handle de la consola.\n");
        return;
    }

    // Configurar el nuevo tamaño de la fuente
    CONSOLE_FONT_INFOEX fontInfo = { 0 };
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX); // Tamaño de la estructura

    // Obtener la configuración actual de la consola
    if (!GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
        fprintf(stderr, "Error al obtener la configuración actual de la consola.\n");
        return;
    }

    // Cambiar solo el tamaño de la fuente
    fontInfo.dwFontSize.X = 8;           // Mantener el ancho predeterminado
    fontInfo.dwFontSize.Y = fontSize;    // Ajustar la altura del carácter

    // Aplicar el nuevo tamaño
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
        DWORD error = GetLastError();
        fprintf(stderr, "Error al configurar el tamaño de la fuente de la consola.\n");
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

