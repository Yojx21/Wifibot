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
quint16 MainWindow::crc16(QByteArray buffer) {

    quint16 crc = 0xFFFF;
    quint16 polynome = 0xA001;
    unsigned int parity = 0;
    unsigned int cptBit;
    unsigned int cptOct;

    for (cptOct = 1; cptOct < 7; cptOct++){

        crc ^= (unsigned char) buffer.at(cptOct);

        for (cptBit = 0; cptBit <= 7 ; cptBit++){

            parity = crc;
            crc >>= 1;

            if (parity % 2 == true) crc ^= polynome;
        }
    }

    return crc;
}

void MainWindow::on_Connex_Button_clicked()
{
     socket->connectToHost(ui->IP_text->text(),ui->PORT_text->text().toInt());
     if(socket->waitForConnected(3000))
     {
            ui->label_5->setText("Connecté");
            ui->Connex_Button->setEnabled(false);
            ui->Deco_button->setEnabled(true);

     }
     else
     {
         ui->label_5->setText("Erreur de connection: "+socket->errorString());

     }


}

void MainWindow::on_Av_Button_clicked()
{
    QByteArray data;
     data.append((char)0xff);
     data.append((char)0x07);
     data.append((char)0x78);
     data.append((char)0x00);
     data.append((char)0x78);
     data.append((char)0x00);
     data.append((char)0x50);
     quint16 crc = crc16(data);
     data.append((char)crc);
     data.append((char)(crc >> 8));

     socket->waitForBytesWritten(10);
     socket->write(data);
update();

}


void MainWindow::on_Deco_button_clicked()
{
    socket->disconnectFromHost();
    ui->Connex_Button->setEnabled(true);
    ui->Deco_button->setEnabled(false);
    ui->label_5->setText("Deconnecté");
}
