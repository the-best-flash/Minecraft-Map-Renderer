#ifndef _COLOR_H_
#define _COLOR_H_

typedef unsigned char uchar;

class Color
{
public:
    uchar r, g, b, a;
    
    Color(uchar red = 0, uchar green = 0, uchar blue = 0, uchar alpha = 255) :
    r(red), g(green), b(blue), a(alpha)
    {
    
    }
}; 

#endif 
