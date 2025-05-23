#pragma once

/**
 * @file vk_Command.hpp
 * @author Evan F.
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Ocean/Types/Bool.hpp"
#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Primitives/Macros.hpp"
#include "Ocean/Primitives/HashMap.hpp"

// libs
#include <glad/vulkan.h>

namespace Ocean {

    namespace Splash {

        /**
         * @brief Wrapper class for a Vulkan Command Pool that stores corresponding vkCommandBuffer's.
         */
        class vkCommandPool {
        private:
            /**
            * @brief Wrapper class for a Vulkan Command Buffer.
            */
            class vkCommandBuffer {
            public:
                vkCommandBuffer();
                /**
                * @brief Constructs a new vkCommandBuffer object.
                * 
                * @param pool 
                * @param primary 
                */
                vkCommandBuffer(VkCommandPool pool, b8 primary);
                vkCommandBuffer(const vkCommandBuffer& other);
                ~vkCommandBuffer();

                b8 operator == (const vkCommandBuffer& other) const;
                b8 operator != (const vkCommandBuffer& other) const;

            private:
                const vkCommandBuffer& operator = (const vkCommandBuffer&) = delete;

            private:
                const VkCommandPool m_ParentPool; /** @brief The Vulkan command pool that this buffer is owned by. */

                VkCommandBuffer m_Buffer; /** @brief The Vulkan command buffer. */

            };  // vkCommandBuffer

        public:
            /**
             * @brief Constructs a new vkCommandPool object.
             * 
             * @param queueIndex The queue family index for the command pool.
             */
            vkCommandPool(u32 queueIndex);
            ~vkCommandPool();

            /**
             * @brief Create a vkCommandBuffer within the command pool.
             * 
             * @param name The name of the buffer. E.g. "primary3D".
             * @param primary Whether the command buffer is a primary buffer or not.
             */
            void CreateBuffer(cstring name, b8 primary);
            /**
             * @brief Destroy's a vkCommandBuffer within the command pool.
             * 
             * @param name The name of the buffer to destroy.
             */
            void DestroyBuffer(cstring name);

            /**
             * @brief Get's the Vulkan command pool.
             * 
             * @return VkCommandPool 
             */
            OC_INLINE VkCommandPool Pool() const { return this->m_Pool; }
            /**
             * @brief Get's the vkCommandBuffer from the command pool.
             * 
             * @param name The name of the command buffer to get.
             * @return const vkCommandBuffer&
             */
            OC_INLINE const vkCommandBuffer& Buffer(cstring name) { return this->m_Buffers[name]; }

        private:
            VkCommandPool m_Pool; /** @brief The Vulkan command pool. */

            u32 m_QueueIndex; /** @brief The queue family index that the command pool is assigned to. */

            UnorderedMap<cstring, vkCommandBuffer> m_Buffers; /** @brief The list of vkCommandBuffer's that are stored by name. */

        };  // vkCommandPool

    }   // Splash

}   // Ocean
