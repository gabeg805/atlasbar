/* *****************************************************************************
 * 
 * Name:    AtlasUserAppBuilder.cc
 * Class:   <AtlasUserAppBuilder>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas User Application builder.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasUserAppBuilder.h"
#include "AtlasUserApp.h"
#include <stdint.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <string>

/* Globals */
AtlasUserApp *AtlasUserAppBuilder::container;
uint8_t       AtlasUserAppBuilder::index;

/* ************************************************************************** */
/* Constructor */
AtlasUserAppBuilder::AtlasUserAppBuilder(uint8_t size)
{
    this->container = (AtlasUserApp*) calloc(size+1, sizeof(AtlasUserApp));
    this->index     = 0;
}

/* ************************************************************************** */
/* Create a new user app */
int AtlasUserAppBuilder::new_app(std::string name, AtlasFunc func)
{
    this->container[this->index].name = name;
    this->container[this->index].func = func;
    this->index++;
    return 0;
}

/* ************************************************************************** */
/* Remove a user app */
int AtlasUserAppBuilder::remove_app(std::string name)
{
    bool    found = false;
    uint8_t i;
    for ( i=0; i < this->index; ++i ) {
        if ( found ) {
            this->container[i-1] = this->container[i];
            this->clear_app(i);
        }
        if ( (this->container[i].name).compare(name) == 0 ) {
            this->clear_app(i);
            found = true;
        }
    }
    return (found ? 0 : -1);
}

/* ************************************************************************** */
/* Remove a user app */
int AtlasUserAppBuilder::remove_app(uint8_t i)
{
    if ( i >= this->index )
        return -1;

    uint8_t j;
    for ( j=i+1; j < this->index; ++j ) {
        this->container[j-1] = this->container[j];
        this->clear_app(j);
    }
    return 0;
}

/* ************************************************************************** */
/* Clear app */
int AtlasUserAppBuilder::clear_app(AtlasUserApp *app)
{
    memset(app, 0, sizeof(*app));
    return 0;
}

/* ************************************************************************** */
/* Clear app */
int AtlasUserAppBuilder::clear_app(uint8_t i)
{
    memset(&this->container[i], 0, sizeof(this->container[i]));
    return 0;
}

/* ************************************************************************** */
/* Return app container */
AtlasUserApp * AtlasUserAppBuilder::get_apps(void)
{
    return this->container;
}

/* ************************************************************************** */
/* Print apps in container */
void AtlasUserAppBuilder::print_apps(void)
{
    uint8_t i;
    for ( i=0; i < this->index; ++i )
        std::cout << "name: " << this->container[i].name
                  << " | func: " << (void*)&this->container[i].func
                  << std::endl;
}
