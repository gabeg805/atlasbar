/* *****************************************************************************
 * 
 * Name:    atlasalign.h
 * Type:    <AtlasAlign>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Alignment types.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_ALIGN_H
#define ATLAS_ALIGN_H

/* Structure */
struct AtlasAlign {
    enum Align {
        NONE = 0,
        TOP  = 1,
        LEFT = TOP,
        CENTER,
        BOTTOM,
        RIGHT = BOTTOM
    };
};
 
/* Namespace extension */
namespace atlas
{
    typedef AtlasAlign::Align align;
    typedef align             align_t;
};

#endif /* ATLAS_ALIGN_H */
