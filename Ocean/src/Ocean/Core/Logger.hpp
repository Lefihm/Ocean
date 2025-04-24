/**
 * @file Logger.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Core/Service/LogService.hpp"

namespace Ocean {

    /** @brief Print's the given string and arguments to the console. */
    #define oprint(format, ...)    Ocean::LogService::Instance()->PrintFormat(format, ## __VA_ARGS__)

    /** @brief Print's the given string and arguments to the console. Add's a new line after the output. */
    #define oprintret(format, ...) Ocean::LogService::Instance()->PrintFormat(format, ## __VA_ARGS__); Ocean::LogService::Instance()->PrintFormat("\n")

}   // Ocean
