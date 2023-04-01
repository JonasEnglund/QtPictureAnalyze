#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <vector>
#include <QToolButton>
#include "itemsizewidget.h"

class Custom_View : public QGraphicsView
{
public:
    explicit Custom_View(QWidget *parent = nullptr);
    int m_originX;
    int m_originY;
    int *drawMode;
    bool selectionMode;
    QIcon *iconToDraw;
    QToolButton *toolButton;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *selectedItem;
    itemsizeWidget *itemWidget;
    double scaleLevel;
    std::vector<QGraphicsPixmapItem*> items;
    //std::vector<QGraphicsPixmapItem*> items;

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    bool checkItemUnderMouse(QGraphicsPixmapItem* item, int posX, int posY);
    using QGraphicsView::QGraphicsView;
};

#endif // CUSTOM_VIEW_H
