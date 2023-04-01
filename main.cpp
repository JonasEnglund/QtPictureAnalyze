#include "mainwindow.h"
#include "brightnessbar.h"
#include <QApplication>
#include "rl4reader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RL4reader rl4reader = RL4reader();
    rl4reader.readRL4file("/home/acer/Diplom/CPP/rl4_files/arm21_20221012_s012_001_20_25-2.rl4");
    MainWindow w(nullptr, rl4reader.header.RLIFileParams.width, rl4reader.header.RLIFileParams.height, rl4reader.image);
    w.brightnessBar = new BrightnessBar(nullptr, w.image, w.picturePixmap, w.scene);
    w.obj = new objects(nullptr, w.drawMode, w.iconToDraw);
    w.show();
    return a.exec();
}
