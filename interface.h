#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QTimer>

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
    QTimer *timer;

private slots:
    void updateGL();
};
#endif // INTERFACE_H
