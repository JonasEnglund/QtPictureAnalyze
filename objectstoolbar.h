#ifndef OBJECTSTOOLBAR_H
#define OBJECTSTOOLBAR_H

#include <QWidget>

namespace Ui {
class ObjectsToolbar;
}

class ObjectsToolbar : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectsToolbar(QWidget *parent = nullptr);
    ~ObjectsToolbar();

private:
    Ui::ObjectsToolbar *ui;
};

#endif // OBJECTSTOOLBAR_H
