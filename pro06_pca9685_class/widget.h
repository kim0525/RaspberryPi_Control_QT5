#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "GPIO_PWM_API.h"
#include "I2C_API.h"

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();

public:
    Ui::widget *ui;
    GPIO_LED *LED12[2];
    PWM_LED *LED34[2];
    GPIO_SW *SW[4];
    GPIO_SW *PIR;
    I2C_SHT20 *SHT20;
    I2C_PCA9685 * RGB_LED[3];
    I2C_PCA9685 * SERVO[2];

public slots:
    void chkChanged(bool value);
    void sliderChanged(int value);
    int playButton(bool value);
    void sliderRgb(int value);

};
#endif // WIDGET_H
