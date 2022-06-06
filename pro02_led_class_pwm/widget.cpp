#include "widget.h"
#include "ui_widget.h"
#include <wiringPi.h>
#include <softPwm.h>

int ledPin12[2] = {23,24};   // BCM 번호
int ledPin34[2] = {25,1};

widget::widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);

    for(int i=0; i<2; i++)
        LED12[i] = new GPIO_LED(ledPin12[i]);
    for(int i=0; i<2; i++)
        LED34[i] = new PWM_LED(ledPin34[i]);

    connect(ui->checkBox_LED1, &QCheckBox::clicked, this, &widget::chkChanged);
    connect(ui->checkBox_LED2, &QCheckBox::clicked, this, &widget::chkChanged);
    connect(ui->Slider_LED3, QOverload<int>::of(&QSlider::valueChanged), this, &widget::sliderChanged);
    connect(ui->Slider_LED4, QOverload<int>::of(&QSlider::valueChanged), this, &widget::sliderChanged);
}

widget::~widget()
{
    delete ui;
    for(int i=0; i<2; i++){
        delete LED12[i];
        delete LED34[i];
    }
}

void widget::chkChanged(bool value)
{
    QCheckBox *chkBox[2] = {ui->checkBox_LED1, ui->checkBox_LED2};
    int i;

    for(i=0; i<2; i++)
    {
        if(sender() == chkBox[i])
        {
            qDebug("LED%d이 체크됐습니다.\n", i+1);
            LED12[i]->ledWrite(chkBox[i]->isChecked());
        }
    }
}

void widget::sliderChanged(int value)
{
    QSlider *sliderBox[2] = {ui->Slider_LED3, ui->Slider_LED4};
    int i;

    for(i=0; i<2; i++)
    {
        if(sender() == sliderBox[i])
        {
            qDebug("LED%d이 체크됐습니다.\n", i+3);
            LED34[i]->setLedBright(value);
        }
    }
}

