#include "buttonwindow.h"
#include <QPushButton>
#include <QInputDialog>
#include <QLabel>

#include <QDir>
#include <iostream>
#include <QtWidgets>

ButtonWindow::ButtonWindow(QWidget *parent) : QWidget(parent)
{
    createSimpleGroup();
    createAdvGroup();
    createZoomGroup();
    createConvGroup();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(simpleOpGroup);
    layout->addWidget(advancedOpGroup);
    layout->addWidget(zoomAndRotateGroup);
    layout->addWidget(convolutionGroup);

    setLayout(layout);

    setWindowTitle("Image Processing");
}
void ButtonWindow::createSimpleGroup(){
    simpleOpGroup = new QGroupBox("Simple Operations");

    copyButton = new QPushButton("Copy Image", this);
    vertFlipButton = new QPushButton("Vertical flip", this);
    horFlipButton = new QPushButton("Horizontal Flip",this);
    greyScaleButton = new QPushButton("Luminescence",this);
    quantImageButton = new QPushButton("Quantization",this);
    quitButton = new QPushButton("Quit", this);

    quantShades = new QSpinBox;
    quantShades->setRange(0,256);
    quantShades->setSingleStep(1);
    quantShades->setValue(256);


    saveImageButton = new QPushButton("Save Image", this);

    QGridLayout *quantLayout = new QGridLayout;
    quantLayout->addWidget(quantShades, 0, 0);
    quantLayout->addWidget(quantImageButton, 0, 1);

    QVBoxLayout *simpleLayout = new QVBoxLayout;
    simpleLayout->addWidget(copyButton);
    simpleLayout->addWidget(vertFlipButton);
    simpleLayout->addWidget(horFlipButton);
    simpleLayout->addWidget(greyScaleButton);
    simpleLayout->addLayout(quantLayout);
    simpleLayout->addWidget(saveImageButton);
    simpleLayout->addWidget(quitButton);

    simpleOpGroup->setLayout(simpleLayout);

    // Create connections
    connect( copyButton, SIGNAL( clicked(bool)), this, SLOT( copyClicked()) );
    connect( quitButton, SIGNAL( clicked(bool)), QApplication::instance(),SLOT(quit()) );
    connect( vertFlipButton, SIGNAL( clicked(bool) ), this, SLOT( vertFlipClicked()) );
    connect( horFlipButton, SIGNAL( clicked(bool) ), this, SLOT( horFlipClicked()) );
    connect( greyScaleButton, SIGNAL( clicked(bool) ), this, SLOT( greyScaleClicked()) );
    connect( quantImageButton, SIGNAL( clicked(bool) ), this, SLOT( quantClicked()) );
    connect( saveImageButton, SIGNAL( clicked(bool) ), this, SLOT( saveClicked()) );


}

void ButtonWindow::createAdvGroup(){
    advancedOpGroup = new QGroupBox("Advanced Operations");

    histogramButton = new QPushButton("Show Histogram", this);
    negativeButton = new QPushButton("Negative", this);
    equalizeButton = new QPushButton("Equalize", this);

    QGridLayout *brightLayout = new QGridLayout;
    brightButton = new QPushButton("Change Brightness", this);
    brightValue = new QSpinBox;
    brightValue->setRange(-255, 255);
    brightValue->setValue(0);
    brightValue->setSingleStep(1);

    brightLayout->addWidget(brightValue, 0, 0);
    brightLayout->addWidget(brightButton, 0, 1);

    QGridLayout *contrastLayout = new QGridLayout;
    contrastButton = new QPushButton("Change Constrast", this);
    contrastValue = new QDoubleSpinBox;
    contrastValue->setRange(1.0, 255.0);
    contrastValue->setSingleStep(1.0);
    contrastValue->setValue(1.0);

    contrastLayout->addWidget(contrastValue, 0, 0);
    contrastLayout->addWidget(contrastButton, 0, 1);

    QVBoxLayout *advancedLayout = new QVBoxLayout;
    advancedLayout->addWidget(histogramButton);
    advancedLayout->addWidget(negativeButton);
    advancedLayout->addWidget(equalizeButton);
    advancedLayout->addLayout(brightLayout);
    advancedLayout->addLayout(contrastLayout);

    advancedOpGroup->setLayout(advancedLayout);

    // Create connections
    connect( histogramButton, SIGNAL( clicked(bool) ), this, SLOT( histogramClicked()) );
    connect( brightButton, SIGNAL( clicked(bool) ), this, SLOT( brightClicked()) );
    connect( contrastButton, SIGNAL( clicked(bool)), this, SLOT( contrastClicked()) );
    connect( negativeButton, SIGNAL( clicked(bool)) , this, SLOT(negativeClicked()));
    connect( equalizeButton, SIGNAL( clicked(bool)), this, SLOT(equalizeClicked()));

}

