#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Connex_Button_clicked()
{
     socket->connectToHost(ui->IP_text->text(),ui->PORT_text->text().toInt());
     if(socket->waitForConnected(3000))
     {
            ui->label_5->setText("Connécté");
            ui->label_5->setEnabled(false);
     }
     else
     {
         ui->label_5->setText("Erreur de connection");

     }
}
