#include "brightnessbar.h"
#include "ui_brightnessbar.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <string>

using namespace std;

BrightnessBar::BrightnessBar(QWidget *parent, QImage *image, QGraphicsPixmapItem* pixmap, QGraphicsScene *scene) :
    QMainWindow(parent),
    ui(new Ui::BrightnessBar)
{
    ui->setupUi(this);
    ui->brightnessLabel->setText("Ярксоть изображения: 0");
    ui->horizontalSlider->setRange(0, 255);
    this->setWindowTitle("Brightness level");

    this->image = image;
    this->copyImage = *this->image;
    this->pixmap = pixmap;
    this->scene = scene;
}

BrightnessBar::~BrightnessBar()
{
    delete ui;
}

void BrightnessBar::on_horizontalSlider_valueChanged(int action)
{
    this->brightnessLevel = action;
    string a = "Яркость изображения: " + to_string(action);
    ui->brightnessLabel->setText(QString::fromStdString(a));
}

void BrightnessBar::on_horizontalSlider_sliderReleased()
{
    for(size_t i = 0; i < this->image->width(); ++i) {
        for(size_t j = 0; j < this->image->height(); ++j) {
            QColor color = this->image->pixelColor(i, j);
            QColor copyColor = this->copyImage.pixelColor(i, j);
            if(color.blue() + this->brightnessLevel > 255) {
                copyColor.setRgbF(255, 255, 255);
            } else {
                copyColor.setBlue(color.blue() + this->brightnessLevel);
                copyColor.setRed(color.red() + this->brightnessLevel);
                copyColor.setGreen(color.green() + this->brightnessLevel);
            }
            this->copyImage.setPixelColor(i, j, copyColor);
        }
    }
    this->pixmap->setPixmap(QPixmap::fromImage(copyImage));
    this->scene->update(this->scene->itemsBoundingRect());
}

