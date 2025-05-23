#include "gl_Shader.hpp"

#include "Ocean/Primitives/Assert.hpp"

// libs
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace Ocean {

    namespace Splash {
    
        glShader::glShader(const cstring vertexSource, const cstring fragmentSource, const cstring geometrySource) :
            m_RendererID()
        {
            u32 vertex, fragment, geometry;

            // Vertex Shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vertexSource, NULL);
            glCompileShader(vertex);

            CheckCompileErrors(vertex, SHADER);

            // Fragment Shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);

            glShaderSource(fragment, 1, &fragmentSource, NULL);
            glCompileShader(fragment);

            CheckCompileErrors(fragment, SHADER);

            // Geometry Shader If Given
            if (geometrySource) {
                geometry = glCreateShader(GL_GEOMETRY_SHADER);

                glShaderSource(geometry, 1, &geometrySource, NULL);
                glCompileShader(geometry);

                CheckCompileErrors(geometry, SHADER);
            }

            // Create The Shader Program
            this->m_RendererID = glCreateProgram();

            glAttachShader(this->m_RendererID, vertex);
            glAttachShader(this->m_RendererID, fragment);
            if (geometrySource)
                glAttachShader(this->m_RendererID, geometry);

            glLinkProgram(this->m_RendererID);

            CheckCompileErrors(this->m_RendererID, PROGRAM);
            
            // Clean Up Unecessary Data
            glDeleteShader(vertex);
            glDeleteShader(fragment);

            if (geometrySource)
                glDeleteShader(geometry);
        }

        glShader::~glShader() {

        }

        void glShader::Bind() const {
            glUseProgram(this->m_RendererID);
        }
        
        void glShader::Unbind() const {
            glUseProgram(0);
        }

        void glShader::SetInt(cstring name, i32 value) const {
            GLint location = glGetUniformLocation(this->m_RendererID, name);

            glUniform1i(location, value);
        }
        
        void glShader::SetIntArray(cstring name, i32* array, u32 length) const {
            GLint location = glGetUniformLocation(this->m_RendererID, name);
            
            glUniform1iv(location, length, array);
        }

        void glShader::SetFloat(cstring name, f32 value) const {
            GLint location = glGetUniformLocation(this->m_RendererID, name);

            glUniform1f(location, value);
        }
        
        void glShader::SetVec2f(cstring name, const glm::vec2& value) const {
            GLint location = glGetUniformLocation(this->m_RendererID, name);

            glUniform2f(location, value.x, value.y);
        }
        
        void glShader::SetVec3f(cstring name, const glm::vec3& value) const {
            GLint location = glGetUniformLocation(this->m_RendererID, name);

            glUniform3f(location, value.x, value.y, value.z);
        }
        
        void glShader::SetVec4f(cstring name, const glm::vec4& value) const {
            GLint location = glGetUniformLocation(this->m_RendererID, name);

            glUniform4f(location, value.x, value.y, value.z, value.w);
        }

        void glShader::SetMat4f(cstring name, const glm::mat4& value) const {
            GLint location = glGetUniformLocation(this->m_RendererID, name);

            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        }

        void glShader::SetMat3f(cstring name, const glm::mat3& value) const {
            GLint location = glGetUniformLocation(this->m_RendererID, name);

            glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
        }

        void glShader::CheckCompileErrors(u32 object, CompileType type) {
            int success;
            char infoLog[1024];

            switch (type) {
                case PROGRAM:
                    glGetProgramiv(object, GL_LINK_STATUS, &success);
                    if (!success) {
                        glGetProgramInfoLog(object, 1024, NULL, infoLog);

                        OASSERTM(false, "Shader Program Error:\n\t%s\n", infoLog);
                    }
                    break;

                case SHADER:
                    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
                    if (!success) {
                        glGetShaderInfoLog(object, 1024, NULL, infoLog);

                        OASSERTM(false, "Shader Compile Error:\n\t%s\n", infoLog);

                    }
            }
        }

    }   // Ocean

}   // Ocean
