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

#ifdef __cplusplus
struct AtlasSignal {
#endif
    enum SignalType {
        SCREEN    = 0xa0,
        BRIGHT_UP = 0xb0,
        BRIGHT_DOWN,
        TRACK_PLAY,
        TRACK_NEXT,
        TRACK_PREV,
        VOL_UP,
        VOL_DOWN,
        VOL_MUTE
    };
#ifdef __cplusplus
};
#endif

#endif /* ATLAS_SIGNAL_TYPE_H */
