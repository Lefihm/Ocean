#include "vk_Pipeline.hpp"

#include "Ocean/Primitives/Macros.hpp"
#include "Ocean/Types/FloatingPoints.hpp"

#include "Ocean/Primitives/FixedArray.hpp"

#include "Ocean/Renderer/Vulkan/vk_Vulkan.hpp"
#include "Ocean/Renderer/Vulkan/vk_Instance.hpp"

// libs
#include <glad/vulkan.h>

namespace Ocean {

    namespace Splash {

        vkPipeline::vkPipeline() :
            m_Pipeline(VK_NULL_HANDLE),
            m_Layout(VK_NULL_HANDLE),
            m_RenderPasses(0),
            m_Shader()
        {
            
        }

        vkPipeline::~vkPipeline() {
            
        }

        void vkPipeline::Invalidate() {
            // ============================== VIEWPORT ==============================
            //
            VkViewport viewport {
                0.0f,
                0.0f,
                static_cast<f32>(vkInstance::Get().Swapchain()->Extent().width),
                static_cast<f32>(vkInstance::Get().Swapchain()->Extent().height),
                0.0f,
                1.0f
            };

            // ============================== SCISSOR ==============================
            //
            VkRect2D scissor {
                {
                    0,
                    0
                },
                vkInstance::Get().Swapchain()->Extent()
            };

            // ============================== DYNAMIC STATES ==============================
            //
            FixedArray<VkDynamicState, 2> dynamicStates {
                VK_DYNAMIC_STATE_VIEWPORT,
                VK_DYNAMIC_STATE_SCISSOR,
            };
            VkPipelineDynamicStateCreateInfo dynamicState {
                VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
                nullptr,
                0,
                dynamicStates.Size(),
                dynamicStates.Data()
            };

            VkPipelineViewportStateCreateInfo viewportState {
                VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
                nullptr,
                0,
                1,
                &viewport,
                1,
                &scissor
            };

            // ============================== VERTEX INPUT ==============================
            //
            VkPipelineVertexInputStateCreateInfo vertexInputState {
                VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO,
                nullptr,
                0,
                0,
                nullptr,
                0,
                nullptr
            };

            VkPipelineInputAssemblyStateCreateInfo inputAssemblyState {
                VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                nullptr,
                0,
                VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                VK_FALSE
            };

            // ============================== RASTERIZATION ==============================
            //
            VkPipelineRasterizationStateCreateInfo rasterizationState {
                VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                nullptr,
                0,
                VK_FALSE,
                VK_FALSE,
                VK_POLYGON_MODE_FILL,
                VK_CULL_MODE_BACK_BIT,
                VK_FRONT_FACE_CLOCKWISE,
                VK_FALSE,
                0.0f,
                0.0f,
                0.0f,
                1.0f
            };

            // ============================== MULTISAMPLING ==============================
            //
            VkPipelineMultisampleStateCreateInfo multisamplingState {
                VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                nullptr,
                0,
                VK_SAMPLE_COUNT_1_BIT,
                VK_FALSE,
                1.0f,
                nullptr,
                VK_FALSE,
                VK_FALSE
            };

            // ============================== DEPTH TESTING ==============================
            //

            // ============================== STENCIL TESTING ==============================
            //

            // ============================== COLOR BLENDING ==============================
            //
            VkPipelineColorBlendAttachmentState colorBlendAttachment {
                VK_TRUE,
                VK_BLEND_FACTOR_SRC_ALPHA,
                VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
                VK_BLEND_OP_ADD,
                VK_BLEND_FACTOR_ONE,
                VK_BLEND_FACTOR_ZERO,
                VK_BLEND_OP_ADD,
                VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
            };

            VkPipelineColorBlendStateCreateInfo colorBlendState {
                VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
                nullptr,
                0,
                VK_FALSE,
                VK_LOGIC_OP_COPY,
                1,
                &colorBlendAttachment,
                {
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f
                }
            };

            // ============================== PIPELINE LAYOUT ==============================
            //
            VkPipelineLayoutCreateInfo pipelineLayoutInfo {
                VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                nullptr,
                0,
                0,
                nullptr,
                0,
                nullptr
            };

            vkCheck(
                vkCreatePipelineLayout(vkInstance::Get().Device()->Logical(), &pipelineLayoutInfo, nullptr, &this->m_Layout)
            );

            // ============================== SHADER MODULES ==============================
            //
            VkShaderModule vertShader = this->m_Shader->Vert();
            VkShaderModule fragShader = this->m_Shader->Frag();

            VkPipelineShaderStageCreateInfo vertShaderInfo {
                VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                nullptr,
                0,
                VK_SHADER_STAGE_VERTEX_BIT,
                vertShader,
                "main",
                nullptr
            };

            VkPipelineShaderStageCreateInfo fragShaderInfo {
                VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                nullptr,
                0,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                fragShader,
                "main",
                nullptr
            };

            VkPipelineShaderStageCreateInfo shaderStageInfos[] = {
                vertShaderInfo,
                fragShaderInfo,
            };

            // ============================== PIPELINE INFO ==============================
            //
            VkGraphicsPipelineCreateInfo pipelineInfo {
                VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                nullptr,
                0,
                ArraySize(shaderStageInfos),
                shaderStageInfos,
                &vertexInputState,
                &inputAssemblyState,
                nullptr,
                &viewportState,
                &rasterizationState,
                &multisamplingState,
                nullptr,
                &colorBlendState,
                &dynamicState,
                this->m_Layout,
                this->m_RenderPasses[0].RenderPass(),
                0,
                VK_NULL_HANDLE,
                0
            };

            vkCheck(
                vkCreateGraphicsPipelines(vkInstance::Get().Device()->Logical(), nullptr, 1, &pipelineInfo, nullptr, &this->m_Pipeline)
            );
        }

    } // namespace Splash

} // namespace Ocean
