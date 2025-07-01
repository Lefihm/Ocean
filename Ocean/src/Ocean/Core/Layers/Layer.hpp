/**
 * @file Layer.hpp
 * @brief A base class for all layers in the application.
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Bool.hpp"
#include "Ocean/Types/Strings.hpp"
#include "Ocean/Types/Timestep.hpp"

#include "Ocean/Core/Macros.hpp"

#include "Ocean/Platform/Events/Event.hpp"

namespace Ocean {

    /**
     * @brief A layer to be rendered in the Application.
     */
    class Layer {
    public:
        /**
         * @brief Constructs a new Layer.
         * 
         * @param name The name of the layer, only used when OC_DEBUG is enabled.
         */
        Layer(const String& name = "Layer");
        virtual ~Layer() = default;

        /** @brief Occurs when the layer is attached to a LayerStack. */
        inline virtual void OnAttach() { }
        /** @brief Occurs when the layer is dettached from a LayerStack. */
        inline virtual void OnDetach() { }

        /**
         * @brief Occurs when the layer is updated by the Application.
         * 
         * @param ts The time since the last update.
         */
        inline virtual void OnUpdate(OC_UNUSED Timestep ts) { }

        /**
         * @brief Occurs when there is an event submitted to the layer.
         * 
         * @param e The event that was submitted.
         */
        virtual void OnEvent(OC_UNUSED Event& e) { }

        /**
         * @brief Returns true if the layer is enabled, false otherwise.
         * 
         * @return b8 
         */
        inline b8 IsEnabled() const { return this->m_Enabled; }
        /**
         * @brief Sets m_Enabled to the given value.
         * 
         * @param enabled True to enable the layer, false to disable the layer.
         */
        inline void SetEnabled(b8 enabled) { this->m_Enabled = enabled; }

    #ifdef OC_DEBUG

        /**
         * @brief Gets m_DebugName from the layer. DEBUG ONLY
         * 
         * @return const string&
         */
        inline const String& GetName() const { return this->m_DebugName; }

    #endif

    protected:
        /** @brief Records if the layer is enabled, if not then updates are blocked. */
        b8 m_Enabled;

    #ifdef OC_DEBUG

        /** @brief A name for use in debug builds / engine debugging. */
        String m_DebugName;

    #endif

    };  // Layer

}   // Ocean
