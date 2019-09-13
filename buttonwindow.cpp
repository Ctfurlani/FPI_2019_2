#include "buttonwindow.h"
#include <QPushButton>
#include <QInputDialog>
#include <QLabel>
#include <QDir>
#include <iostream>

ButtonWindow::ButtonWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(150, 250);
    // Create and position the buttons

    vertFlipButton = new QPushButton("Flip Vertically", this);
    vertFlipButton->setGeometry(15, 10, 120, 30);

    horFlipButton = new QPushButton("Flip Horizontally", this);
    horFlipButton->setGeometry(15, 50, 120, 30);

    greyScaleButton = new QPushButton("Grey Scale", this);
    greyScaleButton->setGeometry(15, 90, 120, 30);

    quantImageButton = new QPushButton("Quantization", this);
    quantImageButton->setGeometry(15, 130, 120, 30);

    saveImageButton = new QPushButton("Save as JPEG", this);
    saveImageButton->setGeometry(15, 170, 120, 30);

    quitButton = new QPushButton("Quit", this);
    quitButton->setGeometry(15, 210, 120, 30);

    //connections
    connect(quitButton, SIGNAL(clicked(bool)), QApplication::instance(),SLOT(quit()));
    connect(vertFlipButton, SIGNAL (clicked(bool)), this, SLOT(vertFlipClicked()));
    connect(horFlipButton, SIGNAL (clicked(bool)), this, SLOT(horFlipClicked()));
    connect(greyScaleButton, SIGNAL (clicked(bool)), this, SLOT(greyScaleClicked()));
    connect(quantImageButton, SIGNAL (clicked(bool)), this, SLOT(quantClicked()));
    connect(saveImageButton, SIGNAL (clicked(bool)), this, SLOT(saveClicked()));
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
