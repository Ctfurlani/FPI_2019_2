#ifndef BUTTONWINDOW_H
#define BUTTONWINDOW_H

#include <QApplication>
#include <QWidget>

class QPushButton;
class ButtonWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonWindow(QWidget *parent = nullptr);
signals:
    void vertFlip();
    void horFlip();
    void grScale();
    void quantization(int);
    void save(char*);
    void copy();

    void showHistogram();
    void brightness(int);
    void contrast(double);
    void negative();
    void equalize();

private slots:
    void vertFlipClicked();
    void horFlipClicked();
    void greyScaleClicked();
    void quantClicked();
    void saveClicked();
    void copyClicked();

    void histogramClicked();
    void brightClicked();
    void contrastClicked();
    void negativeClicked();
    void equalizeClicked();
private:
    //QOL buttons

    QPushButton *quitButton;
    QPushButton *copyButton;

    QPushButton *saveImageButton;
    QPushButton *vertFlipButton;
    QPushButton *horFlipButton;
    QPushButton *greyScaleButton;
    QPushButton *quantImageButton;

    QPushButton *histogramButton;
    QPushButton *brightButton;
    QPushButton *contrastButton;
    QPushButton *negativeButton;
    QPushButton *equalizeButton;
};

#endif // BUTTONWINDOW_H
