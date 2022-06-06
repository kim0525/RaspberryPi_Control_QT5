#define _countof(_Array)     sizeof(_Array) / sizeof(_Array[0])

#include <iostream> 
using namespace std; 

#include "GPIO_PWM_API.h"
#include <wiringPi.h>
#include <unistd.h>
#include <softPwm.h>
#include <array>
#include "piezo.h"

int aMelody1[] = {523,587,659,698,783,880,987,1046};
//array<int, 8> aMelody2 = {523,587,659,698,783,880,987,1046};
int StarWarsMelody[] = { a, a, f, cH, a, f, cH, a, eH, eH,
                        eH, fH, cH, gS, f, cH, a, aH, a, a,
                        aH,gHS,gH,fHS,fH,fHS,mute,aS,dHS,dH,
                        cHS, cH, b, cH,mute, f, gS, f, a,cH,
                        a, cH, eH,aH,a,a,aH,gHS,gH,fHS,
                        fH,fHS,mute,aS,dHS,dH,cHS,cH,b,cH,
                        mute,f,gS,f,cH,a,f,c,a};
int StarWarsTime[] = {500,500,350,150,500,350,150,1000,500,500,
                      500,350,150,500,350,150,1000,500,350,150,
                      500,250,250,125,125,250,250,250,500,250,
                      250,125,125,250,250,125,500,375,125,500,
                      375,125,1000,500,350,150,500,250,250,125,
                      125,250,250,250,500,250,250,125,125,250,
                      250,250,500,375,125,500,375,125,1000};
void play(TONE_PIEZO song);

int main(void) {
	TONE_PIEZO piezo(12); 
    int i;

    cout << (sizeof aMelody1/sizeof aMelody1[0]) << endl;

    cout << "PIEZO TEST 1\n";
    for(i=0; i<(sizeof aMelody1/sizeof aMelody1[0]); i++){
        piezo.setScaleOnTime(aMelody1[i], 100);
    }

    // cout << "PIEZO TEST 2\n";
    // for(i=0; i<aMelody2.size();i++){
    //     piezo.setScaleOnTime(aMelody2[i], 100);
    // }
    // piezo.setScaleOFF();

    // melody 
    //play(piezo);

    piezo.setMelody(StarWarsMelody, StarWarsTime, _countof(StarWarsMelody));

    return 0;
    	
}

void play(TONE_PIEZO song)
{
  song.setScaleOnTime( a, 500);
  song.setScaleOnTime( a, 500);
  song.setScaleOnTime( f, 350);
  song.setScaleOnTime( cH, 150);
 
  song.setScaleOnTime( a, 500);
  song.setScaleOnTime( f, 350);
  song.setScaleOnTime( cH, 150);
  song.setScaleOnTime( a, 1000);
  song.setScaleOnTime( eH, 500);
 
  song.setScaleOnTime( eH, 500);    // 10
  song.setScaleOnTime( eH, 500);
  song.setScaleOnTime( fH, 350);
  song.setScaleOnTime( cH, 150);
  song.setScaleOnTime( gS, 500);
 
  song.setScaleOnTime( f, 350);
  song.setScaleOnTime( cH, 150);
  song.setScaleOnTime( a, 1000);
  song.setScaleOnTime( aH, 500);
  song.setScaleOnTime( a, 350);
 
  song.setScaleOnTime( a, 150);     // 20
  song.setScaleOnTime( aH, 500);
  song.setScaleOnTime( gHS, 250);
  song.setScaleOnTime( gH, 250);
  song.setScaleOnTime( fHS, 125);
 
  song.setScaleOnTime( fH, 125);
  song.setScaleOnTime( fHS, 250);
 
  song.setScaleOnTime(mute, 250);
 
  song.setScaleOnTime( aS, 250);
  song.setScaleOnTime( dHS, 500);
  song.setScaleOnTime( dH, 250);    // 30
  song.setScaleOnTime( cHS, 250);
  song.setScaleOnTime( cH, 125);
 
  song.setScaleOnTime( b, 125);
  song.setScaleOnTime( cH, 250);
 
  song.setScaleOnTime(mute, 250);
 
  song.setScaleOnTime( f, 125);
  song.setScaleOnTime( gS, 500);
  song.setScaleOnTime( f, 375);
  song.setScaleOnTime( a, 125);
  song.setScaleOnTime( cH, 500);    // 40
 
  song.setScaleOnTime( a, 375);
  song.setScaleOnTime( cH, 125);
  song.setScaleOnTime( eH, 1000);
  song.setScaleOnTime( aH, 500);
  song.setScaleOnTime( a, 350);
 
  song.setScaleOnTime( a, 150);
  song.setScaleOnTime( aH, 500);
  song.setScaleOnTime( gHS, 250);
  song.setScaleOnTime( gH, 250);
  song.setScaleOnTime( fHS, 125);   // 50
 
  song.setScaleOnTime( fH, 125);
  song.setScaleOnTime( fHS, 250);
 
  song.setScaleOnTime(mute, 250);
 
  song.setScaleOnTime( aS, 250);
  song.setScaleOnTime( dHS, 500);
  song.setScaleOnTime( dH, 250);
  song.setScaleOnTime( cHS, 250);
  song.setScaleOnTime( cH, 125);
 
  song.setScaleOnTime( b, 125);
  song.setScaleOnTime( cH, 250);    // 60
 
  song.setScaleOnTime(mute, 250);
 
  song.setScaleOnTime( f, 250);
  song.setScaleOnTime( gS, 500);
  song.setScaleOnTime( f, 375);
  song.setScaleOnTime( cH, 125);
  song.setScaleOnTime( a, 500);
 
  song.setScaleOnTime( f, 375);
  song.setScaleOnTime( c, 125);
  song.setScaleOnTime( a, 1000);
}