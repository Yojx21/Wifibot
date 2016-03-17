#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTcpSocket>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    quint16 crc16(QByteArray buffer);
    ~MainWindow();

private slots:
    void on_Connex_Button_clicked();

    void on_Av_Button_clicked();

    void on_Deco_button_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
