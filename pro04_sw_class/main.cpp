#include "widget.h"
#include "ui_widget.h"

#include <QApplication>
#include <wiringPi.h>

widget *pW;
const int swPin[] = {4,17,27,22};

void isrFunc1(void);
void isrFunc2(void);
void isrFunc3(void);
void isrFunc4(void);
void isrFuncAll(void);
void (*fp[4])(void) = {isrFunc1,isrFunc2,isrFunc3,isrFunc4};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget w;
    pW = &w;
    w.show();

    for(int i=0; i<4; i++)
    {
       //  w.SW[i] = new GPIO_SW(swPin[i], INT_EDGE_RISING, fp[i]);
        w.SW[i] = new GPIO_SW(swPin[i], INT_EDGE_RISING, isrFuncAll);
    }

    return a.exec();
}

void isrFunc1(void)
{
    if(pW->ui->label_SW_PIC1->isEnabled())
        pW->ui->label_SW_PIC1->setEnabled(false);
    else
        pW->ui->label_SW_PIC1->setEnabled(true);
}

void isrFunc2(void)
{
    if(pW->ui->label_SW_PIC2->isEnabled())
        pW->ui->label_SW_PIC2->setEnabled(false);
    else
        pW->ui->label_SW_PIC2->setEnabled(true);
}

void isrFunc3(void)
{
    if(pW->ui->label_SW_PIC3->isEnabled())
        pW->ui->label_SW_PIC3->setEnabled(false);
    else
        pW->ui->label_SW_PIC3->setEnabled(true);

}

void isrFunc4(void)
{
    if(pW->ui->label_SW_PIC4->isEnabled())
        pW->ui->label_SW_PIC4->setEnabled(false);
    else
        pW->ui->label_SW_PIC4->setEnabled(true);
}

void isrFuncAll(void)
{
    QLabel *SW_PIC[4] = {pW->ui->label_SW_PIC1,pW->ui->label_SW_PIC2,
                         pW->ui->label_SW_PIC3,pW->ui->label_SW_PIC4};

    for(int i=0; i<4; i++){
        if(pW->SW[i]->swRead()){
            if(SW_PIC[i]->isEnabled())
                SW_PIC[i]->setEnabled(false);
            else
                SW_PIC[i]->setEnabled(true);
        }
    }
}
