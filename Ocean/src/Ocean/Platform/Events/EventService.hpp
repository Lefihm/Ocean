/**
 * @file EventService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/SmartPtrs.hpp"

#include "Ocean/Core/Service.hpp"

#include "Ocean/Primitives/FixedArray.hpp"
#include "Ocean/Primitives/DynamicArray.hpp"

#include "Ocean/Platform/Events/Event.hpp"

// std
#include <functional>
#include <queue>

namespace Ocean {

    /** @brief A Service to handle Events. */
    class EventService : public RuntimeService<EventService> {
    public:
        /** @brief Type definition for an Event callback function. */
        using EventCallback_T = std::function<void(Event&)>;

    public:
        EventService();
        virtual ~EventService();

        AssignServiceName(EventService);
        AssignServicePriority(ServicePriority::IMMEDIATE);

        /** @brief Initializes the EventService. */
        virtual void Init() override;
        /** @brief Shuts down the EventService. */
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
         * @tparam category The EventCategory to assign to the callback.
         * 
         * @param callback The function to dispatch to.
         */
        template <EventCategory category>
        static void AddEventCallback(EventCallback_T callback) {
            s_Instance->m_Callbacks[static_cast<u16>(category)].EmplaceBack(std::move(callback));
        }
        /**
         * @brief Removes an EventCallback from dispatching.
         * 
         * @tparam category The EventCategory to remove the callback from.
         * 
         * @param callback The function to remove from dispatching.
         */
        template <EventCategory category>
        static void RemoveEventCallback(EventCallback_T callback) {
            auto& callbacks = s_Instance->m_Callbacks[static_cast<u16>(category)];

            if (callbacks.Empty())
                throw Exception(Error::BAD_EXPECTED_ACCESS, "No callbacks registered for the given EventCategory!");

            for (auto it = callbacks.begin(); it != callbacks.end(); ++it) {
                if (*it && callback) {
                    // Compare the targets of the std::function
                    if ((*it).target_type() == callback.target_type()) {
                        // For function pointers
                        if (auto lhs = (*it).template target<void(*)(Event&)>()) {
                            auto rhs = callback.template target<void(*)(Event&)>();

                            if (lhs && rhs && *lhs == *rhs) {
                                callbacks.Erase(it);

                                return;
                            }
                        }
                    }
                }
            }
        }

        /** @brief Binds an event function to a portable lambda. */
        #define OC_BIND_EVENT_FN(fn) [this](auto&& ... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

        /** @brief Dispatches events to callbacks. */
        static void DispatchEvents();

    private:
        /** @brief Dispatches an event to the appropriate callback categories. */
        b8 DispatchEvent(Event& e, EventCategory category);

    private:
        /** @brief Pointer to the singleton instance of the EventService. */
        inline static EventService* s_Instance = nullptr;

        /** @brief Queue of events to be processed. */
        std::queue<Scope<Event>> m_Events;

        /**
         * @todo Make a more dynamic storage system that is based on the EventLevel enum.
         *       Some form of a bucket list most likely, a sorted array would work but may be cumbersome.
         */
        FixedArray<DynamicArray<EventCallback_T>, static_cast<u16>(EventCategory::EVENT_CATEGORY_MAX)> m_Callbacks;

    };  // EventProcessor

}   // Ocean
