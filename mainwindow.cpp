#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QLabel(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QPixmap pix(":/m_comeo.png");
    setPixmap(pix);

    setFixedSize(pix.size());
    setWindowIcon(QIcon(":/app_icon.png"));

    quitbtn= new QPushButton("");
    quitbtn->setIcon(QIcon(":/exit.png"));
    quitbtn->setFixedSize(20,20);
    QObject::connect(quitbtn, SIGNAL(clicked()), this, SLOT(hide()));

    update= new QPushButton("");
    update->setIcon(QIcon(":/rotateright.png"));
    update->setFixedSize(20,20);
    QObject::connect(update, SIGNAL(clicked()), this, SLOT(on_update()));

    butlay = new QHBoxLayout();
    butlay->setMargin(0);
    butlay->setSpacing(5);
    butlay->addWidget(quitbtn);
    butlay->addWidget(update);

    mlist = new QListWidget(this);
    mlist->setFixedSize(116,156);
    mlist->setSelectionMode(QAbstractItemView::NoSelection);
    mlist->setFont(QFont("Times", 12, 1));
    fill_cb();

    bxlay = new QVBoxLayout();
    bxlay->addLayout(butlay);
    bxlay->addWidget(mlist);
    bxlay->setSpacing(0);
    bxlay->setMargin(12);

    setLayout(bxlay);
    bxlay->setGeometry(QRect(0,0, pix.size().width(), pix.size().height()));

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
    mlist->clear();
    QStringList list;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        list.append(info.portName());
    mlist->insertItems(0, list);
    mlist->sortItems();
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
