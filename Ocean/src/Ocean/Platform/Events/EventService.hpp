/**
 * @file EventService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Core/Service.hpp"

#include "Ocean/Platform/Events/Event.hpp"

// std
#include <functional>

namespace Ocean {

    /**
     * @brief A Service to handle Events.
     */
    class EventService : public RuntimeService<EventService> {
    private:
        using EventCallback_T = std::function<void(Event&)>;

    public:
        typedef void (*EventCallback)(Event&);

    public:
        EventService();
        virtual ~EventService();

        AssignServiceName(EventService);
        AssignServicePriority(ServicePriority::DONT_CARE);

        /**
         * @brief 
         */
        virtual void Init() override;
        /**
         * @brief 
         */
        virtual void Shutdown() override;

        static EventService* Instance();

        /**
         * @brief Sends an Event to the dispatcher.
         * 
         * @param e The Event to signal.
         */
        void SignalEvent(Event& e);

        #define SendEvent(event)   EventService::Instance()->SignalEvent(event)

        /**
         * @brief Adds an EventCallback to dispatch to.
         * 
         * @note The callback must conform to EventCallback.
         * 
         * @param category The EventCategory to assign to the callback.
         * @param callback The function to dispatch to.
         */
        void AddEventCallback(EventCategory category, const EventCallback_T& callback);

        /**
         * @brief Dispatches events to callbacks.
         */
        void DispatchEvents();

    private:
        inline static EventService* s_Instance = nullptr;

        /** @todo An event queue may be usefull to collect events in a frame until they are dispatched,
         *        rather than immediately dispatching events when recieved.
         *        This may help provide the ability to do input sanitization / duplicate event detection.
         */

        /**
         * @todo Make a more dynamic storage system that is based on the EventLevel enum.
         *       Some form of a buck list most likely, a sorted array would work but may be cumbersome.
         */

    };  // EventProcessor

}   // Ocean
