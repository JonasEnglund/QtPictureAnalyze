#include "custom_view.h"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QIcon>
#include "itemsizewidget.h"

using namespace std;

bool checkButtonPosition(QToolButton *button, int x, int y) {
    if(x > button->pos().x() && x < button->pos().x() + button->width()) {
        if(y > button->pos().y() && y < button->pos().y() + button->height()) {
            return true;
        }
    }
    return false;
}

bool Custom_View::checkItemUnderMouse(QGraphicsPixmapItem* item, int posX, int posY) {
    cout << "Координаты объекта: x1 - " << item->pos().x() << " y1 - " << item->pos().y() << " x2 - " << item->pos().x() + item->pixmap().width() << " y2 - " << item->pos().y() + item->pixmap().height() << endl;
    cout << posX << ' ' << posY << endl;
    if(posX * scaleLevel > item->pos().x() && posX * scaleLevel < item->pos().x() + item->pixmap().width()) {
        if(posY * scaleLevel > item->pos().y() && posY * scaleLevel < item->pos().y() + item->pixmap().height()) {
            return true;
        }
    }
    return false;
}

Custom_View::Custom_View(QWidget *parent) : QGraphicsView(parent)
{
    iconToDraw = new QIcon;
    selectionMode = false;
    scaleLevel = 1;
    itemWidget = new itemsizeWidget(nullptr, nullptr);
}

void Custom_View::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::NoAnchor);
    double scalefactor = 1.1;
    if( event->angleDelta().y() > 0) {
        scale(scalefactor, scalefactor);
        scaleLevel /= scalefactor;
    } else {
        scale(1/scalefactor, 1/scalefactor);
        scaleLevel *= scalefactor;
    }
}

void Custom_View::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_originX = event->position().x();
        m_originY = event->position().y();
        itemWidget->close();
        for(size_t i = 0; i < items.size(); ++i) {
            cout << items.size() << endl;
            if(checkItemUnderMouse(items[i],m_originX,m_originY)) {
                this->selectedItem = items[i];
                this->selectionMode = true;
                this->selectedItem->setTransformationMode(Qt::FastTransformation);
                return;
            }
        }
        this->selectionMode = false;
        this->selectedItem = nullptr;
        if(*drawMode == 1) {
            QGraphicsPixmapItem *item;
            item = new QGraphicsPixmapItem;
            item->setPixmap(this->iconToDraw->pixmap(100, 100));
            item->setPos(event->position().x() - 35, event->position().y() - 45);
            item->setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable);
            this->scene->addItem(item);
            items.push_back(item);
            *drawMode = 0;
        }
//        if(checkButtonPosition(this->toolButton, m_originX, m_originY)) {
//            this->toolButton->move(m_originX, m_originY);
//        }
    }
    if(event->button() == Qt::RightButton) {
        m_originX = event->position().x();
        m_originY = event->position().y();

        for(size_t i = 0; i < items.size(); ++i) {
            if(checkItemUnderMouse(items[i],m_originX,m_originY)) {
                itemWidget->setItem(items[i]);
                itemWidget->move(m_originX + items[i]->pixmap().width(), m_originY - 57);
                itemWidget->show();
                return;
            }
        }
    }
}

void Custom_View::mouseMoveEvent(QMouseEvent *event)
{
    if(*drawMode == 0) {
        if (event->buttons() & Qt::LeftButton) {
            QPointF oldPosition = mapToScene(m_originX, m_originY);
            QPointF newPosition = mapToScene(event->position().x(), event->position().y());
            QPointF translation = newPosition - oldPosition;
            m_originX = event->position().x();
            m_originY = event->position().y();
            if(selectionMode) {
                if(this->selectedItem != nullptr) {
                    this->selectedItem->setPos(selectedItem->pos().x() + translation.x(), selectedItem->pos().y() + translation.y());
                }

            } else translate(translation.x(), translation.y());
        }
    }
}
