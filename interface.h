#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include "scene.h"

class Interface : public QWidget
{
    Q_OBJECT
    Scene *mainScene;
public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
    void setScene(Scene *s);

private slots:
    void on_speedupButton_clicked();
    void on_cam2Button_clicked();
    void on_cam1Button_clicked();
    void on_cam3Button_clicked();
    void on_startButton_clicked();
};
#endif // INTERFACE_H
