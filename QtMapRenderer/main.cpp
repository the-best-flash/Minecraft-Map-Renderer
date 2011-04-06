#include <QtGui/QApplication>
#include "renderoptions.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RenderOptions w;
    w.show();

    return a.exec();
}
