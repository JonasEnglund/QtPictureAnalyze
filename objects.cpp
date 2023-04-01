#include "objects.h"
#include "ui_objects.h"
#include <QTreeWidgetItem>
#include <QIcon>
#include <iostream>

using namespace std;

objects::objects(QWidget *parent, int *drawFlag, QIcon *icon) :
    QMainWindow(parent),
    ui(new Ui::objects)
{

    ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);
    drawMode = drawFlag;
    iconToDraw = icon;
    AddRoot("Авиационные объекты");
        AddChild("Авиационные объекты", "Бпла ближнего радиуса действия");
        AddChild("Авиационные объекты", "Бпла среднего радиуса действия");
        AddChild("Авиационные объекты", "Вертолет");
        AddChild("Авиационные объекты", "Самолет ближнего радиуса действия");
        AddChild("Авиационные объекты", "Самолет среднего радиуса действия");
        AddChild("Авиационные объекты", "Самолет дальнего радиуса действия");
    AddRoot("Морские объекты");
        AddChild("Морские объекты", "Судно");
    AddRoot("Сухопутная техника");
        AddChild("Сухопутная техника", "T-90");
        AddChild("Сухопутная техника", "Автомобиль");
        AddChild("Сухопутная техника", "Боевая машина пехоты");
        AddChild("Сухопутная техника", "Бронетранспортер");
}

void objects::AddRoot(QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    this->items.push_back(item);
    ui->treeWidget->addTopLevelItem(item);
}

void objects::AddChild(QString parentName, QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    QSize iconSize(10, 10);
    QIcon icon; icon.addFile(":/icons/" + name + ".png", iconSize);
    if(!icon.isNull())
        item->setIcon(0, icon);
    for(size_t i = 0; i < this->items.size(); ++i) {
        if(this->items[i]->text(0) == parentName)
            items[i]->addChild(item);
    }
    this->items.push_back(item);
}

objects::~objects()
{
    delete ui;
}

void objects::on_pushButton_released()
{
    *drawMode = 1;
    this->close();
}


void objects::on_treeWidget_itemPressed(QTreeWidgetItem *item, int column)
{
    *iconToDraw = item->icon(0);
}

