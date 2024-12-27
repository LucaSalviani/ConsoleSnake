#include "art.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

struct RGB pink = { 255,105,180 };
struct RGB white = { 255,255,255 };
struct RGB grey = { 150,150,150 };
struct RGB lightGrey = { 50,50,50 };
struct RGB dark_orange = { 255,140,0 };
struct RGB red = { 200,50,50 };
struct RGB redBright = { 255, 0, 0 };

//Ogre font
const char* points_art[] = {
"             _       _         ",
" _ __   ___ (_)_ __ | |_ ___   _",
"| '_ \\ / _ \\| | '_ \\| __/ __| (_)",
"| |_) | (_) | | | | | |_\\__ \\  _",
"| .__/ \\___/|_|_| |_|\\__|___/ (_)",
"|_|                            ",
NULL
};

//Small font
const char* number_0[] = {


"  __   ",
" /  \\ ",
"| () | ",
" \\__/ ",
NULL
};
const char* number_1[] = {
"  _    ",
" / |   ",
" | |   ",
" |_|   ",
NULL
};

const char* number_2[] = {
"  ___  ",
" | _ ) ",
"  / /  ",
" /___| ",
NULL
};
const char* number_3[] = {
"  ____ ",
" |__ / ",
"  |_ \\ ",
" |___/ ",
NULL
};

const char* number_4[] = {
"  _ _  ",
" | | | ",
" |_  _|",
"  |_|  ",
NULL
};

const char* number_5[] = {

"  ___   ",
" | __|  ",
" |__ \\  ",
" |___/  ",
NULL
};
const char* number_6[] = {
"   __   ",
"  / /   ",
" / _ \\  ",
" \\___/  ",
NULL
};
const char* number_7[] = {
"  ____  ",
" |___ | ",
"   / /  ",
"  /_/   ",
NULL
};
const char* number_8[] = {

"  ___   ",
" ( _ )  ",
" / _ \\  ",
" \\___/  ",
NULL
};
const char* number_9[] = {

"  ___   ",
" / _ \\  ",
" \\_, /  ",
"  /_/   ",
NULL
};

const char** numbers[] = {
number_0,
number_1,
number_2,
number_3,
number_4,
number_5,
number_6,
number_7,
number_8,
number_9
};

//Slant font

const char* game_over[] = {
"                                                    ",
"   ______                      ____                 ",
"  / ____/___ _____ ___  ___   / __ \\_   _____  _____",
" / / __/ __ `/ __ `__ \\/ _ \\ / / / / | / / _ \\/ ___/",
"/ /_/ / /_/ / / / / / / __/ / /_/ /| |/ /  __/ /    ",
"\\____/\\__,_/_/ /_/ /_/\\___/ \\____/ |___/\\___/_/     ",
NULL
};
const char* game_keys[] = {
"       ____                    ",
"      ||^ ||                   ",
"      ||__||                   ",
"      |/__\\|                  ",
"  ____ ____ ____ _____________ ",
" ||< |||v |||> ||| SPACE BAR ||",
" ||__|||__|||__|||___________||",
" |/__\\|/__\\|/__\\|/___________\\|",
NULL
};



const char* controls_text[] = {
"  ___ ___  _  _ _____ ___  ___  _    ___       ",
" / __/ _ \\| \\| |_   _| _ \\/ _ \\| |  / __|  ",
"| (_| (_) | .` | | | |   / (_) | |__\\__ \\    ",
" \\___\\___/|_|\\_| |_| |_|_\\\\___/|____|___/ ",
"                                                ",
NULL
};

const char* ouch[] = {
"Ouch! Dont bite me you barbarian. ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
NULL
};

