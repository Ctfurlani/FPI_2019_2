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


    QImage showHistogram(int *);
    void imageHistogram();
    void brightness(int bright);
    void contrast(double cont);
    void negative();
    void equalizeHistogram();
    void histogramMatching(char* filename);

    void zoomOut(int h, int w);
    void zoomIn();
    void rotate90CounterClockwise();
    void rotate90Clockwise();
    void applyFilter(double *, bool);

private:
    char *filename = nullptr;
    JSAMPROW imageData = nullptr;
    JDIMENSION width, height;
    QLabel *label = nullptr;
    bool greyImage = false;

    QWidget *histogramWindow = nullptr;
    QWidget *equalizedImageWindow = nullptr;
    QWidget *equalizedHistogramWindow = nullptr;
    int *histogram = nullptr;
    int* histogramComputation(JSAMPROW data);
    void greyScaleImage(JSAMPROW data, int w, int h);
    int closestShade(int shade, int *src, int *target);


};

#endif // ImageWindow
