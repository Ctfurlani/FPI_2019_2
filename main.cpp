#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

#include "buttonwindow.h"
#include "imagewindow.h"

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{

    // Windows and buttons
    QApplication a(argc, argv);

    ImageWindow processedImageWindow, original;
    processedImageWindow.setWindowTitle("Processed Image");
    processedImageWindow.loadImage(argv[1]);
    original.setWindowTitle("Original Image");
    original.loadImage(argv[1]);
    original.show();
    processedImageWindow.show();

    ButtonWindow buttonWindow;
    buttonWindow.setWindowTitle("Options");
    buttonWindow.show();

    // Setup connections
    QObject::connect(&buttonWindow,SIGNAL(horFlip()), &processedImageWindow, SLOT(horizontalFlip() ));
    QObject::connect(&buttonWindow,SIGNAL(vertFlip()), &processedImageWindow, SLOT(verticalFlip() ));
    QObject::connect(&buttonWindow,SIGNAL(grScale()), &processedImageWindow, SLOT(greyScale() ));
    QObject::connect(&buttonWindow, SIGNAL(save(char*)), &processedImageWindow, SLOT(saveImage(char*)));
    QObject::connect(&buttonWindow, SIGNAL(quantization(int)), &processedImageWindow, SLOT(quantization(int)));

    return a.exec();
    //return 0;

}
