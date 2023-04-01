#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QIcon>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent, int sizeX, int sizeY, QImage *image) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setting window parameters
    this->setWindowTitle("RL4 picture");
    this->setFixedSize(sizeX, sizeY);
    //setting local variables
    this->image = new QImage;
    this->image = image;
    this->drawMode = new int;
    *drawMode = 0;
    this->toolBar = new ObjectsToolbar;
    this->toolBar->move(this->pos().x() + sizeX, 0);
    this->iconToDraw = new QIcon;
    scene = new QGraphicsScene(this);
    picturePixmap = new QGraphicsPixmapItem;
    picturePixmap->setPixmap(QPixmap::fromImage(*this->image));
    scene->addItem(picturePixmap);
    ui->graphicsView->resize(sizeX, sizeY - 45);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->drawMode = this->drawMode;
    ui->graphicsView->iconToDraw = this->iconToDraw;
    ui->graphicsView->scene = this->scene;
    ui->graphicsView->toolButton = this->ui->toolButton;
    ui->action_2->setCheckable(true);
    ui->toolButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
   this->brightnessBar->show();
}

void MainWindow::on_action_2_toggled(bool arg1)
{
   if(arg1) {
    this->toolBar->show();
    this->ui->toolButton->show();
   }
   else {
    this->ui->toolButton->hide();
    //this->toolBar->hide();
   }
}

void MainWindow::on_toolButton_clicked()
{
   this->obj->show();
}