void ButtonWindow::createZoomGroup(){
    zoomAndRotateGroup = new QGroupBox("Zoom and Rotate");

    zoomInButton = new QPushButton(tr("Zoom in %1x%2").arg(2).arg(2), this);
    rotateClockwiseButton = new QPushButton("Rotate clockwise",this);
    rotateCounterClockwiseButton = new QPushButton("Rotate counter clockwise", this);

    QGridLayout *zoomOutLayout = new QGridLayout;
    zoomOutValue1 = new QSpinBox;
    zoomOutValue1->setMinimum(1);
    zoomOutValue1->setValue(1);

    zoomOutValue2 = new QSpinBox;
    zoomOutValue2->setMinimum(1);
    zoomOutValue2->setValue(1);
    zoomOutButton = new QPushButton("Zoom Out",this);
    zoomOutLayout->addWidget(zoomOutValue1, 0, 0);
    zoomOutLayout->addWidget(zoomOutValue2, 0, 1);
    zoomOutLayout->addWidget(zoomOutButton, 0, 2);

    QVBoxLayout *zoomAndRotateLayout = new QVBoxLayout;
    zoomAndRotateLayout->addWidget(zoomInButton);
    zoomAndRotateLayout->addWidget(rotateClockwiseButton);
    zoomAndRotateLayout->addWidget(rotateCounterClockwiseButton);
    zoomAndRotateLayout->addLayout(zoomOutLayout);

    zoomAndRotateGroup->setLayout(zoomAndRotateLayout);

    // Create Connections
    connect( zoomInButton, SIGNAL( clicked(bool)), this, SLOT(zoomInClicked()) );
    connect( rotateClockwiseButton, SIGNAL( clicked(bool)), this, SLOT( rotateClockClicked() ));


}
void ButtonWindow::createConvGroup(){
    gaussianFilterButton = new QPushButton("Gaussian", this);
    laplacianFilteButtonr = new QPushButton("Laplacian", this);
    highPassFilterButton = new QPushButton("High Pass", this);
    prewittHxFilterButton = new QPushButton("Prewitt Hx", this);
    prewittHyFilterButton = new QPushButton("Prewitt Hy", this);
    sobelHxFilterButton = new QPushButton("Sobel Hx",this);
    sobelHyFilterButton = new QPushButton("Sobel Hy", this);
    convoluteButton = new QPushButton("Convolute", this);

    convolutionGroup = new QGroupBox("Convolution Filters");
    QVBoxLayout *convLayout = new QVBoxLayout;
    convLayout->addWidget(gaussianFilterButton);
    convLayout->addWidget(laplacianFilteButtonr);
    convLayout->addWidget(highPassFilterButton);
    convLayout->addWidget(prewittHxFilterButton);
    convLayout->addWidget(prewittHyFilterButton);
    convLayout->addWidget(sobelHxFilterButton);
    convLayout->addWidget(sobelHyFilterButton);
    convLayout->addSpacing(10);
    convLayout->addWidget(convoluteButton);

    convolutionGroup->setLayout(convLayout);
}



void ButtonWindow::vertFlipClicked(){
    emit vertFlip();
}

void ButtonWindow::horFlipClicked(){
    emit horFlip();
}

void ButtonWindow::greyScaleClicked(){
    emit grScale();
}
void ButtonWindow::histogramClicked(){
    emit showHistogram();
}
void ButtonWindow::quantClicked(){
    QLabel *integerLabel = new QLabel(this);
    bool ok;
    int i = QInputDialog::getInt(this, tr("Quantization"), tr("Number of shades:"), 256, 1, 256, 1, &ok);
    if (ok){
        integerLabel->setText(tr("%1%").arg(i));
        emit quantization(i);
    }
}

void ButtonWindow::saveClicked(){
    QLabel *stringLabel = new QLabel(this);
    bool ok;

    QString text = QInputDialog::getText(this, tr("Save Image"), tr("Image name:"), QLineEdit::Normal, nullptr, &ok);

    if(ok and !text.isEmpty()){
        stringLabel->setText(text);
        emit save(text.toUtf8().data());
    }
}

void ButtonWindow::brightClicked(){
    QLabel *integerLabel = new QLabel(this);
    bool ok;
    int i = QInputDialog::getInt(this, tr("Brightness"), tr("Change brightness:"), 0, -255, 255, 1, &ok);
    if (ok){
        integerLabel->setText(tr("%1%").arg(i));
        emit brightness(i);
    }
}


void ButtonWindow::contrastClicked(){
    QLabel *integerLabel = new QLabel(this);
    bool ok;
    double i = QInputDialog::getDouble(this, tr("Brightness"), tr("Change brightness:"), 1, 0, 255, 2, &ok);
    if (ok and i>0){
        integerLabel->setText(tr("%1%").arg(i));
        emit contrast(i);
    }
}

void ButtonWindow::negativeClicked(){
    emit negative();
}

void ButtonWindow::copyClicked(){
    emit copy();
}
void ButtonWindow::equalizeClicked(){
    emit equalize();
}

void ButtonWindow::zoomOutClicked(){

}
void ButtonWindow::zoomInClicked(){
    emit zoomIn();

}
void ButtonWindow::rotateClockClicked(){
    emit rotateClockwise();
}
void ButtonWindow::rotateCounterClicked(){

}
void ButtonWindow::applyFilterClicked(){

}
