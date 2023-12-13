#include "interface.h"
#include "ui_interface.h"
#include "camera.h"

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
}


void Interface::on_pushButton_clicked()
{
    ui->mainScene->cam_idle_state = 0;
    if(ui->mainScene->idle_state){
        ui->mainScene->idle_state = 0;
        ui->pushButton->setText("- - BREAK - -");
    }
    else{
        ui->mainScene->idle_state = 1;
        ui->pushButton->setText("- - START - -");
    }
}
