#include "interface.h"
#include "camera.h"

Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
}

Interface::~Interface()
{
}

void Interface::setScene(Scene* s)
{
    mainScene = s;
}

void Interface::on_startButton_clicked()
{
    QPushButton* startButton = findChild<QPushButton*>("startButton");
    if(mainScene->idle_state){
        mainScene->idle_state = 0;
        startButton->setText("- - BREAK - -");
    }
    else{
        mainScene->idle_state = 1;
        startButton->setText("- - START - -");
    }
}

void Interface::on_cam1Button_clicked()
{
    mainScene->activeCam = 1;
}

void Interface::on_cam2Button_clicked()
{
    mainScene->activeCam = 2;
}

void Interface::on_cam3Button_clicked()
{
    mainScene->activeCam = 3;
}

void Interface::on_speedupButton_clicked(){
    QPushButton* speedupButton = findChild<QPushButton*>("speedupButton");
    if(mainScene->speedup){
        mainScene->speedup = 0;
        speedupButton->setText("x10");
    }
    else{
        mainScene->speedup = 1;
        speedupButton->setText("x1");
    }
}
