/**
 * @file Log.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Service.hpp"

namespace Ocean {

    /** @brief Additional callback for printing. */
    typedef void (*PrintCallback)(const char*);

    /**
     * @brief The Logging Service of Ocean, prints to a console.
     */
    class LogService : public StaticService<LogService> {
    public:
        LogService();
        virtual ~LogService();

        AssignServiceName(LogService);
        AssignServicePriority(ServicePriority::INITIAL);

        static LogService* Instance();

        /**
         * @brief Print's a given format to the console.
         * 
         * @param format The string format to print.
         * @param ... Arguments to pass into the format.
         */
        void PrintFormat(cstring format, ...) const;

        /**
         * @brief Set the PrintCallback for the Log Service.
         * 
         * @param callback The PrintCallback to use.
         */
        void SetCallback(PrintCallback callback);

    private:
        inline static LogService* s_Instance = nullptr;

        PrintCallback m_PrintCallback = nullptr;

    };    // LogService

}    // Ocean
