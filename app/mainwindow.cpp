#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::string test,  QWidget *parent) :
    QMainWindow(parent),
    test2(test),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
          this, SLOT(GuiLoopTimerSlot()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::GuiLoopTimerSlot()
{
    if (ProducerConsumerObjects::dataqueue.empty())
    {
        BOOST_LOG_TRIVIAL(info) << "consumer task no queued objects " + test2;
    }
    else
    {
        datapt = &ProducerConsumerObjects::dataqueue.front();
        ProducerConsumerObjects::dataqueue.pop();
        BOOST_LOG_TRIVIAL(info) << "consumer task pop queued object: " + datapt->getMessage();
    }

}
