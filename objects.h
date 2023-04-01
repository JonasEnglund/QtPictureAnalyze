#ifndef OBJECTS_H
#define OBJECTS_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <vector>

namespace Ui {
class objects;
}

class objects : public QMainWindow
{
    Q_OBJECT

    void AddRoot(QString name);
    void AddChild(QString parentName, QString name);

public:
    explicit objects(QWidget *parent = nullptr, int *drawModeCheck = 0, QIcon *icon = nullptr);
    int *drawMode;
    QIcon *iconToDraw;
    QString *itemName;
    ~objects();

private slots:
    void on_pushButton_released();

    void on_treeWidget_itemPressed(QTreeWidgetItem *item, int column);

private:
    QTreeWidgetItem *clickedItem;
    std::vector<QTreeWidgetItem*> items;
    Ui::objects *ui;
};

#endif // OBJECTS_H
