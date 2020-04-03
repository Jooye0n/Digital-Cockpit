#include "imu.h"
#include "ui_imu.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QPainter>
#include <QTime>

imu::imu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Imu)
{
    ui->setupUi(this);
    initialize();

    obj3d = new imu3d(ui->sensor);
    obj3d ->resize(ui->sensor->width(), ui->sensor->height());
}

imu::~imu()
{
    delete ui;
}

void imu::initialize()
{
    tcpSocket = new QTcpSocket(this);

    connect(ui->conn, SIGNAL(clicked()), this, SLOT(connectButton()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

void imu::connectButton()
{
    QString sensorip = ui->sensorip->text().trimmed();
    QString sensorport = ui->sensorport->text().trimmed();

    QHostAddress serverAddress(sensorip);
    tcpSocket->connectToHost(serverAddress, sensorport.toUShort());

    qDebug() << Q_FUNC_INFO << "서버 접속 요청";
}

void imu::connected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 완료";
    startTimer(1000);
}

void imu::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0)
    {
        // 상태값 수신
        QByteArray readData = tcpSocket->readAll();
        QString strRecv(readData);
        strRecv.remove("\r\n");
        ui->value->setText("현재시간 : " + QTime::currentTime().toString() + "     " + strRecv);
        //strRecv.remove("\r\n").remove("#YPR=");
        strRecv.remove("#YPR=");
        QStringList strRecvArray = strRecv.split(",");
        ui->value2->setText(QString("YAW : %1   PITCH = %2   ROLL = %3").arg(strRecvArray[0]).arg(strRecvArray[1]).arg(strRecvArray[2]));
        //qDebug() << strRecvArray;

        obj3d->setXYZRotation(strRecvArray[0].toFloat(), strRecvArray[1].toFloat(), strRecvArray[2].toFloat());
    }
}

void imu::disconnected()
{
    tcpSocket->close();
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}

void imu::paintEvent(QPaintEvent *event)
{
}

void imu::timerEvent(QTimerEvent* event)
{
    //update();
}
