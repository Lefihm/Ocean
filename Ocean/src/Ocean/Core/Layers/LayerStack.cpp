#include "LayerStack.hpp"

// std
#include <algorithm>

namespace Ocean {

        LayerStack::~LayerStack() {
            for (Layer* layer : this->m_Layers) {
                delete layer;
            }
        }

        void LayerStack::AttachLayers() {
            for (Layer* layer : this->m_Layers) {
                layer->OnAttach();
            }
        }

        void LayerStack::DetachLayers() {
            for (Layer* layer : this->m_Layers) {
                layer->OnDetach();
            }
        }

        void LayerStack::PushLayer(Layer* layer) {
            this->m_Layers.Emplace(this->m_InsertIndex, layer);

            this->m_InsertIndex++;
        }

        void LayerStack::PushOverlay(Layer* overlay) {
            this->m_Layers.EmplaceBack(overlay);
        }

        void LayerStack::PopLayer(Layer* layer) {
            const auto it = std::find(this->m_Layers.Begin(), this->m_Layers.Begin() + this->m_InsertIndex, layer);

            if (it != this->m_Layers.End()) {
                layer->OnDetach();
                
                this->m_Layers.Erase(it);
                this->m_InsertIndex--;
            }
        }

        void LayerStack::PopOverlay(Layer* overlay) {
            const auto it = std::find(this->m_Layers.Begin() + this->m_InsertIndex, this->m_Layers.End(), overlay);

            if (it != this->m_Layers.End()) {
                overlay->OnDetach();

                this->m_Layers.Erase(it);
            }
        }

}   // Ocean
