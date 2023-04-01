#ifndef ITEMSIZEWIDGET_H
#define ITEMSIZEWIDGET_H

#include <QWidget>
#include <QGraphicsPixmapItem>

namespace Ui {
class itemsizeWidget;
}

class itemsizeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit itemsizeWidget(QWidget *parent = nullptr, QGraphicsPixmapItem *item = nullptr);
    QGraphicsPixmapItem *item;
    QPixmap itemPixmap;
    void setItem(QGraphicsPixmapItem *bufItem);
    QSize itemSize;
    ~itemsizeWidget();

private slots:
    void on_verticalSlider_valueChanged(int value);

private:
    Ui::itemsizeWidget *ui;
};

#endif // ITEMSIZEWIDGET_H
