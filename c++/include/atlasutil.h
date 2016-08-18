/* *****************************************************************************
 * 
 * Name:    atlasutil.h
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: Utility functions for Atlas.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_UTIL_H
#define ATLAS_UTIL_H

/* C++ to C guard */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stdint.h>
#include <sys/types.h>

/* Typedefs */
typedef enum { NONE, INFO, WARNING, ERROR, LOG, DEBUG } AtlasPrint_t;

/* Public functions */
uint32_t     logbase2(uint32_t val);
pid_t        pidof(const char *prog);
void         atlasprintf(AtlasPrint_t type, const char *fmt, ...);
const char * getlogfile(void);

#ifdef __cplusplus
}
#endif

#endif /* ATLASIO_H */
