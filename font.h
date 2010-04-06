/* This file is used for storing font definition. */

#ifndef FONT_H
#define FONT_H

namespace
{
    const bool SPACE[8][8] =
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 } };
    const bool COLON[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0, 0 } };
    const bool ZERO[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 } };
    const bool ONE[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0, 0 },
          { 0, 0, 1, 1, 1, 0, 0, 0 },
          { 0, 0, 1, 1, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0, 0 } };
    const bool TWO[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 0, 0, 0, 1, 1, 1, 0 },
          { 0, 0, 1, 1, 1, 1, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 } };
    const bool THREE[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 0, 0, 0, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 } };
    const bool FOUR[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 0, 0, 0, 0, 1, 1, 0 },
          { 0, 0, 0, 0, 0, 1, 1, 0 } };
    const bool FIVE[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 0, 0, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 } };
    const bool SIX[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 } };
    const bool SEVEN[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 0, 0, 0, 1, 1, 0 },
          { 0, 0, 0, 0, 1, 1, 1, 0 },
          { 0, 0, 0, 0, 1, 1, 0, 0 },
          { 0, 0, 0, 0, 1, 1, 0, 0 },
          { 0, 0, 0, 0, 1, 1, 0, 0 } };
    const bool EIGHT[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 } };
    const bool NINE[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 0, 0, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 } };
    const bool F_CAPITAL[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 0, 0, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 } };
    const bool P_CAPITAL[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 } };
    const bool S_CAPITAL[8][8] = 
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 0, 0, 0, 0, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 0, 0, 0, 0, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 1, 0 } };
    const bool UNKNOWN[8][8] =
        { { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 },
          { 0, 0, 0, 0, 0, 0, 0, 0 } };
}

typedef bool PixelArray[8][8];

/* This function returns array 8x8 of bool values, where 1 means black color of
 * pixel and 0 means transparent color of pixel. */
const PixelArray &get_character(char character)
{
    switch(character)
    {
    case ' ':
        return SPACE;
    case ':':
        return COLON;
    case '0':
        return ZERO;
    case '1':
        return ONE;
    case '2':
        return TWO;
    case '3':
        return THREE;
    case '4':
        return FOUR;
    case '5':
        return FIVE;
    case '6':
        return SIX;
    case '7':
        return SEVEN;
    case '8':
        return EIGHT;
    case '9':
        return NINE;
    case 'F':
        return F_CAPITAL;
    case 'P':
        return P_CAPITAL;
    case 'S':
        return S_CAPITAL;
    default:
        return UNKNOWN;
    }
}

#endif // FONT_H
