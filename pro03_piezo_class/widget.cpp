#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <wiringPi.h>
#include <softPwm.h>
#include <pthread.h>
#include "piezo.h"

int ledPin12[2] = {23,24};   // BCM 번호
int ledPin34[2] = {25,1};
int pinPiezo = 12;

int aMelody[] = {523,587,659,698,783,880,987,1046};
int aTime[] = {100,100,100,100,100,100,100,100};
//array<int, 8> aMelody2 = {523,587,659,698,783,880,987,1046};
int StarWarsMelody[] = { S_a, S_a, S_f, S_cH, S_a, S_f, S_cH, S_a, S_eH, S_eH,
                        S_eH, S_fH, S_cH, S_gS, S_f, S_cH, S_a, S_aH, S_a, S_a,
                        S_aH,S_gHS,S_gH,S_fHS,S_fH,S_fHS,S_mute,S_aS,S_dHS,S_dH,
                        S_cHS, S_cH, S_b, S_cH,S_mute, S_f, S_gS, S_f, S_a,S_cH,
                        S_a, S_cH, S_eH,S_aH,S_a,S_a,S_aH,S_gHS,S_gH,S_fHS,
                        S_fH,S_fHS,S_mute,S_aS,S_dHS,S_dH,S_cHS,S_cH,S_b,S_cH,
                        S_mute,S_f,S_gS,S_f,S_cH,S_a,S_f,S_c,S_a};
int StarWarsTime[] = {500,500,350,150,500,350,150,1000,500,500,
                      500,350,150,500,350,150,1000,500,350,150,
                      500,250,250,125,125,250,250,250,500,250,
                      250,125,125,250,250,125,500,375,125,500,
                      375,125,1000,500,350,150,500,250,250,125,
                      125,250,250,250,500,250,250,125,125,250,
                      250,250,500,375,125,500,375,125,1000};


// 일반 함수
void* playThread(void *arg);

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
    connect(ui->pushButton_play, &QPushButton::clicked, this, &widget::playButton);
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

int widget::playButton(bool value)
{
    QString sel = ui->comboBox_sel->currentText();
    qDebug() << sel.toUtf8().constData();

    pthread_t t_id;

    struct scaleTime music;

    if(sel == "음계"){
        music.scale = aMelody;
        music.time = aTime;
        music.cnt = _countof(aMelody);
    }
    else{
        music.scale = StarWarsMelody;
        music.time = StarWarsTime;
        music.cnt = _countof(StarWarsMelody);
    }

    if(pthread_create(&t_id,NULL,playThread, (void*)&music) != 0) return -1;

    return 0;
}

void* playThread(void *arg)
{
    struct scaleTime temp = *((struct scaleTime*)arg);

    TONE_PIEZO PIEZO(pinPiezo);

    PIEZO.setMelodyStruct(temp);

    return NULL;
}

