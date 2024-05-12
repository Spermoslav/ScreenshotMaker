#include "menu.h"
#include "keys.h"
#include <QApplication>
#include <QFileDialog>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    dirLabel = new QLabel;
    dirLabel->setText(dirLabelStr + "\n" + dir);

    fileExtLabel = new QLabel;
    fileExtLabel->setText(fileExtStr);

    keyLabel = new QLabel;
    keyLabel->setText("Сочетание клавиш для скриншота: ");

    dirPB = new QPushButton;
    dirPB->setText("Изменить путь по умолчанию");
    connect(dirPB, &QPushButton::clicked, this, &MainWidget::dirPBClicked);

    keyChangePB = new QPushButton;
    keyChangePB->setText("Изменить сочетание клавиш");
    connect(keyChangePB, &QPushButton::clicked, this, &MainWidget::keyChangePBClicked);

    fileExtCB = new QComboBox;
    fileExtCB->addItem(fileExt);
    fileExtCB->addItem(".jpeg");
    connect(fileExtCB, &QComboBox::activated, this, &MainWidget::fileExtActivated);

    mainLay = new QGridLayout(this);
    mainLay->addWidget(dirLabel, 0, 0);
    mainLay->addWidget(dirPB, 0, 1);
    mainLay->addWidget(fileExtLabel, 1, 0);
    mainLay->addWidget(fileExtCB, 1, 1);
    mainLay->addWidget(keyLabel, 2, 0);
    mainLay->addWidget(keyChangePB, 2, 1);
}

MainWidget::~MainWidget()
{
}

void MainWidget::keyPressEvent(QKeyEvent *e)
{
//    if(e->key() == Qt::Key_S){
//        qDebug() << QApplication::primaryScreen()->grabWindow().save(dir + "/testS" + fileExt)
//                 << dir + "/testS" + fileExt;
//    }
    qDebug() << keyToString(e->key());
}

void MainWidget::keyReleaseEvent(QKeyEvent *e)
{

}

void MainWidget::fileExtActivated(int index)
{
    fileExt = fileExtCB->itemText(index);
    setFocus();
}

void MainWidget::dirPBClicked()
{
    dir = QFileDialog::getExistingDirectory(this, "Выберите директорию", dir);
    dirLabel->setText(dirLabelStr + "\n" + dir);
}

void MainWidget::keyChangePBClicked()
{

}



