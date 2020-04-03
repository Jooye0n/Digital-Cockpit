#include "lidar_sample.h"
#include "ui_lidar_sample_design.h"//여기에 lidar_ui있다
#include <QTcpSocket>
#include <QHostAddress>
#include <QPainter>


lidar_sample::lidar_sample(QWidget* parent)
    :QWidget(parent)
    ,ui(new Ui::lidar_ui)
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

    for(int i=0; i<360; i++){
        iDist[i]=0;
    }
}


void lidar_sample::connectbtn_push()
{
    QString xycarip = ui ->serverip->text().trimmed();
    //디자인한 클래스의 서버 아이피에 접속해서 라인 아이피의 클래스의 택스트 매소드로 space trime
    QString lidarport = ui ->serverport->text().trimmed();



    QHostAddress HADDR_IP(xycarip);

    tcpClient ->connectToHost(HADDR_IP,lidarport.toUShort());


}
void lidar_sample::tcp_connected()
{
    qDebug()<<Q_FUNC_INFO<<"서버 접속 완료";
}

void lidar_sample::tcp_recved_data()
{
    qDebug()<<Q_FUNC_INFO<<"수신";

    if(tcpClient->bytesAvailable()>=0)
    {
        QByteArray readData = tcpClient->readAll();//소켓ㅇ로 들어온 데이터 받는 부분
        qDebug() << readData;

        QString strRecv(readData);//데이터를 q 스트링으로 바꿔줌
        ui->data->setText(strRecv);

        int iStartPos = strRecv.indexOf("[",0);//-1
        int iEndPos = strRecv.indexOf("]",1);

        if(iStartPos !=-1){
            if(iStartPos < iEndPos){
                qDebug() <<"start : " <<iStartPos<<"end : "<<iEndPos;


                QString strRadTotal=strRecv.mid(iStartPos,iEndPos-iStartPos);

                strRadTotal.remove(0,1);
                QStringList strRad = strRadTotal.split("|");

                if(strRad.count()==361)
                {
                    for(int i=0; i<360;i++)
                    {
                        int iRad = strRad[i].mid(0,3).toInt();
                        int iDistance = strRad[i].remove(0,4).toInt();
                        iDist[iRad] = iDistance;
                        iDist_buf[iRad] = iDistance;
                    }
                    update();

                }
            }
        }
    }
}
void lidar_sample::tcp_disconnected()
{
    qDebug()<<Q_FUNC_INFO<<"연결 종료";
}

void lidar_sample::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);

    painter -> setPen(QPen(Qt::red,6));


    //painter -> drawPoint(200,300);

    //여기에 그림그리는것
    painter ->translate(this->size().width()/2,this->size().height()/2+50);//그리고자 하는것의 중점(원의 중심)
    painter ->drawPoint(0,0);
\




    painter->setPen(QPen(Qt::blue,3));
    painter->drawArc(40/-2,40/-2,40,40,0,360*16);
    painter->drawText(20,20,"20cm");
    painter->drawArc(100/-2,100/-2,100,100,0,360*16);
    painter->drawText(50,50,"50cm");
    painter->drawArc(200/-2,200/-2,200,200,0,360*16);
    painter->drawText(100,100,"100cm");


    painter->setPen(QPen(Qt::green,1));
    painter->drawLine(0,0,0,-50);

    painter ->rotate(ui->angle->text().toInt()*-1);

    painter->setPen(QPen(QColor(255,25,50),3));
    for(int i=0; i<360; i++){
        qDebug() << i;
       //painter->drawLine(0,0,0,-100);
        if(iDist[i]!=0){//측정값이 0이 아니면 점을 찍는다

            qDebug() << "-angle:" << iDist[i];
            painter->drawPoint(iDist[i]/10,0);//x축이 0도인 경우 이렇게 표현한다
            iDist[i] =0;
        }

        painter->rotate(-1);//1도씩 위젯을 회전켜준다(양의 방향으로)
    }
  // painter->drawPoint(50,-50);


    delete painter;
}


lidar_sample::~lidar_sample()
{
    delete ui;
}


void lidar_sample::recvYaw(int iRecvYaw){
    iYaw = iRecvYaw;
}
