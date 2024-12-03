#ifndef UTILS_H
#define UTILS_H

void windowManagement(int wind_x, int wind_y, int wind_h, int wind_w);
int randomBetween(int min, int max);
void right_align(const char* text[],int textX);
void get_console_font_size(int* FontSizeY, int* FontSizeX);
void textPositioning(const char* text[],int textX, int textY);
#endif // UTILS_H