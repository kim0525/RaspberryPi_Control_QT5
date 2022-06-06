#ifndef PIEZO_H
#define PIEZO_H

#define S_mute 0

#define S_cL 129
#define S_cLS 139
#define S_dL 146
#define S_dLS 156
#define S_eL 163
#define S_fL 173
#define S_fLS 185
#define S_gL 194
#define S_gLS 207
#define S_aL 219
#define S_aLS 228
#define S_bL 232

#define S_c 261
#define S_cS 277
#define S_d 294
#define S_dS 311
#define S_e 329
#define S_f 349
#define S_fS 370
#define S_g 391
#define S_gS 415
#define S_a 440
#define S_aS 455
#define S_b 466

#define S_cH 523
#define S_cHS 554
#define S_dH 587
#define S_dHS 622
#define S_eH 659
#define S_fH 698
#define S_fHS 740
#define S_gH 784
#define S_gHS 830
#define S_aH 880
#define S_aHS 910
#define S_bH 933

#define _countof(_Array)    sizeof(_Array)/sizeof(_Array[0])

struct scaleTime{
    int *scale;
    int *time;
    int cnt;
};


#endif // PIEZO_H
