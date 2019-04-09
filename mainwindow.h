#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QComboBox>
#include <QSerialPortInfo>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>
#include <QSettings>
#include <QDir>
#include <QDebug>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QLabel
{
    Q_OBJECT
    QPoint m_ptPosition;
    QComboBox *cbports;
    QPushButton *quitbtn;
    QPushButton *update;
    QHBoxLayout *bxulay;
    QVBoxLayout *bxlay;
    QTimer mtimer;
    QSystemTrayIcon* trayIcon;
    QListWidget* mlist;
    QHBoxLayout* butlay;

public slots:
    void on_update();
    void timerMainShot();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fill_cb();
protected:
    void closeEvent(QCloseEvent* event);
    virtual void mousePressEvent(QMouseEvent *pe)
    {
        m_ptPosition = pe->pos();
    }
    virtual void mouseMoveEvent(QMouseEvent *pe)
    {
        move(pe->globalPos() - m_ptPosition);
    }
};

#endif // MAINWINDOW_H
