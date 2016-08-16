/* *****************************************************************************
 * 
 * Name:    atlasutil.cc
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

/* Includes */
#include "atlasutil.h"
#include <dirent.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

/* Private functions */
static char * modetostr(AtlasPrint_t mode);
static char * strtimenow(const char *fmt);
static void infoprintf(const char *fmt, va_list ap);
static void warnprintf(const char *fmt, va_list ap);
static void errprintf(const char *fmt, va_list ap);
static void logprintf(const char *fmt, va_list ap);
static void debugprintf(const char *fmt, va_list ap);

/* ************************************************************************** */
/* Calculate log2(value) */
uint32_t logbase2(uint32_t val)
{
    uint32_t i;
    for ( i = 0; i < 31; ++i )
        if ( (val >>= 1) == 0 )
            return i;
    return i;
}

/* ************************************************************************** */
/* Return PID of a program */
uint16_t pidof(const char *prog)
{
    const char    *parent  = "/proc";
    DIR           *dstream = opendir(parent);
    FILE          *fstream;
    struct dirent *dir;
    struct stat    info;
    static char    path[256];
    static char    line[256];
    char          *ret;
    size_t         len;
    while ( (dir=readdir(dstream)) != NULL ) {
        if ( dir->d_type == DT_DIR ) {
            len = 5+1+strlen(dir->d_name)+8+1;
            if ( sizeof(path) < len )
                continue;
            snprintf(path, len, "%s/%s/cmdline", parent, dir->d_name);
            if ( stat(path, &info) != 0 )
                continue;
            if ( getuid() != info.st_uid )
                continue;
            fstream = fopen(path, "r");
            ret     = fgets(line, sizeof(line), fstream);
            fclose(fstream);
            if ( ret == NULL )
                continue;
            if ( strstr(line, prog) != NULL )
                return strtoul(dir->d_name, NULL, 10);
        }
    }

    return 0;
}

/* ************************************************************************** */
/* Print */
void atlasprintf(AtlasPrint_t mode, const char *fmt, ...)
{
    /* Format line label */
    static const char *timefmt = "%Y-%m-%d %X";
    static char label[256];
    static char linefmt[64];
    snprintf(label, sizeof(label), "[%s] %s:", strtimenow(timefmt),
             modetostr(mode));
    snprintf(linefmt, sizeof(linefmt), "%s %s\n", label, fmt);

    /* Call appropriate logging function */
    va_list arglist;
    va_start(arglist, fmt);
    if ( mode == INFO )
        infoprintf(linefmt, arglist);
    else if ( mode == WARNING )
        warnprintf(linefmt, arglist);
    else if ( mode == ERROR )
        errprintf(linefmt, arglist);
    else if ( mode == LOG )
        logprintf(linefmt, arglist);
    else if ( mode == DEBUG )
        debugprintf(linefmt, arglist);
    else if ( mode == NONE )
        infoprintf(linefmt, arglist);
    else
        ;
    va_end(arglist);
}

/* ************************************************************************** */
/* Convert print mode to string */
char * modetostr(AtlasPrint_t mode)
{
    static char str[10];
    if ( mode == INFO )
        strncpy(str, "INFO", 4);
    else if ( mode == WARNING )
        strncpy(str, "WARNING", 7);
    else if ( mode == ERROR )
        strncpy(str, "ERROR", 5);
    else if ( mode == DEBUG )
        strncpy(str, "DEBUG", 5);
    else if ( mode == LOG )
        strncpy(str, "LOG", 3);
    else
        str[0] = '\0';

    uint8_t len = strlen(str);
    if ( len >= 10 )
        len = 9;
    str[len] = '\0';
    return str;
}

/* ************************************************************************** */
/* Return current time string */
char * strtimenow(const char *fmt)
{
    time_t       now     = time(0);
    struct tm   *tstruct = localtime(&now);
    static char  buf[128];
    strftime(buf, sizeof(buf), fmt, tstruct);
    return buf;
}

/* ************************************************************************** */
/* Print informational messages to stdout */
void infoprintf(const char *fmt, va_list ap)
{
    vprintf(fmt, ap);
}

/* ************************************************************************** */
/* Print warning messages to stdout */
void warnprintf(const char *fmt, va_list ap)
{
    vprintf(fmt, ap);
}

/* ************************************************************************** */
/* Print error messages to stderr */
void errprintf(const char *fmt, va_list ap)
{
    vfprintf(stderr, fmt, ap);
}

/* ************************************************************************** */
/* Print messages for logging to log */
void logprintf(const char *fmt, va_list ap)
{
    static const char *file = "/tmp/atlas.log";
    FILE *stream = fopen(file, "a+");
    vfprintf(stream, fmt, ap);
    fclose(stream);
}

/* ************************************************************************** */
/* Print debug messages to stdout and to the log */
void debugprintf(const char *fmt, va_list ap)
{
    infoprintf(fmt, ap);
    logprintf(fmt, ap);
}
