#include "SceneViewerWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SceneViewerWidget w;
    w.showMaximized();
    w.show();

    return a.exec();
}
