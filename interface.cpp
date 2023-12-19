#include "interface.h"
#include "ui_interface.h"
#include "camera.h"

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interface)
{
    ui->setupUi(this);
}

Interface::~Interface()
{
    delete ui;
}

void Interface::on_startButton_clicked()
{
    if(ui->mainScene->idle_state){
        ui->mainScene->idle_state = 0;
        ui->startButton->setText("- - BREAK - -");
    }
    else{
        ui->mainScene->idle_state = 1;
        ui->startButton->setText("- - START - -");
    }
}

void Interface::on_cam1Button_clicked()
{
    ui->mainScene->activeCam = 1;
}

void Interface::on_cam2Button_clicked()
{
    ui->mainScene->activeCam = 2;
}

void Interface::on_cam3Button_clicked()
{
    ui->mainScene->activeCam = 3;
}

void Interface::on_speedupButton_clicked(){
    if(ui->mainScene->speedup){
        ui->mainScene->speedup = 0;
        ui->speedupButton->setText("x10");
    }
    else{
        ui->mainScene->speedup = 1;
        ui->speedupButton->setText("x1");
    }
}
