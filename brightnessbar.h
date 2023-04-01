#ifndef BRIGHTNESSBAR_H
#define BRIGHTNESSBAR_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QSlider>
#include <QLabel>
#include <QPixmap>

namespace Ui {
class BrightnessBar;
}

class BrightnessBar : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrightnessBar(QWidget *parent = nullptr, QImage *image = nullptr, QGraphicsPixmapItem *pixmap = nullptr, QGraphicsScene *scene = nullptr);
    ~BrightnessBar();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_sliderReleased();

private:
    int brightnessLevel;
    QImage *image;
    QImage copyImage;
    QSlider *slider;
    QLabel *label;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmap;
    Ui::BrightnessBar *ui;
};

#endif // BRIGHTNESSBAR_H
