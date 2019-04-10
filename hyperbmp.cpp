#include "hyperbmp.h"

using namespace std;

hyperBmp::hyperBmp()
{
    fileHead = new BITMAPFILEHEADER;
    infor = new BITMAPINFO;

}

string hyperBmp::showInformation()
{
    string s = "type:"+string((fileHead->bfType==19778)?"BMP":"UNKWNO")+
               " size:"+to_string((float)fileHead->bfSize/1024)+
               " width:"+to_string(infor->bmiHeader.biWidth)+
               " height:"+to_string(infor->bmiHeader.biHeight)+
               " count:"+to_string(infor->bmiHeader.biBitCount);
    return s;

}


