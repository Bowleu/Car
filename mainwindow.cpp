#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Interface *i = ui->centralwidget->findChild<Interface*>();
    Scene *c = ui->centralwidget->findChild<Scene*>();
    i->setScene(c);
}

MainWindow::~MainWindow() {
    delete ui;
}
