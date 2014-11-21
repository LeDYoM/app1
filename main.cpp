#include <QApplication>
#include "config.h"
#include "glwrenderer.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("cube");
    app.setApplicationVersion("0.1");
    GLWRenderer *widget;

    QGLFormat format;
    format.setDoubleBuffer(true);
    MainWindow mWindow;
    widget = new GLWRenderer(format,&mWindow);
    mWindow.setCentralWidget(widget);
    mWindow.show();

    return app.exec();
}
