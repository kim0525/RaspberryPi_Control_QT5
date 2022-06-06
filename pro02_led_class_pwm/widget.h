#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "GPIO_PWM_API.h"

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();

private:
    Ui::widget *ui;
    GPIO_LED *LED12[2];
    PWM_LED *LED34[2];
public slots:
    void chkChanged(bool value);
    void sliderChanged(int value);
};
#endif // WIDGET_H
