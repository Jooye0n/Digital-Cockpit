#ifndef ULTRA_TEST_H
#define ULTRA_TEST_H


#include <QWidget>
#include "imu_test.h"
QT_BEGIN_NAMESPACE
namespace Ui {class ultra_ui;}

QT_END_NAMESPACE

class QTcpSocket;

class ultra_test : public QWidget
{
    Q_OBJECT

public:
    ultra_test(QWidget* parent  = nullptr);
    ultra_test* ultraobj = nullptr;
    ~ultra_test();
    int ultraDist_cm;
    int iUltraDist_cm;
    QString strMsg;

private:
    Ui::ultra_ui *ui;
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


#endif // ULTRA_TEST_H
