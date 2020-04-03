#include "widget.h"
#include "imu.h"
#include "imu3d_test.h"
#include "lidar_sample.h"
#include "imu_test.h"
#include "cam_test.h"
#include "ultra_test.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//  Widget w;
//  w.show();

//    lidar_sample w;
//    w.show();

//    imu_test imu;
//    imu.show();

//      QObject::connect(&imu, SIGNAL(sendYaw()), &w, SLOT(recvYaw()));

//    imu3d_test imu3d;
//    imu3d.show();

    ultra_test w4;
    w4.show();

//    cam_test w3;
//    w3.show();

    return a.exec();
}
