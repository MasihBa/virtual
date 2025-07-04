#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QHostInfo>
#include <QNetworkInterface>
#include <QString>
#include <QList>
#include <QMainWindow>
#include <myserver.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QString getWifiIPv4Address();
    ~MainWindow();

private slots:
    void on_btnStart_clicked();

private:
    MyServer server;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
