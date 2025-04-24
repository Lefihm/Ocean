/**
 * @file Assert.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Core/Macros.hpp"
#include "Ocean/Core/Logger.hpp"

/** @brief Assert given that the condition is NOT true. */
#define OASSERT(condition) if (!(condition)) { oprintret(OCEAN_FUNCTIONLINE("FALSE")); OCEAN_DEBUG_BREAK; }

/** @brief Asserts when the index is outside the length from 0. */
#define OASSERT_LENGTH(i, max) OASSERT((i) < (max))

/** @brief Assert given that the condition is NOT true. Also can be given a message like oprint. */
#define OASSERTM(condition, message, ...) if (!(condition)) { oprintret(OCEAN_FUNCTIONLINE(message), ## __VA_ARGS__); OCEAN_DEBUG_BREAK; }
