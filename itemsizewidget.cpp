#include "itemsizewidget.h"
#include "ui_itemsizewidget.h"
#include <iostream>

using namespace std;

itemsizeWidget::itemsizeWidget(QWidget *parent, QGraphicsPixmapItem *item) :
    QWidget(parent),
    ui(new Ui::itemsizeWidget)
{
    ui->setupUi(this);
    if(item != nullptr) {
        this->item = item;
        this->itemSize.setHeight(item->pixmap().height());
        this->itemSize.setWidth(item->pixmap().width());
        this->itemPixmap = item->pixmap();
    }
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

void itemsizeWidget::setItem(QGraphicsPixmapItem *bufItem)
{
    this->item = bufItem;
    this->itemSize.setHeight(bufItem->pixmap().height());
    this->itemSize.setWidth(bufItem->pixmap().width());
    itemPixmap = item->pixmap();
}

itemsizeWidget::~itemsizeWidget()
{
    delete ui;
}

void itemsizeWidget::on_verticalSlider_valueChanged(int value)
{
    QSize itemPixmapSize(this->itemSize.width() / value, this->itemSize.height() / value);
    QPixmap bufItemPixmap = itemPixmap.scaled(itemPixmapSize, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    item->setPixmap(bufItemPixmap);
}

