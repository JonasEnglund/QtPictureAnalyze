#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QLabel>
#include "brightnessbar.h"
#include "objects.h"
#include "objectstoolbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int sizeX = 0, int sizeY = 0, QImage *image = nullptr);
    BrightnessBar *brightnessBar;
    objects *obj;
    ObjectsToolbar *toolBar;
    int *drawMode;
    QIcon *iconToDraw;
    QGraphicsPixmapItem *picturePixmap;
    QGraphicsScene *scene;
    QImage *image;
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_action_2_toggled(bool arg1);

    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
