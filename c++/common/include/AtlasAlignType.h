/* *****************************************************************************
 * 
 * Name:      AtlasAlignType.h
 * Namespace: <AtlasAlign>
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Syntax: #include "AtlasAlignType.h"
 * 
 * Description: Atlas Status Bar alignment types for both vertical and
 *              horizontal orientations.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_ALIGN_TYPE_H
#define ATLAS_ALIGN_TYPE_H

struct AtlasAlign {
    enum AlignType {
        TOP  = 1,
        LEFT = TOP,
        CENTER,
        BOTTOM,
        RIGHT = BOTTOM
    };
};

#endif /* ATLAS_ALIGN_TYPE_H */
