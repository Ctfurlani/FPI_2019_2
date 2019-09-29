#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

#include "buttonwindow.h"
#include "imagewindow.h"
#include "convolutionwindow.h"

#include <QApplication>
#include <QObject>

char* T = "Gramado_72k.jpg";
char* U = "Underwater_53k.jpg";

int main(int argc, char *argv[])
{
    // Windows and buttons
    QApplication a(argc, argv);
    ImageWindow processedImageWindow, original;
    ConvolutionWindow convWindow;

    processedImageWindow.setWindowTitle("Processed Image");
    processedImageWindow.loadImage(argv[1]);
    processedImageWindow.move(600,0);
    processedImageWindow.show();

    original.setWindowTitle("Original Image");
    original.loadImage(argv[1]);
    original.move(0,0);
    original.show();

    ButtonWindow buttonWindow;
    buttonWindow.move(1150,0);
    buttonWindow.show();

    convWindow.show();

    // Setup connections
    QObject::connect(&buttonWindow, SIGNAL( horFlip() ), &processedImageWindow, SLOT( horizontalFlip()) );
    QObject::connect(&buttonWindow, SIGNAL( vertFlip() ), &processedImageWindow, SLOT( verticalFlip()) );
    QObject::connect(&buttonWindow, SIGNAL( grScale() ), &processedImageWindow, SLOT( greyScale()) );
    QObject::connect(&buttonWindow, SIGNAL( save(char*) ), &processedImageWindow, SLOT( saveImage(char*)) );
    QObject::connect(&buttonWindow, SIGNAL( quantization(int) ), &processedImageWindow, SLOT( quantization(int)) );

    QObject::connect(&buttonWindow, SIGNAL( showHistogram() ), &processedImageWindow, SLOT( imageHistogram()) );
    QObject::connect(&buttonWindow, SIGNAL( brightness(int) ), &processedImageWindow, SLOT( brightness(int)) );
    QObject::connect(&buttonWindow, SIGNAL( contrast(double) ), &processedImageWindow, SLOT( contrast(double)) );
    QObject::connect(&buttonWindow, SIGNAL( negative() ), &processedImageWindow, SLOT( negative()) );
    QObject::connect(&buttonWindow, SIGNAL( copy() ), &processedImageWindow, SLOT( copyImage()) );
    QObject::connect(&buttonWindow, SIGNAL( equalize() ), &processedImageWindow, SLOT( equalizeHistogram()) );
    QObject::connect(&buttonWindow, SIGNAL( histMatching(char*)), &processedImageWindow, SLOT( histogramMatching(char*) ) );

    QObject::connect(&buttonWindow, SIGNAL( zoomIn()), &processedImageWindow, SLOT( zoomIn()) );
    QObject::connect(&buttonWindow, SIGNAL( rotateClockwise()), &processedImageWindow, SLOT( rotate90Clockwise()));
    QObject::connect(&buttonWindow, SIGNAL( rotateCounterClock()), &processedImageWindow, SLOT(rotate90CounterClockwise()));
    QObject::connect(&buttonWindow, SIGNAL( zoomOut(int, int)), &processedImageWindow, SLOT(zoomOut(int, int)));


    // between windows
    QObject::connect(&buttonWindow, SIGNAL( gaussian()), &convWindow, SLOT( useGaussian()) );
    QObject::connect(&buttonWindow, SIGNAL( laplacian()), &convWindow, SLOT( useLaplacian()) );
    QObject::connect(&buttonWindow, SIGNAL( highPass()), &convWindow, SLOT( useHighPass()) );
    QObject::connect(&buttonWindow, SIGNAL( prewittHx()), &convWindow, SLOT( usePrewittHx()) );
    QObject::connect(&buttonWindow, SIGNAL( prewittHy()), &convWindow, SLOT( usePrewittHy()) );
    QObject::connect(&buttonWindow, SIGNAL( sobelHx()), &convWindow, SLOT( useSobelHx()) );
    QObject::connect(&buttonWindow, SIGNAL( sobelHy()), &convWindow, SLOT( useSobelHy()) );

    QObject::connect(&buttonWindow, SIGNAL( applyFilter()), &convWindow, SLOT( convolute()));
    QObject::connect(&convWindow, SIGNAL( sendConvMatrix(double*, bool) ), &processedImageWindow, SLOT( applyFilter(double*, bool) ));
    return a.exec();
    //return 0;

}
