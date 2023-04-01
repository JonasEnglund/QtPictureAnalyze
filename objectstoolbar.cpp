#include "objectstoolbar.h"
#include "ui_objectstoolbar.h"

ObjectsToolbar::ObjectsToolbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsToolbar)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавить объект");
}

ObjectsToolbar::~ObjectsToolbar()
{
    delete ui;
}
