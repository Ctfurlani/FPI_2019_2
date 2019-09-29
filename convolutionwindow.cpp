#include <QtWidgets>
#include <iostream>
#include "convolutionwindow.h"

ConvolutionWindow::ConvolutionWindow(QWidget *parent) : QWidget(parent)
{
    createFirstRow();
    createSecondRow();
    createThirdRow();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(firstRow);
    layout->addWidget(secondRow);
    layout->addWidget(thirdRow);
    setLayout(layout);

    setWindowTitle(tr("Convolution Matrix"));
}

void ConvolutionWindow::createFirstRow(){
    firstRow = new QGroupBox(tr("First Row"));

    firstValue = new QDoubleSpinBox;
    firstValue->setRange(-99999,99999);
    firstValue->setSingleStep(1.0);
    firstValue->setValue(1.0);
    firstValue->setDecimals(4);

    secondValue = new QDoubleSpinBox;
    secondValue->setRange(-99999,99999);
    secondValue->setSingleStep(1.0);
    secondValue->setValue(1.0);
    secondValue->setDecimals(4);

    thirdValue = new QDoubleSpinBox;
    thirdValue->setRange(-99999,99999);
    thirdValue->setSingleStep(1.0);
    thirdValue->setValue(1.0);
    thirdValue->setDecimals(4);

    QVBoxLayout *row1 = new QVBoxLayout;
    row1->addWidget(firstValue);
    row1->addWidget(secondValue);
    row1->addWidget(thirdValue);

    firstRow->setLayout(row1);
}

void ConvolutionWindow::createSecondRow(){

    secondRow = new QGroupBox(tr("Second Row"));
    // Second row

    fourthValue = new QDoubleSpinBox;
    fourthValue->setRange(-99999,99999);
    fourthValue->setSingleStep(1.0);
    fourthValue->setValue(1.0);
    fourthValue->setDecimals(4);

    fifthValue = new QDoubleSpinBox;
    fifthValue->setRange(-99999,99999);
    fifthValue->setSingleStep(1.0);
    fifthValue->setValue(1.0);
    fifthValue->setDecimals(4);

    sixthValue = new QDoubleSpinBox;
    sixthValue->setRange(-99999,99999);
    sixthValue->setSingleStep(1.0);
    sixthValue->setValue(1.0);
    sixthValue->setDecimals(4);


    QVBoxLayout *row2 = new QVBoxLayout;
    row2->addWidget(fourthValue);
    row2->addWidget(fifthValue);
    row2->addWidget(sixthValue);

    secondRow->setLayout(row2);

}

void ConvolutionWindow::createThirdRow(){

    thirdRow = new QGroupBox(tr("Third Row"));

    seventhValue = new QDoubleSpinBox;
    seventhValue->setRange(-99999,99999);
    seventhValue->setSingleStep(1.0);
    seventhValue->setValue(1.0);
    seventhValue->setDecimals(4);

    eighthValue = new QDoubleSpinBox;
    eighthValue->setRange(-99999,99999);
    eighthValue->setSingleStep(1.0);
    eighthValue->setValue(1.0);
    eighthValue->setDecimals(4);

    ninthValue = new QDoubleSpinBox;
    ninthValue->setRange(-99999,99999);
    ninthValue->setSingleStep(1.0);
    ninthValue->setValue(1.0);
    ninthValue->setDecimals(4);


    QVBoxLayout *row3 = new QVBoxLayout;

    row3->addWidget(seventhValue);
    row3->addWidget(eighthValue);
    row3->addWidget(ninthValue);

    thirdRow->setLayout(row3);

}
void ConvolutionWindow::convolute(){
    double filter[9];
    // Kernel is rotated
    filter[8] = firstValue->value();
    filter[7] = secondValue->value();
    filter[6] = thirdValue->value();
    filter[5] = fourthValue->value();
    filter[4] = fifthValue->value();
    filter[3] = sixthValue->value();
    filter[2] = seventhValue->value();
    filter[1] = eighthValue->value();
    filter[0] = ninthValue->value();
    emit sendConvMatrix(filter, add127);
}

void ConvolutionWindow::useGaussian(){
    firstValue->setValue(0.0625);
    secondValue->setValue(0.125);
    thirdValue->setValue(0.0625);

    fourthValue->setValue(0.125);
    fifthValue->setValue(0.25);
    sixthValue->setValue(0.125);

    seventhValue->setValue(0.0625);
    eighthValue->setValue(0.125);
    ninthValue->setValue(0.0625);
    add127 = false;
}
void ConvolutionWindow::useLaplacian(){
    firstValue->setValue(0.0);
    secondValue->setValue(-1.0);
    thirdValue->setValue(0.0);

    fourthValue->setValue(-1);
    fifthValue->setValue(4);
    sixthValue->setValue(-1);

    seventhValue->setValue(0.0);
    eighthValue->setValue(-1.0);
    ninthValue->setValue(0.0);
    add127 = true;
}
void ConvolutionWindow::useHighPass(){
    firstValue->setValue(-1.0);
    secondValue->setValue(-1.0);
    thirdValue->setValue(-1.0);

    fourthValue->setValue(-1.0);
    fifthValue->setValue(8.0);
    sixthValue->setValue(-1.0);

    seventhValue->setValue(-1.0);
    eighthValue->setValue(-1.0);
    ninthValue->setValue(-1.0);
    add127 = false;
}
void ConvolutionWindow::usePrewittHx(){
    firstValue->setValue(-1.0);
    secondValue->setValue(-1.0);
    thirdValue->setValue(-1.0);

    fourthValue->setValue(0.0);
    fifthValue->setValue(0.0);
    sixthValue->setValue(0.0);

    seventhValue->setValue(1.0);
    eighthValue->setValue(1.0);
    ninthValue->setValue(1.0);
    add127 = true;
}
void ConvolutionWindow::usePrewittHy(){
    firstValue->setValue(-1.0);
    secondValue->setValue(0.0);
    thirdValue->setValue(1.0);

    fourthValue->setValue(-1.0);
    fifthValue->setValue(0.0);
    sixthValue->setValue(1.0);

    seventhValue->setValue(-1.0);
    eighthValue->setValue(0.0);
    ninthValue->setValue(1.0);
    add127 = true;
}
void ConvolutionWindow::useSobelHx(){
    firstValue->setValue(-1.0);
    secondValue->setValue(-2.0);
    thirdValue->setValue(-1.0);

    fourthValue->setValue(0.0);
    fifthValue->setValue(0.0);
    sixthValue->setValue(0.0);

    seventhValue->setValue(1.0);
    eighthValue->setValue(2.0);
    ninthValue->setValue(1.0);
    add127 = true;
}
void ConvolutionWindow::useSobelHy(){
    firstValue->setValue(-1.0);
    secondValue->setValue(0.0);
    thirdValue->setValue(1.0);

    fourthValue->setValue(-2.0);
    fifthValue->setValue(0.0);
    sixthValue->setValue(2.0);

    seventhValue->setValue(-1.0);
    eighthValue->setValue(0.0);
    ninthValue->setValue(1.0);
    add127 = true;
}
