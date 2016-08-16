/* *****************************************************************************
 * 
 * Name:      atlassignal.h
 * Namespace: <atlas::signal>
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: The Atlas signal handler.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_SIGNAL_H
#define ATLAS_SIGNAL_H

/* Includes */
#include <stdint.h>

/* Typedefs */
typedef void                  (*AtlasCallback)(uint32_t);
typedef uint32_t                AtlasKey;

/* Structures */
struct AtlasSignal
{
    AtlasCallback callback;
    AtlasKey      key;
};

/* Namespace */
namespace atlas
{
    typedef AtlasSignal         sig_t;
    typedef AtlasCallback       clbk_t;
    typedef AtlasKey            key_t;

    namespace signal
    {
        void handler(int sig);
    };
};

#endif /* ATLAS_SIGNAL_H */
