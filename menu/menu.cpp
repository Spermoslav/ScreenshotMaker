#include <QApplication>
#include <QFileDialog>
#include <QCursor>
#include <QMenu>

#include "menu.h"
#include "changekeys.h"
#include "screenshotmaker.h"
#include "keyboardhook.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      dirLabel(new QLabel),
      fileExtLabel(new QLabel),
      keyLabel(new QLabel),
      dirPB(new QPushButton),
      keyChangePB(new QPushButton),
      fileExtCB(new QComboBox),
      mainLay(new QGridLayout(this)),
      changeKeys(new ChangeKeys(this)),
      SSMaker(new ScreenShotMaker),
      tray(new QSystemTrayIcon(this))
{
    if(QFile::exists(FileConfig::CONFIG_NAME))
    {
        QFile config(FileConfig::CONFIG_NAME);  // чтение конфига
        config.open(QIODevice::ReadOnly | QIODevice::Text);
        QStringList x = QString::fromLocal8Bit(config.readAll()).split('\n');
        FileConfig::DIR = x.at(0);
        FileConfig::EXT = x.at(1);

        QStringList t = x.at(2).split("+");
        for(const auto& p : t) {
            keys.addKey((Qt::Key)p.toInt());
        }
    }
    else
    {
        QFile config(FileConfig::CONFIG_NAME);  // запись в конфиг настроек по умолчанию
        config.open(QIODevice::WriteOnly | QIODevice::Text);
        QString dir = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).join("/") + "/";
        QString ext = ".png";
        config.write(dir.toLocal8Bit());
        config.write("\n");
        config.write(ext.toLocal8Bit());
        config.write("\n");
        config.write(QString::number(Qt::Key_PrintScreen).toLocal8Bit());
        keys.addKey(Qt::Key_PrintScreen);
    }

    Call::setMenu(this, keyEvent);

    keys.setFunc(this, &MainWidget::keyShortcutPress);

    dirLabel->setText(dirLabelStr + "\n" + FileConfig::DIR);
    fileExtLabel->setText(fileExtStr);
    updateKeysLabel();

    dirPB->setText("Изменить путь по умолчанию");
    keyChangePB->setText("Изменить сочетание клавиш");
    connect(dirPB, &QPushButton::clicked, this, &MainWidget::dirPBClicked);
    connect(keyChangePB, &QPushButton::clicked, this, &MainWidget::keyChangePBClicked);

    fileExtCB->addItem(FileConfig::EXT);
    if(FileConfig::EXT == ".png") fileExtCB->addItem(".jpeg");
    else fileExtCB->addItem(".png");
    connect(fileExtCB, &QComboBox::activated, this, &MainWidget::fileExtActivated);

    mainLay->addWidget(dirLabel, 0, 0);
    mainLay->addWidget(dirPB, 0, 1);
    mainLay->addWidget(fileExtLabel, 1, 0);
    mainLay->addWidget(fileExtCB, 1, 1);
    mainLay->addWidget(keyLabel, 2, 0);
    mainLay->addWidget(keyChangePB, 2, 1);

    changeKeys->setFixedSize(300, 100);

    QMenu *menu = new QMenu(this);                                     // инициализация контекстного меню
    QAction *viewWindow = new QAction("Открыть меню", this);
    QAction *quitAction = new QAction("Закрыть", this);
    connect(viewWindow, &QAction::triggered, this, &MainWidget::show);
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
    menu->addAction(viewWindow);
    menu->addAction(quitAction);

    QImage pix(QApplication::applicationDirPath() + "/icon/camera.png");  // инициализация картинки для трэя
    pix = pix.scaled(QSize(32, 32), Qt::AspectRatioMode::KeepAspectRatio);
    tray->setIcon(QIcon(QPixmap::fromImage(pix)));
    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    tray->setContextMenu(menu);
    tray->show();
    tray->setToolTip("ScreenshotMaker");

#ifdef SSMAKER_START
    SSMaker->activate();
#endif
}

MainWidget::~MainWidget()
{
}

void MainWidget::setKey(const std::list<KeyPair> &key)
{
    if(!key.empty()) {
        keys.clear();
        for(auto &k : key) {
            keys.addKey((Qt::Key)k.first);
        }
        updateConfig();
    }
    else  qDebug() << "setKey(keys) keys - empty";
    updateKeysLabel();
}

void MainWidget::updateKeysLabel()
{
    if(!keys.empty()) {
        QString labelText = "Сочетание клавиш для скриншота: \n";

        for(auto &k : keys.shortcut()) {
            labelText += keyToString(k) + "+";
        }
        labelText.erase(labelText.end() - 1);
        keyLabel->setText(labelText);
    }
    else {
        qDebug() << "in updateKeysLabel()    keys - empty";
    }
}

void MainWidget::close()
{
    hide();
}

void MainWidget::keyPressEvent(QKeyEvent *e)
{
    keys.keyPress((Qt::Key)e->key());
}

void MainWidget::keyReleaseEvent(QKeyEvent *e)
{
    keys.keyRelease((Qt::Key)e->key());
}

void MainWidget::closeEvent(QCloseEvent *e)
{
    if(isVisible() && e->spontaneous()) {
        hide();
        tray->showMessage("ScreenshotMaker",
                          "Меню свернуто в трей. Для того чтобы, "
                          "развернуть меню приложения, щелкните по иконке приложения в трее",
                          tray->icon(),
                          1000);
    }
}

void MainWidget::keyShortcutPress()
{
    SSMaker->activate();
}

void MainWidget::fileExtActivated(int index)
{
    FileConfig::EXT = fileExtCB->itemText(index);
    updateConfig();
    setFocus();
}

void MainWidget::dirPBClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Выберите директорию", FileConfig::DIR);
    if(dir.isNull()) return;
    FileConfig::DIR = std::move(dir);
    if(FileConfig::DIR.at(FileConfig::DIR.size() - 1) != '/') FileConfig::DIR += "/";
    dirLabel->setText(dirLabelStr + "\n" + FileConfig::DIR);

    updateConfig();
}

void MainWidget::keyChangePBClicked()
{
    changeKeys->show();
}

void MainWidget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
        if(!isVisible()){
            show();
        }
        else {
            hide();
        }
    }
}

void MainWidget::keyEvent(KeyStatus ks)
{
    if(SSMaker->isHidden()){
        if(ks.second) keys.keyPress(ks.first);
        else          keys.keyRelease(ks.first);
    }
}

void MainWidget::updateConfig()
{
    QString shortcut = "";

    for(int p : keys.shortcut()) {
        shortcut += QString::number(p) + "+";
    }
    if(!keys.shortcut().empty()) shortcut.erase(shortcut.end() - 1);

    QFile config(FileConfig::CONFIG_NAME);
    config.open(QIODevice::WriteOnly | QIODevice::Text);
    config.write(FileConfig::DIR.toLocal8Bit());
    config.write("\n");
    config.write(FileConfig::EXT.toLocal8Bit());
    config.write("\n");
    config.write(shortcut.toLocal8Bit());
}

