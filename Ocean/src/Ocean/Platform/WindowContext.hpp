/**
 * @file Context.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Strings.hpp"
namespace Ocean {

    /**
     * @brief The window handler context.
     */
    class WindowContext {
    public:
        /**
         * @brief Ocean's window platform ID.
         */
        typedef enum PlatformID {
            /** @brief Default NULL value. */
            NONE = 0,
            /** @brief Win32 based windows. */
            WINDOWS,
            /** @brief X11 Linux window server. */
            LINUX_X11,
            /** @brief Wayland Linux window server. */
            LINUX_WAYLAND,
            /** @brief MacOS window server. */
            MACOS_COCOA,

        } PlatformID;

    public:
        /**
         * @brief Initializes the window handler. 
         */
        static void Init();
        /**
         * @brief Shut's down the window handler.
         */
        static void Shutdown();

        /**
         * @brief Get's a PlatformID from the window handler.
         * 
         * @return PlatformID
         */
        static PlatformID GetPlatformID();
        /**
         * @brief Get the platform name.
         * 
         * @return cstring 
         */
        static cstring GetPlatformName();

    };  // WindowContext

}   // Ocean
