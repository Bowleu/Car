#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interface)
{
    ui->setupUi(this);
    timer = new QTimer;

    connect(timer, &QTimer::timeout, this, &Interface::updateGL);

    timer->start(10);
}

Interface::~Interface()
{
    delete ui;
}

void Interface::updateGL()
{
    ui->mainScene->update();
    timer->start(10);
}

