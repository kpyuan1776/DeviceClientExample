#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <boost/log/trivial.hpp>

#include <queue>

#include "messagehandling.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief MainWindow class
 * 
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::string test, QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_actionExit_triggered();

public slots:
    void GuiLoopTimerSlot();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    std::string test2;
    MessagePacket* datapt;
};

#endif // MAINWINDOW_H
