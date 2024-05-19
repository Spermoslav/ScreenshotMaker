#include <QApplication>
#include <QFileDialog>
#include <QCursor>

#include "menu.h"
#include "changekeys.h"
#include "screenshotmaker.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    dirLabel = new QLabel;
    dirLabel->setText(dirLabelStr + "\n" + fileDir.DIR);

    fileExtLabel = new QLabel;
    fileExtLabel->setText(fileExtStr);

    keyLabel = new QLabel;
    updateKeysLabel();

    dirPB = new QPushButton;
    dirPB->setText("Изменить путь по умолчанию");
    connect(dirPB, &QPushButton::clicked, this, &MainWidget::dirPBClicked);

    keyChangePB = new QPushButton;
    keyChangePB->setText("Изменить сочетание клавиш");
    connect(keyChangePB, &QPushButton::clicked, this, &MainWidget::keyChangePBClicked);

    fileExtCB = new QComboBox;
    fileExtCB->addItem(fileDir.EXT);
    fileExtCB->addItem(".jpeg");
    connect(fileExtCB, &QComboBox::activated, this, &MainWidget::fileExtActivated);

    mainLay = new QGridLayout(this);
    mainLay->addWidget(dirLabel, 0, 0);
    mainLay->addWidget(dirPB, 0, 1);
    mainLay->addWidget(fileExtLabel, 1, 0);
    mainLay->addWidget(fileExtCB, 1, 1);
    mainLay->addWidget(keyLabel, 2, 0);
    mainLay->addWidget(keyChangePB, 2, 1);

    changeKeys = new ChangeKeys(this);
    changeKeys->setFixedSize(300, 100);

    SSMaker = new ScreenShotMaker(this);
}

MainWidget::~MainWidget()
{
}

void MainWidget::setKey(const std::list<KeyPair> &keys)
{
    if(!keys.empty()) this->keys = keys;

    else  qDebug() << "setKey(keys) keys - empty";
    updateKeysLabel();
}

void MainWidget::updateKeysLabel()
{
    if(!keys.empty()) {
        keyLabel->setText("Сочетание клавиш для скриншота: \n");
        keyLabel->setText(keyLabel->text() + keys.begin()->second);

        for(int i = 1; i < keys.size(); ++i) {
            std::list<KeyPair>::iterator it = keys.begin();
            std::advance(it, i);
            keyLabel->setText(keyLabel->text() + "+" + it->second);
        }
    }
    else {
        qDebug() << "in updateKeysLabel()    keys - empty";
    }
}

void MainWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_F1) {
        SSMaker->activate();
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *e)
{

}

void MainWidget::fileExtActivated(int index)
{
    fileDir.EXT = fileExtCB->itemText(index);
    setFocus();
}

void MainWidget::dirPBClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Выберите директорию", fileDir.DIR);
    if(dir.isNull()) return;
    fileDir.DIR = std::move(dir);
    if(fileDir.DIR.at(fileDir.DIR.size() - 1) != '/') fileDir.DIR += "/";
    dirLabel->setText(dirLabelStr + "\n" + fileDir.DIR);
}

void MainWidget::keyChangePBClicked()
{
    changeKeys->show();
}
