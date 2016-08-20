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

/* Namespace */
namespace atlas
{
    typedef void     (*clbk_t)(uint32_t);
    typedef uint32_t   key_t;

    /* Structures */
    typedef struct
    {
        clbk_t callback;
        key_t  key;
    } sig_t;

    /* Public functions */
    namespace signal
    {
        void handler(int sig);
    };
};

#endif /* ATLAS_SIGNAL_H */
