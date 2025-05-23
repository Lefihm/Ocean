#pragma once

/**
 * @file Texture.hpp
 * @author Evan F.
 * @brief The abstract Texture for Ocean.
 * @date 01-14-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/SmartPtrs.hpp"

#include "Ocean/Primitives/Macros.hpp"

namespace Ocean {

    namespace Splash {

        /**
         * @brief An enum of formats that can be used for a Texture.
         */
        enum TextureFormat {
            /** @brief Red bit format. */
            R    = 0,
            /** @brief Green bit format. */
            G    = 1,
            /** @brief Blue bit format. */
            B    = 2,
            /** @brief Red, Green, Blue format. */
            RGB  = 3,
            /** @brief Red, Green, Blue, Alpha format. */
            RGBA = 4,
            /** @brief Alpha bit format. */
            A    = 5,

        };  // TextureFormat



        /**
         * @brief The Texture is the base abstract class for textures that use the renderer API.
         */
        class Texture {
        public:
            /**
             * @brief Constructs a new Texture object.
             * 
             * @param width The width of the texture.
             * @param height The height of the texture.
             */
            OC_INLINE Texture(u32 width, u32 height) : m_Width(width), m_Height(height) { }
            virtual ~Texture() = default;

            /**
             * @brief Bind's the Texture to be used by commmands.
             * 
             * @param slot The slot to bind the Texture to. (OPTIONAL)
             */
            virtual void Bind(u32 slot = 0) const = 0;

            /**
             * @brief Set the data of the texture.
             * 
             * @param data The data to copy.
             * @param size The size of the data array.
             */
            virtual void SetData(void* data, u32 size) = 0;
            /**
             * @brief Set the Format object
             * 
             * @param format 
             */
            virtual void SetFormat(TextureFormat format) = 0;

            /**
             * @brief Gets the width of the texture.
             * 
             * @return u32 
             */
            OC_INLINE u32 GetWidth() const { return this->m_Width; }
            /**
             * @brief Gets the height of the texture.
             * 
             * @return u32 
             */
            OC_INLINE u32 GetHeight() const { return this->m_Height; }

            /**
             * @brief Get the ID of the texture.
             * 
             * @return u32 
             */
            virtual u32 GetRendererID() const = 0;

            /** @brief Texture is equal operator. */
            virtual bool operator == (const Texture& other) const = 0;

        protected:
            /** @brief The width of the texture. */
            u32 m_Width;
            /** @brief The height of the texture. */
            u32 m_Height;

        };  // Texture



        /**
         * @brief The Texture2D controls a 2D texture through the renderer API.
         */
        class Texture2D : public Texture {
        public:
            /** @copydoc Texture::Texture(u32, u32) */
            OC_INLINE Texture2D(u32 width, u32 height) : Texture(width, height) { }
            virtual ~Texture2D() = default;

            /**
             * @brief Create's a Texture2D with the given width and height.
             * 
             * @param width The width of the texture.
             * @param height The height of the texture.
             * @return Ref<Texture2D> 
             */
            OC_STATIC Ref<Texture2D> Create(u32 width, u32 height);

        };  // Texture2D

    }   // Splash

}   // Ocean
