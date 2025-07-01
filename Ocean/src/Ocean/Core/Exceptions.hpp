#pragma once

#include "Ocean/Types/Strings.hpp"

// std
#include <exception>

namespace Ocean{

    /**
     * @brief An enum of different error types that can occur.
     */
    typedef enum Error {
        /**
         * @brief General runtime error.
         * @details This error is thrown when a runtime error occurs that does not fit into any other category.
         *          It is typically used to indicate that something unexpected happened during the execution of the program.
         */
        RUNTIME_ERROR,
        /**
         * @brief General invalid argument error.
         * @details This error is thrown when an argument passed to a function is not valid.
         *          It is typically used to indicate that the function cannot proceed with the given argument.
         */
        INVALID_ARGUMENT,
        /**
         * @brief General domain error.
         * @details This error is thrown when a value is outside the valid domain.
         */
        DOMAIN_ERROR,
        /**
         * @brief General length error.
         * @details This error is thrown when a value is not of the expected length.
         */
        LENGTH_ERROR,
        /**
         * @brief General out of range error.
         * @details This error is thrown when a value is outside the expected range.
         */
        OUT_OF_RANGE,
        /**
         * @brief General future error.
         * @details This error is thrown when a future is not ready to be accessed.
         *          It is typically used in asynchronous programming contexts.
         */
        FUTURE_ERROR,
        /**
         * @brief General overflow error.
         * @details This error is thrown when a value exceeds the maximum limit.
         */
        OVERFLOW_ERROR,
        /**
         * @brief General underflow error.
         * @details This error is thrown when a value is below the minimum limit.
         */
        UNDERFLOW_ERROR,
        /**
         * @brief General regex error.
         * @details This error is thrown when a regular expression fails to match.
         */
        REGEX_ERROR,
        /**
         * @brief General system error.
         * @details This error is thrown when a system-level error occurs.
         */
        SYSTEM_ERROR,
        /**
         * @brief General input/output failure.
         * @details This error is thrown when an input/output operation fails.
         */
        IOS_FAILURE,
        /**
         * @brief General filesystem error.
         * @details This error is thrown when a filesystem operation fails.
         */
        FILESYSTEM_ERROR,
        /**
         * @brief General bad typeid error.
         * @details This error is thrown when typeid is nullptr of polymorphic type.
         */
        BAD_TYPEID,
        /**
         * @brief General bad expected access error.
         * @details This error is thrown when an expected value is not present.
         */
        BAD_EXPECTED_ACCESS,
        /**
         * @brief General bad weak pointer error.
         * @details This error is thrown when a weak pointer is accessed but the object it points to has been deleted.
         */
        BAD_WEAK_PTR,
        /**
         * @brief General bad function call error.
         * @details This error is thrown when a function is called in an invalid context or with invalid arguments.
         */
        BAD_FUNCTION_CALL,
        /**
         * @brief General bad alloc error.
         * @details This error is thrown when memory allocation fails.
         */
        BAD_ALLOC,
        /**
         * @brief General bad array new length error.
         * @details This error is thrown when a new array is created with an invalid length.
         */
        BAD_ARRAY_NEW_LENGTH,
        /**
         * @brief General bad exception error.
         * @details This error is thrown when an exception is thrown in a context where it is not allowed.
         */
        BAD_EXCEPTION,

        /**
         * @brief Occurs when a template is used incorrectly.
         * @details This error is thrown when a template is used in a way that is not allowed.
         */
        BAD_TEMPLATE,

        /**
         * @brief Occurs when code reaches a point that it wasn't supposed to reach.
         */
        YOU_SHOULD_NOT_BE_HERE,
        /**
         * @brief Occurs when an instance does not have a proper value.
         */
        BAD_INSTANCE,

        /**
         * @brief Occurs when the platform cannot be properly determined.
         */
        BAD_PLATFORM,
        /**
         * @brief Occurs when the window handle is not valid.
         */
        BAD_WINDOW_HANDLE,
        /**
         * @brief Occurs when a window fails to be created.
         */
        BAD_WINDOW_CREATION,

        /**
         * @brief Occurs when duplicate data is made when unique data is expected.
         */
        DUPLICATE_DATA,

    } Error;

    /**
     * @brief A exception class that describes an error when thrown.
     */
    class Exception : public std::exception {
    public:
        /**
         * @brief The information container of an Exception.
         */
        struct ExceptionInfo {
            /** @brief The type of @ref Error that the exception is. */
            const Error error;
            /** @brief The message that describes the error. */
            const cstring msg;

        };  // ExceptionInfo

    public:
        /**
         * @brief Construct a new Exception object.
         * 
         * @param message The error message of the exception.
         */
        explicit Exception(cstring message) noexcept : m_Info({ Ocean::Error::RUNTIME_ERROR, message }) { }
        /**
         * @brief Construct a new Exception object.
         * 
         * @param error The error type of the exception.
         * @param message The error message of the exception.
         */
        explicit Exception(const Ocean::Error error, cstring message) noexcept : m_Info({ error, message }) { }

        /**
         * @brief Gets the message of the error.
         * 
         * @return cstring 
         */
        virtual cstring what() const noexcept override { return this->m_Info.msg; }

        /**
         * @brief Gets the error type.
         * 
         * @return Error 
         */
        Ocean::Error error() const noexcept { return this->m_Info.error; }

    protected:
        /** @brief The information of the exception. */
        ExceptionInfo m_Info;

    };  // Exception

}   // Ocean
