#pragma once

#include "Ocean/Primitives/DynamicArray.hpp"

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

        virtual void Init() override;
        virtual void Shutdown() override;

        /**
         * @brief Sends an Event from an internal source.
         * 
         * @param e The Event to signal.
         */
        void SignalEvent(Event& e);

        /**
         * @brief Adds an EventCallback to dispatch to.
         * 
         * @note The callback must conform to EventCallback.
         * 
         * @param level The EventLevel to assign to the callback.
         * @param callback The function to dispatch to.
         */
        void AddEventCallback(EventLevel level, EventCallback_T callback);

        /**
         * @brief Dispatches events to callbacks.
         */
        void DispatchEvents();

    private:
        /** @brief A list of System level callbacks. */
        DynamicArray<EventCallback_T> m_SystemCallbacks;
        /** @brief A list of Application level callbacks. */
        DynamicArray<EventCallback_T> m_ApplicationCallbacks;
        /** @brief A list of User level callbacks. */
        DynamicArray<EventCallback_T> m_UserCallbacks;

    };  // EventProcessor

}   // Ocean
