#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QLabel(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QPixmap pix(":/m_comeo.png");
    setPixmap(pix);

    setWindowIcon(QIcon(":/app_icon.png"));

    quitbtn= new QPushButton("X");
    quitbtn->setFixedSize(20,20);
    QObject::connect(quitbtn, SIGNAL(clicked()), this, SLOT(hide()));

    update= new QPushButton("");
    update->setIcon(QIcon(":/rotateright.png"));
    update->setFixedSize(20,20);
    QObject::connect(update, SIGNAL(clicked()), this, SLOT(on_update()));

    cbports = new QComboBox();
    cbports->setFixedSize(78,20);
    fill_cb();

    bxulay = new QHBoxLayout();
    bxulay->addWidget(cbports);
    bxulay->addWidget(update);
    bxulay->setSpacing(1);

    bxlay = new QVBoxLayout();
    bxlay->addWidget(quitbtn);
    bxlay->addLayout(bxulay);
    bxlay->addStretch(2);
    bxlay->setSpacing(9);

    setLayout(bxlay);

    mtimer.setInterval(1000);
    connect(&mtimer, &QTimer::timeout, this, &MainWindow::timerMainShot);
    mtimer.start();

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/app_icon.png"));
    trayIcon->setToolTip("MCOMew");

    QMenu *menu = new QMenu(this);
    QAction *viewO = new QAction("Open", this);
    QAction *viewQ = new QAction("Quit", this);

    QObject::connect(viewO,  SIGNAL(triggered()), this, SLOT(show()));
    QObject::connect(viewQ,  SIGNAL(triggered()), this, SLOT(close()));

    menu->addAction(viewO);
    menu->addAction(viewQ);

    trayIcon->setContextMenu(menu);
    trayIcon->show();
    QObject::connect(trayIcon,  SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    mtimer.stop();
}

void MainWindow::fill_cb()
{
    cbports->clear();
    cbports->addItem("Откройся!");

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        cbports->addItem(info.portName());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(this->isVisible())
    {
        event->ignore();
        this->hide();
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
        trayIcon->showMessage("MCOMew", "Click trey to open again", icon, 2000);
    }
}

void MainWindow::on_update()
{
    fill_cb();
}

void MainWindow::timerMainShot()
{
    fill_cb();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        if(!this->isVisible())
        {
            this->show();
        }
        else
        {
            this->hide();
        }
        break;
    default:
        break;
    }
}
