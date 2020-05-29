#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define RSHIFT 0x36
#define LSHIFT 0x2a
#define CAPSLOCK 0x3a

uint8_t is_Caps;
uint8_t on_Shift;

char asccode[58][2] = /* Array containing ascii codes for
                         appropriate scan codes */
    {
        {0, 0},      {0x1b, 0x1b},  // ESC
        {'1', '!'},  {'2', '@'},   {'3', '#'}, {'4', '$'}, {'5', '%'},
        {'6', '^'},  {'7', '&'},   {'8', '*'}, {'9', '('}, {'0', ')'},
        {'-', '_'},  {'=', '+'},   {8, 8},  // backsapce
        {9, 9},                             // tab
        {'q', 'Q'},  {'w', 'W'},   {'e', 'E'}, {'r', 'R'}, {'t', 'T'},
        {'y', 'Y'},  {'u', 'U'},   {'i', 'I'}, {'o', 'O'}, {'p', 'P'},
        {'[', '{'},  {']', '}'},   {13, 13},  // enter
        {0, 0},                               // Lctrl
        {'a', 'A'},  {'s', 'S'},   {'d', 'D'}, {'f', 'F'}, {'g', 'G'},
        {'h', 'H'},  {'j', 'J'},   {'k', 'K'}, {'l', 'L'}, {';', ':'},
        {39, 34},    {'`', '~'},   {0, 0},  // Lshift
        {'\\', '|'}, {'z', 'Z'},   {'x', 'X'}, {'c', 'C'}, {'v', 'V'},
        {'b', 'B'},  {'n', 'N'},   {'m', 'M'}, {',', '<'}, {'.', '>'},
        {'/', '?'},  {0, 0},  // Rshift
        {0, 0},      {0, 0},  // Lalt
        {' ', ' '},           // space bar
};

#endif