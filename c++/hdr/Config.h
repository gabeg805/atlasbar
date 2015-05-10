// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef STATUSCONFIG_H
#define STATUSCONFIG_H


// ========
// Includes
// ========

#include <string>
#include <vector>


// ==========
// Namespaces
// ==========

namespace Config {
    std::string                 fetch(std::string key);
    std::string                 fetch(std::string file, std::string key);
    std::vector<std::string>    parse(std::string str, char delim);
    
    extern const std::string FILE;
};

#endif
