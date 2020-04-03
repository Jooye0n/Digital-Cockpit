#include "cam_test.h"

#include "ui_cam.h"

#include <QTcpSocket>
#include <QHostAddress>

cam_test::cam_test(QWidget* parent, lidar_sample* lidar)
        : QWidget(parent)
        , ui(new Ui::CAM_UI)
{
    ptr_lidar = lidar;
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(ui->conn, SIGNAL(clicked()), this, SLOT(connectButton()));
}

cam_test::~cam_test()
{

}

void cam_test::connectButton()
{
    QString sensorip   = ui->serverip->text().trimmed();
    QString sensorport   = ui->serverport->text().trimmed();

    QHostAddress serverAddress(sensorip);
    tcpSocket->connectToHost(serverAddress, sensorport.toUShort());

    qDebug() << Q_FUNC_INFO << "서버 접속 요청";
}

void cam_test::connected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 완료";
}

void cam_test::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0)
    {
        // 영상값 수신
        QByteArray readData = tcpSocket->readAll();
        imgByte.append(readData);

        if(imgByte.count() >= 480 * 640 * 3)
        {
            cv::Mat tmp(480, 640, CV_8UC3, imgByte.data());
            img = tmp.clone();
            imgByte.remove(0, 480*640*3);

            cv::cvtColor(img,img,CV_BGR2RGB);

            for(int i = 0 ; i<160; i++)
             {
                 int iRadDist = i+180;
                 cv::Scalar color;
                 if(ptr_lidar->iDist_buf[iRadDist] > 500)
                 {
                     color = cv::Scalar(0, 0, 255);
                 }
                 else if(ptr_lidar->iDist_buf[iRadDist] > 200)
                 {
                     color = cv::Scalar(255, 255, 0);
                 }
                 else if(ptr_lidar->iDist_buf[iRadDist] > 10)
                 {
                     color = cv::Scalar(255, 0, 0);
                 }

                 cv::line(img, cv::Point(640-i*4, \
                 tmp.size().height / 2), cv::Point(640-i*4, \
                            tmp.size().height / 2), color, 2);
             }


            QImage image( img.data,
                          img.cols, img.rows,
                          static_cast<int>(img.step),
                          QImage::Format_RGB888 );
            ui->cam->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void cam_test::disconnected()
{
    tcpSocket->close();
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}
