#ifndef LIDAR_SAMPLE_H
#define LIDAR_SAMPLE_H

#include <QWidget>
#include "imu_test.h"
QT_BEGIN_NAMESPACE
namespace Ui {class lidar_ui;}

QT_END_NAMESPACE

class QTcpSocket;

class lidar_sample : public QWidget
{
    Q_OBJECT

public:
    lidar_sample(QWidget* parent  = nullptr);
    imu_test* imuobj = nullptr;
    ~lidar_sample();
    int iDist[360];
    int iDist_buf[360];

private:
    Ui::lidar_ui *ui;
    QTcpSocket *tcpClient;


    int iYaw;


protected:
    void paintEvent(QPaintEvent *event) override;
public slots:
    void recvYaw(int);

private slots:
        void connectbtn_push();

        void tcp_connected();
        void tcp_recved_data();
        void tcp_disconnected();
};



#endif // LIDAR_SAMPLE_H
