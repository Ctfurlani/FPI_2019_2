#include <QtWidgets>
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

    secondValue = new QDoubleSpinBox;
    secondValue->setRange(-99999,99999);
    secondValue->setSingleStep(1.0);
    secondValue->setValue(1.0);

    thirdValue = new QDoubleSpinBox;
    thirdValue->setRange(-99999,99999);
    thirdValue->setSingleStep(1.0);
    thirdValue->setValue(1.0);

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

    fifthValue = new QDoubleSpinBox;
    fifthValue->setRange(-99999,99999);
    fifthValue->setSingleStep(1.0);
    fifthValue->setValue(1.0);

    sixthValue = new QDoubleSpinBox;
    sixthValue->setRange(-99999,99999);
    sixthValue->setSingleStep(1.0);
    sixthValue->setValue(1.0);


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

    eighthValue = new QDoubleSpinBox;
    eighthValue->setRange(-99999,99999);
    eighthValue->setSingleStep(1.0);
    eighthValue->setValue(1.0);

    ninthValue = new QDoubleSpinBox;
    ninthValue->setRange(-99999,99999);
    ninthValue->setSingleStep(1.0);
    ninthValue->setValue(1.0);


    QVBoxLayout *row3 = new QVBoxLayout;

    row3->addWidget(seventhValue);
    row3->addWidget(eighthValue);
    row3->addWidget(ninthValue);

    thirdRow->setLayout(row3);

}
