#include "buttonwindow.h"
#include <QPushButton>
#include <QInputDialog>
#include <QLabel>
#include <QGroupBox>
#include <QDir>
#include <iostream>

ButtonWindow::ButtonWindow(QWidget *parent) : QWidget(parent)
{
    int n = 12;
    int buttonHeight = 30;
    int buttonWidth = 140;
    setFixedSize(buttonWidth + 20, buttonHeight*n + 20 + (n-1)*10);
    // Create and position the buttons

    //QOL buttons 
    copyButton = new QPushButton("Copy Image", this);
    copyButton->setGeometry(15, 10, buttonWidth, buttonHeight);

    vertFlipButton = new QPushButton("Flip Vertically", this);
    vertFlipButton->setGeometry(15, 1*40+10, buttonWidth, buttonHeight);

    horFlipButton = new QPushButton("Flip Horizontally", this);
    horFlipButton->setGeometry(15, 2*40+10, buttonWidth, buttonHeight);

    greyScaleButton = new QPushButton("Grey Scale", this);
    greyScaleButton->setGeometry(15, 3*40+10, buttonWidth, buttonHeight);

    quantImageButton = new QPushButton("Quantization", this);
    quantImageButton->setGeometry(15, 4*40+10, buttonWidth, buttonHeight);

    saveImageButton = new QPushButton("Save as JPEG", this);
    saveImageButton->setGeometry(15, 5*40+10, buttonWidth, buttonHeight);

    histogramButton = new QPushButton("Histogram", this);
    histogramButton->setGeometry(15, 6*40+10, buttonWidth, buttonHeight);

    brightButton = new QPushButton("Change Brightness", this);
    brightButton->setGeometry(15, 7*40+10, buttonWidth, buttonHeight);

    contrastButton = new QPushButton("Change Constrast", this);
    contrastButton->setGeometry(15, 8*40+10, buttonWidth, buttonHeight);

    negativeButton = new QPushButton("Negative", this);
    negativeButton->setGeometry(15, 9*40+10, buttonWidth, buttonHeight);

    equalizeButton = new QPushButton("Equalize Histogram", this);
    equalizeButton->setGeometry(15, 10*40+10, buttonWidth, buttonHeight);

    quitButton = new QPushButton("Quit", this);
    quitButton->setGeometry(15, 11*40+10, buttonWidth, buttonHeight);


    //connections
    connect(copyButton, SIGNAL( clicked(bool)), this, SLOT( copyClicked()) );
    connect( quitButton, SIGNAL(clicked(bool)), QApplication::instance(),SLOT(quit()) );

    connect( vertFlipButton, SIGNAL( clicked(bool) ), this, SLOT( vertFlipClicked()) );
    connect( horFlipButton, SIGNAL( clicked(bool) ), this, SLOT( horFlipClicked()) );
    connect( greyScaleButton, SIGNAL( clicked(bool) ), this, SLOT( greyScaleClicked()) );
    connect( quantImageButton, SIGNAL( clicked(bool) ), this, SLOT( quantClicked()) );
    connect( saveImageButton, SIGNAL( clicked(bool) ), this, SLOT( saveClicked()) );

    connect( histogramButton, SIGNAL( clicked(bool) ), this, SLOT( histogramClicked()) );
    connect( brightButton, SIGNAL( clicked(bool) ), this, SLOT( brightClicked()) );
    connect( contrastButton, SIGNAL( clicked(bool)), this, SLOT( contrastClicked()) );
    connect( negativeButton, SIGNAL( clicked(bool)) , this, SLOT(negativeClicked()));
    connect( equalizeButton, SIGNAL( clicked(bool)), this, SLOT(equalizeClicked()));

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

}
void ButtonWindow::rotateClockClicked(){

}
void ButtonWindow::rotateCounterClicked(){

}
void ButtonWindow::applyFilterClicked(){

}
