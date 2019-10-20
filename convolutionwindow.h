#ifndef CONVOLUTIONWINDOW_H
#define CONVOLUTIONWINDOW_H

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;
class QGroupBox;

class ConvolutionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ConvolutionWindow(QWidget *parent = nullptr);

signals:
    void sendConvMatrix(double*, bool);

public slots:
    void convolute();
    void useGaussian();
    void useLaplacian();
    void useHighPass();
    void usePrewittHx();
    void usePrewittHy();
    void useSobelHx();
    void useSobelHy();
private:
    QDoubleSpinBox *firstValue, *secondValue, *thirdValue;
    QDoubleSpinBox *fourthValue, *fifthValue, *sixthValue;
    QDoubleSpinBox *seventhValue, *eighthValue, *ninthValue;

    QGroupBox *firstRow, *secondRow, *thirdRow;
    bool add127 = false;

    void createFirstRow();
    void createSecondRow();
    void createThirdRow();


};

#endif // CONVOLUTIONWINDOW_H
