#include "rl4reader.h"
#include "rl4_headers.h"
#include <fstream>
#include <iostream>

using namespace std;

RL4reader::RL4reader(){};

void RL4reader::readRL4file(string filepath) {
    ifstream file(filepath, ios::binary);
        // Создаем заголовок файла
        TRLIFileHeader header{};
        // Считываем сигнатуру файла
        file.read(header.fileSign, 4);
        cout << "File signature: " << header.fileSign << endl;
        // Считываем версию файла
        file.read((char *) &header.fileVersion, sizeof(header.fileVersion));
        cout << "File version: " << header.fileVersion << endl;

        TGOLFileParams &golParams = header.GOLFileParams;
        file.read((char *) &golParams, sizeof(golParams));
        cout << "GOL file params:" << endl;
        cout << "File time: " << &golParams.fileTime << endl;
        cout << "File length: " << golParams.fileLength << endl;
        cout << "File header length: " << golParams.fileHeaderLength << endl;
        cout << "File tail length: " << golParams.fileTailLength << endl;
        cout << "Type: " << golParams.type - ' ' + ' ' << endl;
        cout << "String header length: " << golParams.strHeaderLength << endl;
        cout << "String signal count: " << golParams.strSignalCount << endl;
        cout << "Cadr width: " << golParams.cadrWidth << endl;
        cout << "Cadr height: " << golParams.cadrHeight << endl;
        cout << "Width: " << golParams.width << endl;
        cout << "Height: " << golParams.height << endl;
        cout << "Dummy4: " << golParams.dummy4 << endl;
        cout << "Dx: " << golParams.dx << endl;
        cout << "Dy: " << golParams.dy << endl;
        cout << "File name: " << golParams.filename << endl;
        cout << endl;

        TRLIFileParams &rliParams = header.RLIFileParams;
        file.read((char *) &rliParams, sizeof(rliParams));

        cout << "RLI file params" << endl;
        cout << "File length: " << rliParams.fileLength << endl;
        cout << "File header length: " << rliParams.fileHeaderLength << endl;
        cout << "File tail length: " << rliParams.fileTailLength << endl;
        cout << "Type: " << rliParams.type << endl;
        cout << "Str header length: " << rliParams.strHeaderLength << endl;
        cout << "Str signal count: " << rliParams.strSignalCount << endl;
        cout << "Cadr width: " << rliParams.cadrWidth << endl;
        cout << "Cadr height: " << rliParams.cadrHeight << endl;
        cout << "Width: " << rliParams.width << endl;
        cout << "Height: " << rliParams.height << endl;
        cout << "Frames: " << rliParams.frames << endl;
        cout << "Process time: " << rliParams.processTime << endl;
        cout << "Process i: " << rliParams.processi << endl;
        cout << "Process j: " << rliParams.processj << endl;
        cout << "U0: " << rliParams.u0 << endl;
        cout << "U1: " << rliParams.u1 << endl;
        cout << "V0: " << rliParams.v0 << endl;
        cout << "V1: " << rliParams.v1 << endl;
        cout << "Range type: " << rliParams.rangeType << endl;
        cout << "DX: " << rliParams.dx << endl;
        cout << "DY: " << rliParams.dy << endl;
        cout << "Flip type: " << rliParams.flipType << endl;
        cout << "SX: " << rliParams.sx << endl;
        cout << "SY: " << rliParams.sy << endl;
        cout << "Calibration rli: " << rliParams.calibration_rli << endl;
        cout << "SX: " << rliParams.sx << endl;
        cout << "File name: " << rliParams.fileName << endl;
        cout << endl;

        TSynthParams &synthParams = header.SynthParams;
        file.read((char *) &synthParams, sizeof(synthParams));

        file.read((char *) &header.aligningPointsCount, sizeof(header.aligningPointsCount));
        file.read((char *) &header.rangeCompressionCoef, sizeof(header.rangeCompressionCoef));
        file.read((char *) &header.azimuthCompressionCoef, sizeof(header.azimuthCompressionCoef));
        file.read((char *) &header.reserved, sizeof(header.reserved));
        cout << "Aligning points count: " << header.aligningPointsCount << endl;
        cout << "Range compression coef: " << header.rangeCompressionCoef << endl;
        cout << "Azimuth compression coef: " << header.azimuthCompressionCoef << endl;

        //Read rli picture
        cout << rliParams.height << ' ' << rliParams.width << endl;
        TRLIStrHeader *strHeader = NULL;
        float** picture = NULL;
        picture = new float *[rliParams.height];
        strHeader = new TRLIStrHeader[rliParams.height];
        float maxFloat = 0;
        float minFloat = 1000000;
        for (int i = 0; i < rliParams.height; ++i) {
            picture[i] = new float[rliParams.width];
            file.read((char *) &strHeader[i], sizeof(TRLIStrHeader));
            for (int j = 0; j < rliParams.width; j++) {
                file.read((char *) &picture[i][j], sizeof(float));
                if (picture[i][j] > maxFloat)
                    maxFloat = picture[i][j];
                if (picture[i][j] < minFloat)
                    minFloat = picture[i][j];
            }
        }
        cout << "Max float: " << maxFloat << endl;
        cout << "Min float: " << minFloat << endl;

        this->norm = this->CountNorm(rliParams.width, rliParams.height, picture, maxFloat);
        cout << this->norm << endl;
        QImage* bufImage = new QImage(rliParams.width, rliParams.height, QImage::Format_RGB32);
        for(int y = 0; y < rliParams.height; ++y) {
            for(int x = 0; x < rliParams.width; ++x) {
                if (picture[y][x] < (float)this->norm) {
                    picture[y][x] = ((picture[y][x] - minFloat) / (float) this->norm) * 255;
                } else {
                    picture[y][x] = 255;
                }
                bufImage->setPixel(x, y, qRgb((int)picture[y][x], (int)picture[y][x], (int)picture[y][x]));
            }
        }
        bufImage->save("/home/acer/praktika/rl4_reader_qt/RL4_reader/rl4_pictures/picture.jpg", 0, -1);
        this->header = header;
        this->picture = picture;
        this->image = bufImage;
}

int RL4reader::CountNorm(int width, int height, float** picture, float h) {
    int* g;
        g = new int[(int)h];
        for(int i = 0; i < (int)h; ++i) {
            g[i] = 0;
        }
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                g[(int)picture[i][j]]++;
            }
        }
        int pixelsCountToGet = width * height * 0.99;
        cout << width * height << endl;
        int countPixels = 0;
        for(int i = 0; i < h; i++) {
            countPixels += g[i];
            if (countPixels >= pixelsCountToGet) {
                return i;
            }
        }
}
