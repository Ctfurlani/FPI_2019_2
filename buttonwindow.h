#ifndef BUTTONWINDOW_H
#define BUTTONWINDOW_H

#include <QApplication>
#include <QLabel>
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

    // Trab 2 Part 1
    void histogramClicked();
    void brightClicked();
    void contrastClicked();
    void negativeClicked();
    void equalizeClicked();

    // Trab 2 Part 2
    void zoomOutClicked();
    void zoomInClicked();
    void rotateClockClicked();
    void rotateCounterClicked();
    void applyFilterClicked();

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

    QPushButton *rotateClockwise;
    QPushButton *rotateCounterClockwise;
    QPushButton *zoomIn;
    QPushButton *zoomOut;
    QPushButton *applyFilter;
};

#endif // BUTTONWINDOW_H
