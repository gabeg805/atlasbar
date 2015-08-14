/* *****************************************************************************
 * 
 * Name:      AtlasSignalType.h
 * Namespace: <AtlasSignal>
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Syntax: #include "AtlasSignalType.h"
 * 
 * Description: Atlas Status Bar signal types.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_SIGNAL_TYPE_H
#define ATLAS_SIGNAL_TYPE_H

struct AtlasSignal {
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
};

#endif /* ATLAS_SIGNAL_TYPE_H */
