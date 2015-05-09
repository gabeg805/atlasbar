// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     Config.cc
// 
// 
// SYNTAX: 
// 
//     #include "Config.h"
// 
// 
// PURPOSE:
// 
//     Provides the necessary functionality to parse the config file.
// 
// 
// MODIFICATION HISTORY:
// 
//     gabeg May 09 2015 <> Created.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/Config.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>



// ////////////////////////////////
// ///// NAMESPACE DEFINITION /////
// ////////////////////////////////

// Read the config file
std::string Config::read(std::string file, std::string key) {
    
    // Define file/line parameters
    std::ifstream is(file.c_str(), std::ifstream::in);
    std::string delimiter = ":";
    std::string line;
    
    // Loop through file line by line
    while ( std::getline(is, line) ) {
        
        // Parse line for correct key
        size_t loc            = line.find(delimiter);
        std::string setting   = line.substr(0, loc);
        
        if ( setting.compare(key) != 0 )
            continue;
        
        // Retrieve remainder of line (excluding the key and leading space)
        size_t len            = line.length();
        std::string remainder = line.substr(loc+1, len);
        size_t startpos       = remainder.find_first_not_of(" \t");
        remainder             = remainder.substr(startpos, len);
        
        return remainder;
    }
    
    return "";
}



// Read the config file
std::vector<std::string> Config::parse(std::string str, char delim) {
    
    // Define string/vector parameters
    std::stringstream ss(str);
    std::vector<std::string> vec;
    std::string item;
    
    // Loop through string by delimeter
    while ( std::getline(ss, item, delim) ) {
        vec.push_back(item);
    }
    
    return vec;
}
