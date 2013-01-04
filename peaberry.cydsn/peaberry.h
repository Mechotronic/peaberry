// Copyright 2012 David Turnbull AE9RB
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PEABERRY_H
#define PEABERRY_H

#include <device.h>

// Status register bits
#define KEY_0  0x01
#define KEY_1  0x02
#define B96_EN 0x04

// 48 24-bit stereo samples every 1 ms
#define I2S_B48_SIZE (48u * 3 * 2)
#define I2S_B96_SIZE (96u * 2 * 2)
// 48 12-bit mono samples every 1 ms
#define MIC_BUF_SIZE (48u * 2)
// buffer storage
#define USB_AUDIO_BUFS 3

// Constants from our USBFS enumeration
#define RX_ENDPOINT              2
#define RX_INTERFACE             2
#define TX_ENDPOINT              3
#define TX_INTERFACE             3
#define MIC_ENDPOINT             4
#define MIC_INTERFACE            5
#define SPKR_ENDPOINT            5
#define SPKR_INTERFACE           6

// Unvisible stuff from Cypress that they expect us to use and don't export
uint8 USBFS_InitControlRead(void);
uint8 USBFS_InitControlWrite(void);
extern volatile uint8 USBFS_currentSampleFrequency[USBFS_MAX_EP][USBFS_SAMPLE_FREQ_LEN];
extern volatile T_USBFS_TD USBFS_currentTD;
extern uint8 USBFS_initVar;
extern uint8 USBFS_DmaTd[USBFS_MAX_EP];
extern uint8 USBFS_currentVolume[];
extern uint8 USBFS_minimumVolume[];
extern uint8 USBFS_maximumVolume[];
extern uint8 USBFS_currentMute;

// main.c
extern uint8 TX_Request, Locked_I2C;
extern uint16 I2S_Buf_Size;
uint32 swap32(uint32) CYREENTRANT;
extern uint8 B96_Enabled;

// audio.c
extern uint8 Audio_IQ_Channels;
void Audio_Start(void);
void Audio_Main(void);
void Audio_Set_Speaker(void);
void Audio_USB_Start(void);
uint8 Audio_Volume(void);

// si570.c
#define SI570_STARTUP_FREQ 56.32
extern volatile uint32 Si570_Xtal, Si570_LO;
extern uint8 Si570_Buf[], Si570_Factory[], Si570_OLD[];
void Si570_Start(void);
void Si570_Main(void);
void Si570_Fake_Reset(void);

// pcm3060.c
void PCM3060_Setup(void);
void PCM3060_Init(void);
void PCM3060_Start(void);
void PCM3060_Main(void);
uint8* PCM3060_TxBuf(void);
uint8* PCM3060_RxBuf(void);

// mic.c
void Mic_Setup(void);
void Mic_Init(void);
void Mic_Start(void);
uint8* Mic_Buf(void);

// settings.c
void Settings_Start(void);
void Settings_Main(void);


#endif //PEABERRY_H