const char* ouch_variant1[] = {
"Hey! I'm fragile, not a chew toy!",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* ouch_variant2[] = {
"Yikes! That's no way to say hello!",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
NULL
};

const char* huh[] = {
"Huh, at least you figured out    ",
"the controls.                    ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* huh_variant1[] = {
"Wow, you managed to move the     ",
"damn snake.A true snake whisperer...",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* huh_variant2[] = {
"Not bad! The snake approves...   ",
"for now.                         ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* not_that_bad[] = {
"Hey, not bad! That's a... well,  ",
"let's call it a *decent* score.  ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* not_that_bad_variant1[] = {
"Alright, not too shabby!         ",
"You might actually impress a worm,",
"which you know its not much, but ",
"it's something!                  ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* not_that_bad_variant2[] = {
"Decent job! Let's just say it's  ",
"better than your last attempt.   ",
"Probably(?                       ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};


const char* impressed[] = {
"Alright, now we're getting       ",
"somewhere. I'll admit, you have  ",
"skills. Not quite at my level,   ",
"but you're on your way.          ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};


const char* impressed_1[] = {
"Impressive! I see you're no      ",
"ordinary player. Still, I've     ",
"seen better. Care to surprise    ",
"me more?                         ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* impressed_cs50[] = {
"Whoa, looks like you're          ",
"channeling your inner CS50 pro!  ",
"Impressive work, but remember,   ",
"even David Malan had to practice.",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* almost_there_comic_1[] = {
"You're almost there! Imagine if  ",
"you tripped now... embarrassing, ",
"right? So, uh, don't do that.    ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* almost_there_comic_2[] = {
"Wow, so close! If you mess up now,",
"even my grandma will judge you. ",
"She doesn't play games, but still.",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};

const char* almost_there_comic_3[] = {
"Almost there! The snakes are     ",
"rooting for you... or maybe not. ",
"Honestly, I can't tell.Keep going!",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
"                                 ",
NULL
};



const char* worm1[] = {
"                (o)(o)             ",
"               /     \\    LISAN  AL",
"              /       |      GAIB!",
"             /   \\  * |   100 points",
"_______     /    /\\__/          ",
"       \\   /    /               ",
" ____    \\_/    /               ",
" /    \\         /               ",
"/      \\       /                ",
"        \\_____/                 ",
NULL
};

const char* worm2[] = {
"                (o)(-)  ",
"               /     \\             ",
"              /       |   <<Nice>>  ",
"             /   \\  * |             ",
"_______     /    /\\__/              ",
"       \\   /    /               ",
" ____    \\_/    /  Im proud of you.",
" /    \\         /               ",
"/      \\       /                ",
"        \\_____/                 ",
NULL
};

const char* worm3[] = {
"                (o)(o)              ",
"               /     \\             ",
"              /       |  < <Nice> >",
"             /   \\  * |             ",
"_______     /    /\\__/              ",
"       \\   /    /               ",
" ____    \\_/    /  Im proud of you.",
" /    \\         /               ",
"/      \\       /                ",
"        \\_____/                 ",
NULL
};

const char* fireworks_1[] = {
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"        |        |                ",
NULL
};

const char* fireworks_2[] = {
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"        |        |                ",
"        |        |                ",
"            |                     ",
NULL
};

const char* fireworks_3[] = {
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"        |        |                ",
"        |        |                ",
"            |                     ",
"                                  ",
"                                  ",
NULL
};

const char* fireworks_4[] = {
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"        |        |                ",
"        |        |                ",
"            |                     ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
NULL
};

const char* fireworks_5[] = {
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"        **       |                ",
"        *        |                ",
"            |                     ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
NULL
};

const char* fireworks_6[] = {
"                                  ",
"                                  ",
"                 *                ",
"        *       **                ",
"      .***       |                ",
"       ***. |                     ",
"        *                         ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
NULL
};
const char* fireworks_7[] = {
"                                  ",
"                                  ",
"                .***.             ",
"       . *     .*****.            ",
"      .** **                      ",
"      **  *. **                   ",
"      . **   *                    ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
NULL
};

const char* fireworks_8[] = {
"                                  ",
"                                  ",
"               .******.           ",
"       . *   .***....***....      ",
"     .**  * **... ....  ***..     ",
"  *.,  .   *. **vv      ...       ",
" .  , . * *   v*v                 ",
"       . *     v                  ",
"   ,  ,  . ,                      ",
"    ,   ,                         ",
"                                  ",
"                                  ",
NULL
};
const char* fireworks_9[] = {
"                                  ",
"                                  ",
"                                  ",
"              ;;;;;;;;.           ",
"       . .***..;;;;;..***....     ",
"     ..* ,* **... ....  ***..     ",
"   .,  .   *. **;;      ...       ",
" .  , . . *   ;*;  v  ******      ",
"    *  . *   v  v v      ,,,      ",
"   ,  ,* . ,  v  v                ",
"    ,   ,     ,  ,                ",
"               v                  ",
NULL
};

const char* fireworks_10[] = {
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"       .           , .. ..        ",
"         ,. ;;. . . ..   * ..     ",
"   ,  .   *. * ; ;      ...       ",
"    . .     ; ;  `     ; ; ;      ",
"     *  .     `  ` v       ,,,    ",
"      ,* . ,  `  `                ",
NULL
};

const char* fireworks_11[] = {
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"         !CONGRATULATIONS!        ",
"            100 points            ",
"       .           , .. ..        ",
"         ,. ;;. . . ..   * ..     ",
"   ,  .   *. * ; ;      ...       ",
"    . .     ; ;  `     ; ; ;      ",
NULL
};
const char* fireworks_12[] = {
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
"      !!!!CONGRATULATIONS!!!!     ",
"            100 points            ",
"                                  ",
"                                  ",
"                                  ",
"                                  ",
NULL
};


const char* thumbs_up[] = {
"         __                      ",
"         ) )             You are! ",
"         \\ =\\                   ",
"         \\` __\\______          ",
"    ----/ )    ((____)           ",
"          __   ((____)           ",
"              ((____)            ",
"    ----\\_____((___)             ",
NULL
};

const char* happy_face[] = {
"    .oOOOOOOo.                     ",
" oO'          'Oo   --- AWESOME--- ",
"O'   O      O   'O    100 points   ",
"O                O                 ",
"O                O                 ",
"O  Oo,      ,oO  O                 ",
" O. 'OOOOOOOO' .O                  ",
"  Yb.        .dP                   ",
"    'YOOOOOOP'                     ",
NULL
};

const char* happy_face_2[] = {
"    .oOOOOOOo.                     ",
" oO'          'Oo  - -- AWESOME-- -",
"O'   O      __  'O    100 points  ",
"O                O                 ",
"O                O                 ",
"O  Oo,      ,oO  O                 ",
" O. 'OOOOOOOO' .O                  ",
"  Yb.        .dP                   ",
"    'YOOOOOOP'                     ",
NULL
};


const char* blank[] = {
"                                    ",
"                                    ",
"                                    ",
"                                    ",
"                                    ",
"                                    ",
"                                    ",
"                                    ",
"                                    ",
"                                    ",
"                                    ",
"                                    ",
NULL
};

const char* bigBlank[] = {
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
"                                                                                                                                     ",
NULL
};

const char* arena3[] = {
"+-----------------------------------------------------------------------------------------------------------------------------------+",
"|/------------------------------------------------------------------------------------------/--------------------------------------\\|",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |______________________________________||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"||                                                                                          |                                      ||",
"|\\------------------------------------------------------------------------------------------\\--------------------------------------/|",
"+-----------------------------------------------------------------------------------------------------------------------------------+",
NULL
};

const char* arenaPiece1[] = {
"+--------------------------------------------------------------------------------------------",
"|/-------------------------------------------------------------------------------------------",
NULL
};

const char* arenaPiece2[] = {
"|\\------------------------------------------------------------------------------------------",
"+-------------------------------------------------------------------------------------------",
NULL
};

const char* arenaPiece3[] = {
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
"||",
NULL
};

const char* arenaPiece4[] = {
"----------------------------------------+",
"/--------------------------------------\\|",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|______________________________________||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"|                                      ||",
"\\--------------------------------------/|",
"----------------------------------------+",
NULL
};




const char* top[] = {
"|TOP  ",
NULL
};


void titleErasser()
{
    for (int i = 0; i < 126; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("\x1b[%d;%dH%s // ", 14 + j, i, ANSI_COLOR_DARK_ORANGE);

        }
        Sleep(17);
    }
}
