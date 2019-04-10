#ifndef HBMP24_H
#define HBMP24_H
#include <hyperbmp.h>
#include <fstream>

class hBmp24 : public hyperBmp
{
public:
    hBmp24();
    void invert();
    void flipHorizontal();
    void flipVertical();
    void toGrayScale();
    virtual bool load(string);
    virtual bool save(string);
    virtual bool save();
};

#endif // HBMP_24H
