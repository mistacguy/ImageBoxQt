#include "hbmp24.h"
#include <QDebug>
using namespace std;

hBmp24::hBmp24()
{

}

bool hBmp24::load(string filename)
{

    fstream f(filename, ios::in);
    if(!f)
    {
        return false;
    }
    f.read((char*)fileHead, sizeof(BITMAPFILEHEADER));
    f.read((char*)&infor->bmiHeader, sizeof(BITMAPINFOHEADER));
    int width = infor->bmiHeader.biWidth;
    int height = infor->bmiHeader.biHeight;
    int step = WIDBYTE(width*24) - width*3;
    BYTE *data = new BYTE[infor->bmiHeader.biSizeImage];
    f.read((char*)data, infor->bmiHeader.biSizeImage);
    f.close();

    int index = 0;
    infor->bmiColors = new RGBQUAD*[height];
    for(int i = 0; i < height; i++)
    {
        infor->bmiColors[i] = new RGBQUAD[width];
        for(int j = 0; j < width; j++)
        {
            infor->bmiColors[i][j].rgbBlue = data[index++];
            //qDebug()<<infor->bmiColors[i][j].rgbBlue;
            infor->bmiColors[i][j].rgbGreen = data[index++];
            infor->bmiColors[i][j].rgbRed = data[index++];
            infor->bmiColors[i][j].rgbReserved = 0;
        }
        index+=step;
    }
    free(data);;
    return true;
}

bool hBmp24::save()
{
    fstream f("catch.bmp", ios::out);
    if(!f)
    {
        return false;
    }
    int width = infor->bmiHeader.biWidth;
    int height = infor->bmiHeader.biHeight;
    int step = WIDBYTE(width*24) - width*3;
    BYTE stuff = 0;
    f.write((char*)fileHead, sizeof(BITMAPFILEHEADER));
    f.write((char*)&infor->bmiHeader, sizeof(BITMAPINFOHEADER));
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            f.write((char*)&infor->bmiColors[i][j],3);
             //qDebug()<<infor->bmiColors[i][j].rgbBlue;

        }
        for(int k = 0; k < step; k++)
        {
            f.write((char*)&stuff,1);
        }
    }
    f.close();
    return true;
}

void hBmp24::invert()
{
    for(int i = 0; i < infor->bmiHeader.biHeight; i++)
    {
        for(int j = 0; j < infor->bmiHeader.biWidth; j++)
        {
            infor->bmiColors[i][j].rgbBlue = 255 - infor->bmiColors[i][j].rgbBlue;
            infor->bmiColors[i][j].rgbGreen = 255 - infor->bmiColors[i][j].rgbGreen;
            infor->bmiColors[i][j].rgbRed = 255 - infor->bmiColors[i][j].rgbRed;
        }
    }
}

void hBmp24::flipHorizontal()
{
    int width = infor->bmiHeader.biWidth;
    int height = infor->bmiHeader.biHeight;
    RGBQUAD **catchs = new RGBQUAD*[height];
    for(int i = 0; i < height; i++)
    {
        catchs[i] = new RGBQUAD[width];
        for(int j = 0; j < width; j++)
        {
            catchs[i][j].rgbBlue = infor->bmiColors[i][width - j - 1].rgbBlue;
            catchs[i][j].rgbGreen = infor->bmiColors[i][width - j - 1].rgbGreen;
            catchs[i][j].rgbRed = infor->bmiColors[i][width - j - 1].rgbRed;
            catchs[i][j].rgbReserved = 0;
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            infor->bmiColors[i][j].rgbBlue = catchs[i][j].rgbBlue;
            infor->bmiColors[i][j].rgbGreen = catchs[i][j].rgbGreen;
            infor->bmiColors[i][j].rgbRed = catchs[i][j].rgbRed;
        }
        free(catchs[i]);
    }
    free(catchs);
}

void hBmp24::flipVertical()
{
    int width = infor->bmiHeader.biWidth;
    int height = infor->bmiHeader.biHeight;
    RGBQUAD **catchs = new RGBQUAD*[height];
    for(int i = 0; i < height; i++)
    {
        catchs[i] = new RGBQUAD[width];
        for(int j = 0; j < width; j++)
        {
            catchs[i][j].rgbBlue = infor->bmiColors[height - i - 1][j].rgbBlue;
            catchs[i][j].rgbGreen = infor->bmiColors[height - i - 1][j].rgbGreen;
            catchs[i][j].rgbRed = infor->bmiColors[height - i - 1][j].rgbRed;
            catchs[i][j].rgbReserved = 0;
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            infor->bmiColors[i][j].rgbBlue = catchs[i][j].rgbBlue;
            infor->bmiColors[i][j].rgbGreen = catchs[i][j].rgbGreen;
            infor->bmiColors[i][j].rgbRed = catchs[i][j].rgbRed;
        }
        free(catchs[i]);
    }
    free(catchs);
}

void hBmp24::toGrayScale()
{
    //Gray = (R*19595 + G*38469 + B*7472) >> 16
    for(int i = 0; i < infor->bmiHeader.biHeight; i++)
    {
        for(int j = 0; j < infor->bmiHeader.biWidth; j++)
        {
            infor->bmiColors[i][j].rgbBlue = (15*infor->bmiColors[i][j].rgbBlue+
                                              75*infor->bmiColors[i][j].rgbGreen+
                                              38*infor->bmiColors[i][j].rgbRed)>>7;
            infor->bmiColors[i][j].rgbGreen = (15*infor->bmiColors[i][j].rgbBlue+
                                               75*infor->bmiColors[i][j].rgbGreen+
                                               38*infor->bmiColors[i][j].rgbRed)>>7;
            infor->bmiColors[i][j].rgbRed = (15*infor->bmiColors[i][j].rgbBlue+
                                             75*infor->bmiColors[i][j].rgbGreen+
                                             38*infor->bmiColors[i][j].rgbRed)>>7;
        }
    }

}

bool hBmp24::save(string filename)
{

}
