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

private slots:
    void vertFlipClicked();
    void horFlipClicked();
    void greyScaleClicked();
    void quantClicked();
    void saveClicked();

private:
    QPushButton *vertFlipButton;
    QPushButton *horFlipButton;
    QPushButton *greyScaleButton;
    QPushButton *quantImageButton;
    QPushButton *saveImageButton;
    QPushButton *quitButton;
};

#endif // BUTTONWINDOW_H
