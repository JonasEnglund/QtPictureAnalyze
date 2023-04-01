#ifndef RL4READER_H
#define RL4READER_H
#include "rl4_headers.h"
#include <iostream>
#include <QImage>
using namespace std;

class RL4reader
{
public:
    TRLIFileHeader header;
    float** picture;
    int norm;
    QImage *image;
    int CountNorm(int width, int heigth, float** picture, float maxfloat);
    RL4reader();
    void readRL4file(string filepath);
};

#endif // RL4READER_H
