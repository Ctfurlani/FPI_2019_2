#ifndef BUTTONWINDOW_H
#define BUTTONWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>


QT_BEGIN_NAMESPACE
class QSpinBox;
class QPushButton;
class QLineEdit;
class QGroupBox;
class QDoubleSpinBox;
class QLabel;
QT_END_NAMESPACE

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

    void zoomIn();
    void zoomOut(int, int);
    void rotateClockwise();
    void rotateCounterClock();

    void gaussian();
    void laplacian();
    void highPass();
    void prewittHx();
    void prewittHy();
    void sobelHx();
    void sobelHy();
    void applyFilter();


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

    void gaussianClicked();
    void laplacianClicked();
    void highPassClicked();
    void prewittHxClicked();
    void prewittHyCLicked();
    void sobelHxClicked();
    void sobelHyClicked();
    void convoluteClicked();

private:
    //QOL buttons
    QPushButton *quitButton;
    QPushButton *copyButton;

    //Trab 1
    QPushButton *saveImageButton;
    QPushButton *vertFlipButton;
    QPushButton *horFlipButton;
    QPushButton *greyScaleButton;
    QPushButton *quantImageButton;
    // Trab 2 Part 2
    QPushButton *histogramButton;
    QPushButton *brightButton;
    QPushButton *contrastButton;
    QPushButton *negativeButton;
    QPushButton *equalizeButton;
    QPushButton *histMatchingButton;

    QPushButton *rotateClockwiseButton;
    QPushButton *rotateCounterClockwiseButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;

    QPushButton *gaussianFilterButton;
    QPushButton *laplacianFilterButton;
    QPushButton *highPassFilterButton;
    QPushButton *prewittHxFilterButton;
    QPushButton *prewittHyFilterButton;
    QPushButton *sobelHxFilterButton;
    QPushButton *sobelHyFilterButton;
    QPushButton *convoluteButton;

    QLineEdit *histMatchingTarget;
    QSpinBox *quantShades;
    QSpinBox *brightValue;
    QDoubleSpinBox *contrastValue;
    QSpinBox *zoomOutValue1, *zoomOutValue2;

    QGroupBox *simpleOpGroup;
    QGroupBox *advancedOpGroup;
    QGroupBox *zoomAndRotateGroup;
    QGroupBox *convolutionGroup;

    bool convBool = false;

    void createSimpleGroup();
    void createAdvGroup();
    void createZoomGroup();
    void createConvGroup();

};

#endif // BUTTONWINDOW_H
