QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /home/class/opencv-3.4.5/include
LIBS += -L/home/class/opencv-3.4.5/build/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc


SOURCES += \
    cam_test.cpp \
    imu.cpp \
    imu3d.cpp \
    imu3d_test.cpp \
    imu_test.cpp \
    lidar_sample.cpp \
    main.cpp \
    ultra_test.cpp \
    widget.cpp

HEADERS += \
    cam_test.h \
    imu.h \
    imu3d.h \
    imu3d_test.h \
    imu_test.h \
    lidar_sample.h \
    ultra_test.h \
    widget.h

FORMS += \
    cam.ui \
    imu.ui \
    imu_test.ui \
    lidar_sample_design.ui \
    ultra.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
