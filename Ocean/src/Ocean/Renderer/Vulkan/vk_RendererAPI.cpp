#include "vk_RendererAPI.hpp"

#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/SmartPtrs.hpp"

#include "Ocean/Renderer/RendererAPI.hpp"
#include "Ocean/Renderer/VertexArray.hpp"

#include "Ocean/Renderer/Vulkan/vk_Instance.hpp"

// std
#include <cstring>

// libs
#include <glad/vulkan.h>

namespace Ocean {

    namespace Splash {

        vkRendererAPI::vkRendererAPI() : RendererAPI() {
            vkInstance::Get();
        }

        vkRendererAPI::~vkRendererAPI() {
            
        }

        void vkRendererAPI::Init() {
            vkInstance::Get().Prepare();
        }

        void vkRendererAPI::Shutdown() {
            vkInstance::Get().Cleanup();
        }

        void vkRendererAPI::SetViewport(u32 x, u32 y, u32 w, u32 h) {
            
        }

        void vkRendererAPI::SetClearColor(const glm::vec4& color) {

        }

        void vkRendererAPI::Clear() {

        }

        void vkRendererAPI::DrawIndexed(const Ref<VertexArray>& array, u32 indexCount) {
            // u32 count = indexCount ? indexCount : array->GetIndexBuffer()->GetCount();

        }

    }   // Splash

}   // Ocean
