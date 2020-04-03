#ifndef IMU_TEST_H
#define IMU_TEST_H

#include <QWidget>
#include "imu3d_test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class imu_test; }
class QTcpSocket;
QT_END_NAMESPACE

class imu_test : public QWidget
{
    Q_OBJECT

public:
    imu_test(QWidget *parent = nullptr);
    ~imu_test();

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void sendYaw(int);

private:
    Ui::imu_test *ui;
    QTcpSocket *tcpSocket;

    QString strRecved;
    QString strMsg;

    imu3d_test* obj3d;

    void initialize();

private slots:
    void timerEvent(QTimerEvent* event);
    void connectButton();
    void connected();
    void readMessage();
    void disconnected();

};

#endif // IMU_TEST_H
