#define _countof(_Array)    sizeof(_Array)/sizeof(_Array[0])

#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <wiringPi.h>
#include <softPwm.h>
#include <pthread.h>
#include "piezo.h"

// piezo Melody
int aMelody[] = {523,587,659,698,783,880,987,1046}; // 음계
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


// ========================== 전역변수 ====================
// 핀 번호 할당
const int ledPin12[] = {23,24};   // BCM 번호
const int ledPin34[] = {25,1};
const int pinPiezo = 12;
const int RGBLedPin[] = {0,1,2};
const int ServoPin[] = {3,4};

Ui::widget *pUi;
int melody_state = 0;   // 0:STOP, 1:PLAY

// 일반 함수
void* playThread(void *arg);    // thread

widget::widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    pUi = ui;   // 전역 포인터 변수에 저장
    ui->setupUi(this);    

    for(int i=0; i<2; i++){
        LED12[i] = new GPIO_LED(ledPin12[i]);
        LED34[i] = new PWM_LED(ledPin34[i]);
    }
    for (int i =0; i<3; i++){
        RGB_LED[i] = new I2C_PCA9685(PCA9685_I2C_ADDR, i);
    }
    for(int i=0; i<2; i++){
        SERVO[i] = new I2C_PCA9685(PCA9685_I2C_ADDR, i+3);
    }

    connect(ui->checkBox_LED1, &QCheckBox::clicked, this, &widget::chkChanged);
    connect(ui->checkBox_LED2, &QCheckBox::clicked, this, &widget::chkChanged);
    connect(ui->Slider_LED3, QOverload<int>::of(&QSlider::valueChanged), this, &widget::sliderChanged);
    connect(ui->Slider_LED4, QOverload<int>::of(&QSlider::valueChanged), this, &widget::sliderChanged);
    connect(ui->pushButton_play, &QPushButton::clicked, this, &widget::playButton);
    connect(ui->Slider_LED_RED, QOverload<int>::of(&QSlider::valueChanged), this, &widget::sliderRgb);
    connect(ui->Slider_LED_BLUE, QOverload<int>::of(&QSlider::valueChanged), this, &widget::sliderRgb);
    connect(ui->Slider_LED_GREEN, QOverload<int>::of(&QSlider::valueChanged), this, &widget::sliderRgb);
    connect(ui->Slider_SERVO1, QOverload<int>::of(&QSlider::valueChanged), this, &widget::sliderRgb);
    connect(ui->Slider_SERVO2, QOverload<int>::of(&QSlider::valueChanged), this, &widget::sliderRgb);

}

widget::~widget()
{
    delete ui;
    for(int i=0; i<2; i++){
        delete LED12[i];
        delete LED34[i];
    }
    for(int i=0; i<4; i++){
        delete SW[i];
    }
    for(int i=0; i<3; i++){
        delete RGB_LED[i];
    }
    for(int i=0; i<2; i++){
        delete SERVO[i];
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

    pthread_t piezo_t_id;

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

    // piezo의 상태값에 따른 동작
    QString btnText = ui->pushButton_play->text();

    if(melody_state == 0){  // melody가 안나오는 상태에서  버튼이 눌렸을 때
        ui->pushButton_play->setText("STOP");
        if(pthread_create(&piezo_t_id,NULL, playThread, (void*)&music) != 0) return -1;
        melody_state = 1;
    }
    else if(melody_state == 1){ // melody가 나오는 상태에서  버튼이 눌렸을 때
        ui->pushButton_play->setText("PLAY");
        melody_state = 0;
    }

   return 0;
}

void* playThread(void *arg)
{
    pUi->comboBox_sel->setEnabled(false);

    struct scaleTime temp = *((struct scaleTime*)arg);      // 객체를 새로 생성
    //struct scaleTime *pTemp = (struct scaleTime*)arg;     // 인자의 객체를 접근

    TONE_PIEZO PIEZO(pinPiezo);

    // PIEZO.setMelodyStruct(temp);
    //PIEZO.setMelody(temp.scale, temp.time, temp.cnt);
    for(int i=0;i<temp.cnt; i++)
    {
        PIEZO.setScaleOnTime( temp.scale[i], temp.time[i]);
        if(melody_state == 0) break;
    }

    pUi->comboBox_sel->setEnabled(true);
    pUi->pushButton_play->setText("PLAY");
    melody_state = 0;   // stop버튼을 누르지 않고 종료 됐을 때를 위해서

    return NULL;
}

void widget::sliderRgb(int value)
{
    QSlider *sliderBox[5] = {ui->Slider_LED_RED, ui->Slider_LED_BLUE,
                             ui->Slider_LED_GREEN, ui->Slider_SERVO1, ui->Slider_SERVO2};
    int i;

    for(i=0; i<5; i++)
    {
        if(sender() == sliderBox[i])
        {
            if (i == 0) RGB_LED[0]->setPwm(value * 40);
            else if (i == 1) RGB_LED[2]->setPwm((int)(value * 40.96));
            else if (i == 2) RGB_LED[1]->setPwm((int)(value * 40.96));
            else if (i == 3) SERVO[0]->setPwm(value);
            else if (i == 4) SERVO[1]->setPwm(value);
        }
    }
}
//void widget::sliderBlue(int value)
//{
//    RGB->setPwmBlu(value * 40);
//}
//void widget::sliderGreen(int value)
//{
//    RGB->setPwmGre(value * 40);
//}




