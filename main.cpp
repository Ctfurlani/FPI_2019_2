#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

#include "buttonwindow.h"
#include "imagewindow.h"

#include <QApplication>
#include <QObject>
char* T = "Gramado_72k.jpg";

int main(int argc, char *argv[])
{
    // Windows and buttons
    QApplication a(argc, argv);

    ImageWindow processedImageWindow, original;

    processedImageWindow.setWindowTitle("Processed Image");
    processedImageWindow.loadImage(T);
    processedImageWindow.move(600,0);
    processedImageWindow.show();

    original.setWindowTitle("Original Image");
    original.loadImage(T);
    original.move(0,0);
    original.show();

    ButtonWindow buttonWindow;
    buttonWindow.setWindowTitle("Options");
    buttonWindow.move(1150,0);
    buttonWindow.show();

    // Setup connections
    QObject::connect(&buttonWindow, SIGNAL( horFlip() ), &processedImageWindow, SLOT( horizontalFlip()) );
    QObject::connect(&buttonWindow, SIGNAL( vertFlip() ), &processedImageWindow, SLOT( verticalFlip()) );
    QObject::connect(&buttonWindow, SIGNAL( grScale() ), &processedImageWindow, SLOT( greyScale()) );
    QObject::connect(&buttonWindow, SIGNAL( save(char*) ), &processedImageWindow, SLOT( saveImage(char*)) );
    QObject::connect(&buttonWindow, SIGNAL( quantization(int) ), &processedImageWindow, SLOT( quantization(int)) );
    QObject::connect(&buttonWindow, SIGNAL( brightness(int) ), &processedImageWindow, SLOT( brightness(int)) );
    QObject::connect(&buttonWindow, SIGNAL( contrast(double) ), &processedImageWindow, SLOT( contrast(double)) );
    QObject::connect(&buttonWindow, SIGNAL( negative() ), &processedImageWindow, SLOT( negative()) );
    QObject::connect(&buttonWindow, SIGNAL( copy() ), &processedImageWindow, SLOT( copyImage()) );
    QObject::connect(&buttonWindow, SIGNAL( equalize() ), &processedImageWindow, SLOT( equalizeHistogram()) );
    return a.exec();
    //return 0;

}
