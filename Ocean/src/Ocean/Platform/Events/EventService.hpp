/**
 * @file EventService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/SmartPtrs.hpp"

#include "Ocean/Core/Service.hpp"

#include "Ocean/Primitives/DynamicArray.hpp"
#include "Ocean/Primitives/HashMap.hpp"

#include "Ocean/Platform/Events/Event.hpp"

// std
#include <functional>
#include <queue>

namespace Ocean {

    /**
     * @brief A Service to handle Events.
     */
    class EventService : public RuntimeService<EventService> {
    public:
        using EventCallback_T = std::function<void(Event&)>;

    public:
        EventService();
        virtual ~EventService();

        AssignServiceName(EventService);
        AssignServicePriority(ServicePriority::IMMEDIATE);

        /**
         * @brief 
         */
        virtual void Init() override;
        /**
         * @brief 
         */
        virtual void Shutdown() override;

        /**
         * @brief Sends an Event to the dispatcher.
         * 
         * @param e The Event to signal.
         */
        static void SignalEvent(Scope<Event> e);

        /**
         * @brief Adds an EventCallback to dispatch to.
         * 
         * @note The callback must conform to EventCallback.
         * 
         * @param category The EventCategory to assign to the callback.
         * @param callback The function to dispatch to.
         */
        template <EventCategory category>
        static void AddEventCallback(EventCallback_T callback) {
            s_Instance->m_Callbacks[category].EmplaceBack(std::move(callback));
        }

        #define OC_BIND_EVENT_FN(fn) [this](auto&& ... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

        /**
         * @brief Dispatches events to callbacks.
         */
        static void DispatchEvents();

    private:
        b8 DispatchEvent(Event& e, EventCategory category);

    private:
        inline static EventService* s_Instance = nullptr;

        /** @todo An event queue may be usefull to collect events in a frame until they are dispatched,
         *        rather than immediately dispatching events when recieved.
         *        This may help provide the ability to do input sanitization / duplicate event detection.
         */
        std::queue<Scope<Event>> m_Events;

        /**
         * @todo Make a more dynamic storage system that is based on the EventLevel enum.
         *       Some form of a buck list most likely, a sorted array would work but may be cumbersome.
         */
        UnorderedMap<EventCategory, DynamicArray<EventCallback_T>> m_Callbacks;

    };  // EventProcessor

}   // Ocean
