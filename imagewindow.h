#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QtCharts>

extern "C"{
#include "jpeg-9c/jpeglib.h"
}

class QLabel;
class ImageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWindow(QWidget *parent = nullptr);

signals:

public slots:
    void verticalFlip();
    void horizontalFlip();
    void greyScale();
    void quantization(int quant);
    void loadImage(char* filename);
    void saveImage(char* filename);
    void copyImage();


    QImage showHistogram();
    void imageHistogram();
    void brightness(int bright);
    void contrast(double cont);
    void negative();
    void equalizeHistogram();
private:
    char *filename;
    JSAMPROW imageData;
    JDIMENSION width, height;
    QLabel *label;

    QWidget *histogramWindow;
    QWidget *equalizedImageWindow;
    QWidget *equalizedHistogramWindow;
    int histogram[256];
    void histogramComputation();

};

#endif // ImageWindow
