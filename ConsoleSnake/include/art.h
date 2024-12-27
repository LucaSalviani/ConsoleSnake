#ifndef ART_H
#define ART_H

void titleErasser();

struct RGB
{
	int R;
	int G;
	int B;
};

extern struct RGB pink;
extern struct RGB white;
extern struct RGB dark_orange;
extern struct RGB red;
extern struct RGB redBright;
extern struct RGB grey;
extern struct RGB lightGrey;


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
+-----------------------------------------------------------------------------------------------------------------------------------+\n"

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

extern const char* game_keys[];

extern const char* controls_text[];

extern const char* ouch[];

extern const char* ouch_variant1[];

extern const char* ouch_variant2[];

extern const char* huh[];

extern const char* huh_variant1[];

extern const char* huh_variant2[];

extern const char* not_that_bad[];

extern const char* not_that_bad_variant1[];

extern const char* not_that_bad_variant2[];

extern const char* impressed[];

extern const char* impressed_1[];

extern const char* impressed_cs50[];

extern const char* almost_there_comic_1[];

extern const char* almost_there_comic_2[];

extern const char* almost_there_comic_3[];

extern const char* worm1[];

extern const char* worm2[];

extern const char* worm3[];

extern const char* thumbs_up[];

extern const char* happy_face[];

extern const char* happy_face_2[];

extern const char* fireworks_1[];

extern const char* fireworks_2[];

extern const char* fireworks_3[];

extern const char* fireworks_4[];

extern const char* fireworks_5[];

extern const char* fireworks_6[];

extern const char* fireworks_7[];

extern const char* fireworks_8[];

extern const char* fireworks_9[];

extern const char* fireworks_10[];

extern const char* fireworks_11[];

extern const char* fireworks_12[];

extern const char* top[];

const char* arena3[];

const char* arenaPiece1[];

const char* arenaPiece2[];

const char* arenaPiece3[];

const char* arenaPiece4[];


extern const char* bigBlank[];

extern const char* blank[];

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
#define ANSI_COLOR_DARK_RED     "\033[38;2;200;50;50m"
#define ANSI_COLOR_DARK_BLUE	 "\x1b[34m"
#define ANSI_COLOR_BRIGHT_PINK   "\033[38;2;255;105;180m"
#define ANSI_COLOR_GOLD          "\033[38;2;255;204;0m"
#define ANSI_COLOR_DARK_PINK     "\033[38;2;150;60;100m"
#define ANSI_COLOR_GREY          "\033[38;2;105;105;105m"
#define ANSI_COLOR_LIGHT_GREY    "\033[38;2;80;80;80m"


#define ANSI_RESET_STYLE            "\033[0m"
#define ANSI_RESET_POSITION			"\033[H"
#define ANSI_TEXT_BACKGROUND_INVERSION      "\033[7m"
#define ANSI_TEXT_BACKGROUND_REVERSION      "\033[27m"


#endif // ART_H
