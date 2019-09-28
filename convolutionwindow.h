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

public slots:
private:
    QDoubleSpinBox *firstValue, *secondValue, *thirdValue;
    QDoubleSpinBox *fourthValue, *fifthValue, *sixthValue;
    QDoubleSpinBox *seventhValue, *eighthValue, *ninthValue;

    QGroupBox *firstRow, *secondRow, *thirdRow;

    void createFirstRow();
    void createSecondRow();
    void createThirdRow();
};

#endif // CONVOLUTIONWINDOW_H
