#ifndef ART_H
#define ART_H

struct RGB
{
	int R;
	int G;
	int B;
};

extern struct RGB pink;
extern struct RGB white;
extern struct RGB dark_orange;

//First art style, simpler to write MUCH more difficult if you want to move the art in the X axis, good for big static images like titles, or that are already right aligned
#define SNAKE_LOGO "\n\
      _______________________________________________________________________________________________________________________\n\
     /                                                                                                                       \\\n\
     |       ::::::::  ::::    :::     :::     :::    ::: ::::::::::           ::::::::      :::       :::   :::   :::::::::  |\n\
     |     :+:    :+: :+:+:   :+:   :+: :+:   :+:   :+:  :+:                 :+:    :+:   :+: :+:    :+:+: :+:+:  :+:         |\n\
     |    +:+        :+:+:+  +:+  +:+   +:+  +:+  +:+   +:+                 +:+         +:+   +:+  +:+ +:+:+ +:+ +:+          |\n\
     |   +#++:++#++ +#+ +:+ +#+ +#++:++#++: +#++:++    +#++:++#            :#:        +#++:++#++: +#+  +:+  +#+ +#++:++#      |\n\
     |         +#+ +#+  +#+#+# +#+     +#+ +#+  +#+   +#+                 +#+   +#+# +#+     +#+ +#+       +#+ +#+            |\n\
     | #+#    #+# #+#   #+#+# #+#     #+# #+#   #+#  #+#                 #+#    #+# #+#     #+# #+#       #+# #+#             |\n\
     | ########  ###    #### ###     ### ###    ### ##########           ########  ###     ### ###       ### ##########       |\n\
     \\_______________________________________________________________________________________________________________________/ \n"

#define ARENA2 "\n\
+-----------------------------------------------------------------------------------------------------------------------------------+\n\
|/------------------------------------------------------------------------------------------/--------------------------------------\\|\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |______________________________________||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
||                                                                                          |                                      ||\n\
|\\------------------------------------------------------------------------------------------\\--------------------------------------/|\n\
+---------------------------------------------------------------------------------------------------------------------------------- - +\n"

//Trying different ascii art formats. This one is a little bit more difficult to define the art in itself, you have to also make another .c file with the art definitions, but way easier to move in X axis and also easier to make dynamic (provided you have a function that does that for you as i have). I think the easiest format might be to use a text file read from that and apply the changes to the text to move it on its axis on the go, only problem is you wont have a nice executable and it wont all be contained on your code, and youd need external resources so not one file executable.

extern const char* points_art[];
extern const char* number_0[];
extern const char* number_1[];
extern const char* number_2[];
extern const char* number_3[];
extern const char* number_4[];
extern const char* number_5[];
extern const char* number_6[];
extern const char* number_7[];
extern const char* number_8[];
extern const char* number_9[];
extern const char** numbers[];

extern const char* game_over[];

#define RIGHT_ALIGN "\x1b[98G"



// Texto en colores brillantes
#define ANSI_COLOR_BRIGHT_BLACK    "\033[1;30m"
#define ANSI_COLOR_BRIGHT_RED      "\033[1;31m"
#define ANSI_COLOR_BRIGHT_GREEN    "\033[1;32m"
#define ANSI_COLOR_BRIGHT_YELLOW   "\033[1;33m"
#define ANSI_COLOR_BRIGHT_BLUE     "\033[1;34m"
#define ANSI_COLOR_BRIGHT_MAGENTA  "\033[1;35m"
#define ANSI_COLOR_BRIGHT_CYAN     "\033[1;36m"
#define ANSI_COLOR_BRIGHT_WHITE    "\033[1;37m"

// Texto en colores básicos
#define ANSI_COLOR_BLACK       "\033[0;30m"
#define ANSI_COLOR_RED         "\033[0;31m"
#define ANSI_COLOR_GREEN       "\033[0;32m"
#define ANSI_COLOR_YELLOW      "\033[0;33m"
#define ANSI_COLOR_BLUE        "\033[0;34m"
#define ANSI_COLOR_MAGENTA     "\033[0;35m"
#define ANSI_COLOR_CYAN        "\033[0;36m"
#define ANSI_COLOR_WHITE       "\033[0;37m"

#define ANSI_COLOR_DARK_ORANGE   "\033[38;2;255;140;0m"
#define ANSI_COLOR_DARK_BLUE	 "\x1b[34m"
#define ANSI_COLOR_BRIGHT_PINK   "\033[38;2;255;105;180m"
#define ANSI_COLOR_GOLD          "\033[38;2;255;204;0m"
#define ANSI_COLOR_DARK_PINK     "\033[38;2;150;60;100m"


#define ANSI_RESET_STYLE            "\033[0m"
#define ANSI_RESET_POSITION			"\033[H"

#endif // ART_H
