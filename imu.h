#ifndef IMU_H
#define IMU_H

#include <QWidget>
#include "imu3d.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Imu; }
class QTcpSocket;
class imu3d;
QT_END_NAMESPACE

class imu : public QWidget
{
    Q_OBJECT
public:
    explicit imu(QWidget *parent = nullptr);
    ~imu();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Imu *ui;

    QTcpSocket* tcpSocket;

    QString strRecved;
    QString strMsg;

    imu3d* obj3d;

    void initialize();

signals:

public slots:
    void timerEvent(QTimerEvent* event);
    void connectButton();
    void connected();
    void readMessage();
    void disconnected();
};

#endif // IMU_H
