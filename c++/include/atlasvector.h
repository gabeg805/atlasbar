/* *****************************************************************************
 * 
 * Name:      atlasvector.h
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: The Atlas vector container type.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_VECTOR_H
#define ATLAS_VECTOR_H

/* Includes */
#include "atlasapp.h"
#include <vector>

/* Typedefs */
typedef std::vector<AtlasApp>   AtlasVector;
typedef AtlasVector::iterator   AtlasVectorIterator;

/* Namespace */
namespace atlas
{
    typedef AtlasVector         vec_t;
    typedef AtlasVectorIterator vecit_t;
};

#endif /* ATLAS_VECTOR_H */
