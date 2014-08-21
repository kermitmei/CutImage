#include <QCoreApplication>
#include "CutImage.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CutImage cutImage;
    if(argc <= 1) {
        return 1;
    }

    for(int i = 1; i < argc; ++i) {
        cutImage.processImage(argv[i]);
    }
    return 0;
    //return a.exec();
}
