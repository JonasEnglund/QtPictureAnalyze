#ifndef ITEMSTRUCT_H
#define ITEMSTRUCT_H

#include <QGraphicsPixmapItem>

class ItemStruct {
public:
    ItemStruct itemStruct() {}
    QGraphicsPixmapItem *pixmapItem;
    QPixmap pixmap;
    QString name;
    QString maskirovka;
    QString ispravnost;
};

#endif // ITEMSTRUCT_H
