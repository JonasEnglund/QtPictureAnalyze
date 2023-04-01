#ifndef RL4_HEADERS_H
#define RL4_HEADERS_H

#pragma pack (push, 1)

#include <tiff.h>
#include <ctime>
#include <limits.h>

using namespace std;

struct TGOLFileParams
{
    // время создания
     char fileTime[16];

    // формат файла
    int64_t fileLength;
    int64_t fileHeaderLength;
    int64_t fileTailLength;

    // тип файла
    char type; // 255
    // формат строки
    int strHeaderLength;
    char dummy1[8];
    int strSignalCount;

    // размер кадра
    int cadrWidth;
    int cadrHeight;

    // размер изображения
    int width;
    int height;
    char dummy4[4];

    char reserved1[49];

    float dx;
    float dy;

    char reserved2[3697];

    char filename[256];

    char reserved3[9];
};

struct TRLIFileParams
{
    // время создания
    char fileTime[16];

    // формат файла
    int64_t fileLength;
    int64_t fileHeaderLength;
    int64_t fileTailLength;

    // тип файла
    char type; // 2 - float, 3 - {float, float} (комплексное число)

    // формат строки
    int strHeaderLength;
    char dummy1[8];
    int strSignalCount;

    // размер кадра
    int cadrWidth;
    int cadrHeight;

    // размер изображения
    int width;
    int height;
    int frames;

    // время синтеза
    char processTime[16];

    // размер соответствующего фрагмента РГГ
    int processi;
    int processj;

    // параметры упаковки
    float u0;
    float u1;

    int v0;
    int v1;

    char reserved2[8];

    // проекция
    char rangeType;

    // шаг разложения
    float dx;
    float dy;//азимут

    // флип
    char flipType;

    // смещение фрагмента изображения
    int sx;
    int sy;

// калибровка РЛИ
    char calibration_rli; // 0 – не калибровано (амплитуда) 1- не калибровано (мощность),  2– калибровано , ЭПР амплитуды, 3 – калибровано, ЭПР квадратный метр, 4 – калибровано, ЭПР в дБ кв.м.

    char reserved3[3687];

    char fileName[256];

    char reserved4[9];
};

struct TSynthParams
{
    // алгоритм синтеза
    char processAlgorithm; // 255

    // параметры привязки/носителя
    bool isHeaders1;
    bool isHeaders2;

    // дальность
    float D0;
    float dD;
    char board; // 0 – левый, 1 - правый

    char reserved1[48];

    // параметры сигнала
    float VH;
    float lambda;
    float Fn;

    char reserved2[842];

    // диапазон синтеза по азимуту
    bool isProcessAlli;
    int i1;
    int i2;

    // диапазон синтеза по дальности
    bool isProcessAllj;
    int j1;
    int j2;

    char reserved3[9];

    // параметры упаковки
    char type; // 2 - float, 3 - {float, float}

    float u0;
    float u1;

    int v0;
    int v1;

    // комментарий
    char comments[512];

    char reserved4[20];

    // размер кадра
    int cadrWidth;
    int cadrHeight;

    // дальность
    char rangeType;

    // ближний край полосы
    char flipType;

    // поляризация
    char polarization; //0 – ВВ, 1 – ГГ, 2 – ВГ, 3 – ГВ

    // Угол зондирования относительно вектора скорости
    float angle_zond; // +/- 90 градусов

    //char reserved5[887];
    char reserved5[678];
    int rgg_SY; // смещение начала кадра по азимуту в РГГ
    char reserved51[205];

    char rhgName[128];

    char reserved6[1576];
};

struct TRLIFileHeader {
    // сигнатура
    char fileSign[4];

    // версия
    int fileVersion;

    // подзаголовок РГГ
    TGOLFileParams GOLFileParams;

    // подзаголовок РЛИ
    TRLIFileParams RLIFileParams;

    // подзаголовок параметров синтеза
    TSynthParams SynthParams;

    // количество точек выравнивания
    int aligningPointsCount;
    // коэффициент сжатия по дальности
    float rangeCompressionCoef;
    // коэффициент сжатия по азимуту
    float azimuthCompressionCoef;

    char reserved[4076];
};

struct TRLIStrHeader {
    bool isNavigation;

    char time[16];

    double LatSNS;
    double LongSNS;
    double Hsns;

    double latitude;
    double longtitude;

    double H;
    double V;

    double Ve;
    double Vn;

    double a;

    double g;
    double f;
    double w;

    double Vu;

    double WH;

    char reserved[119];
};


#endif // RL4_HEADERS_H
