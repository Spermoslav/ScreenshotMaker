#include "menu.h"
#include <QApplication>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    dirLabel = new QLabel;
    dirLabel->setText(dirLabelStr + "\n" + dir);

    fileExtLabel = new QLabel;
    fileExtLabel->setText(fileExtStr);

    dirPB = new QPushButton;
    dirPB->setText("Изменить путь по умолчанию");
    connect(dirPB, &QPushButton::clicked, this, &Widget::dirPBClicked);

    fileExtCB = new QComboBox;
    fileExtCB->addItem(fileExt);
    fileExtCB->addItem("test2");
    connect(fileExtCB, &QComboBox::activated, this, &Widget::fileExtActivated);

    mainLay = new QGridLayout(this);
    mainLay->addWidget(dirLabel, 0, 0);
    mainLay->addWidget(dirPB, 0, 1);
    mainLay->addWidget(fileExtLabel, 1, 0);
    mainLay->addWidget(fileExtCB, 1, 1);
}

Widget::~Widget()
{
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_S){
        qDebug() << QApplication::primaryScreen()->grabWindow().save(dir + "/testS.png")
                 << dir;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *e)
{

}

void Widget::fileExtActivated(int index)
{
    qDebug() << index;
}

void Widget::dirPBClicked()
{
    dir = QFileDialog::getExistingDirectory(this, "Выберите директорию", dir);
    dirLabel->setText(dirLabelStr + "\n" + dir);
}

