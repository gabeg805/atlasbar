/* *****************************************************************************
 * 
 * Name:      AtlasSignalType.h
 * Namespace: <AtlasSignal>
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: The Atlas Status Bar signal types.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_SIGNAL_TYPE_H
#define ATLAS_SIGNAL_TYPE_H

/* #ifdef __cplusplus */
/* struct atlassignal { */
/* #endif */
/*     enum SignalType { */

#define ATLAS_SIG_NONE 0x0

#define ATLAS_SIG_MON  0xa0 /* Monitor */
#define ATLAS_SIG_BRT  0xb0 /* Brightness */
#define ATLAS_SIG_VOL  0xc0 /* Volume */

#define ATLAS_SIG_BRT_UP   0xb1 
#define ATLAS_SIG_BRT_DOWN 0xb2

#define ATLAS_SIG_VOL_PLAY 0xc1
#define ATLAS_SIG_VOL_NEXT 0xc2
#define ATLAS_SIG_VOL_PREV 0xc3
#define ATLAS_SIG_VOL_UP   0xc4
#define ATLAS_SIG_VOL_DOWN 0xc5
#define ATLAS_SIG_VOL_MUTE 0xc6

#define ATLAS_SIG_MASK     0xf0
#define ATLAS_SIG_DONE     0xff


#define ATLAS_KEY_BRT_UP      0x1008ff02
#define ATLAS_KEY_BRT_DOWN    0x1008ff03
#define ATLAS_KEY_VOL_DOWN    0x1008ff11
#define ATLAS_KEY_VOL_MUTE    0x1008ff12
#define ATLAS_KEY_VOL_UP      0x1008ff13
#define ATLAS_KEY_VOL_PLAY    0x1008ff14
#define ATLAS_KEY_VOL_NEXT    0x1008ff16
#define ATLAS_KEY_VOL_PREV    0x1008ff17

/*     }; */
/* #ifdef __cplusplus */
/* }; */
/* #endif */

#endif /* ATLAS_SIGNAL_TYPE_H */
