#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

private:
    Ui::Interface *ui;


private slots:
    void updateGL();
    void on_speedupButton_clicked();
    void on_cam2Button_clicked();
    void on_cam1Button_clicked();
    void on_cam3Button_clicked();
    void on_startButton_clicked();
};
#endif // INTERFACE_H
