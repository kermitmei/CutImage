#include <QDir>
#include <QImage>
#include "CutImage.h"

CutImage::CutImage()
{
}

void CutImage::processImage(const QString &fileName)
{
    QString filePath = QDir::currentPath();
    filePath = filePath + "/" + fileName;
    QImage image(filePath);
    
    if(image.isNull()) {
        qDebug("Null image: %s", filePath.toStdString().c_str());
        return ;
    }

    QSize size = image.size();
    QPoint ltPt(size.width(), size.height());
    QPoint rbPt(0,0);
    for(int x = 0; x < size.width(); ++x) {
        for(int y = 0; y < size.height(); ++y) {
            if(image.pixel(x,y) == 0xffffff) {
                continue ;
            }
            if(ltPt.x() > x) {
                ltPt.setX(x);
            }
            if(ltPt.y() > y) {
                ltPt.setY(y);
            }

            if(rbPt.x() < x) {
                rbPt.setX(x);
            }

            if(rbPt.y() < y) {
                rbPt.setY(y);
            }
        }
    }
    qDebug("pix(%x),size(%d,%d), ltPt(%d,%d), rbPt(%d,%d);",
           image.pixel(0,0),
           size.width(), size.height(),
           ltPt.x(), ltPt.y(),
           rbPt.x(), rbPt.y());

    QSize newImgSize(rbPt.x() - ltPt.x(), 
                     rbPt.y() - ltPt.y());
    if(newImgSize == size) {
        return ;
    }
    
    QImage newImg(newImgSize, QImage::Format_ARGB8555_Premultiplied);

    for(int x = 0; x < newImgSize.width(); ++x) {
        for(int y = 0; y < newImgSize.height(); ++y) {
            newImg.setPixel(x, y, image.pixel(x + ltPt.x(),
                                              y + ltPt.y()));
        }
    }
    
    newImg.save(filePath, "PNG");

    return ;
}
