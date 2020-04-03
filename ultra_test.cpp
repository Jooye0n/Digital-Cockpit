#include "ultra_test.h"
#include "ui_ultra.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QPainter>
#include <QString>


ultra_test::ultra_test(QWidget* parent)
    :QWidget(parent)
    ,ui(new Ui::ultra_ui)
{
    ui->setupUi(this);

    connect(ui->connect_button, SIGNAL(clicked()),\
            this,SLOT(connectbtn_push()));

    tcpClient = new QTcpSocket(this);
    connect(tcpClient, SIGNAL(readyRead()),\
            this,SLOT(tcp_recved_data()));

    connect(tcpClient, SIGNAL(connected()),\
            this,SLOT(tcp_connected()));

    connect(tcpClient, SIGNAL(disconnected()),\
            this,SLOT(tcp_disconnected()));

}


void ultra_test::connectbtn_push()
{
    QString xycarip = ui ->serverip->text().trimmed();
    //디자인한 클래스의 서버 아이피에 접속해서 라인 아이피의 클래스의 택스트 매소드로 space trime
    QString lidarport = ui ->serverport->text().trimmed();

    QHostAddress HADDR_IP(xycarip);

    tcpClient ->connectToHost(HADDR_IP,lidarport.toUShort());


}
void ultra_test::tcp_connected()
{
    qDebug()<<Q_FUNC_INFO<<"서버 접속 완료";
}

void ultra_test::tcp_recved_data()
{
    if(tcpClient->bytesAvailable() >= 0)
    {
        // 영상값 수신
        QByteArray readData = tcpClient->readAll();
        QString strRecv(readData);//데이터를 q 스트링으로 바꿔줌
        strMsg = QString::fromStdString(readData.toStdString());
        iUltraDist_cm = 0;
        ultraDist_cm = readData.toInt();
        ui->data->setText(strRecv);
    }
}
void ultra_test::tcp_disconnected()
{
    qDebug()<<Q_FUNC_INFO<<"연결 종료";
}

void ultra_test::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter -> setPen(QPen(Qt::red,6));
    //여기에 그림그리는것
    painter ->translate(this->size().width()/2, ui->sensor->y()+30);//그리고자 하는것의 중점(원의 중심)
    QRect rectangle(-150,-300+20,300,600);
    int startAngle = 5760/4*-1+16*30*-1;
    int spanAngle = 16*30*2;

    painter->setPen(QPen(Qt::blue,1));
    painter->setBrush(QBrush(Qt::blue));
    painter->drawPie(rectangle,startAngle,spanAngle);
    painter->setPen(QPen(Qt::blue,10));
    painter->drawPoint(0,0);

    painter->setPen(QPen(Qt::red,1));
    if(ultraDist_cm > 152){
        iUltraDist_cm = 152;
    }

    painter->drawLine(-150,iUltraDist_cm*2+30,150,iUltraDist_cm);
    painter->drawText(50,0,strMsg);
    QRect clipRect(-150,20,300,iUltraDist_cm*2);
    painter->setClipping(true);
    painter->setClipRect(clipRect);
    painter->setBrush(QBrush(Qt::red));
    painter->drawPie(rectangle, startAngle, spanAngle);
    delete painter;
}


ultra_test::~ultra_test()
{
    delete ui;
}


void ultra_test::recvYaw(int iRecvYaw){
    iYaw = iRecvYaw;
}
