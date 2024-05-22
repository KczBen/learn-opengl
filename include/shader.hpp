#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
    public:
        // Program ID
        unsigned int ID;

        // Construct shader
        Shader(const char* vertexPath, const char* fragmentPath) {
            // Read shader files
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try {
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;

                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                vShaderFile.close();
                fShaderFile.close();

                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            
            catch(std::ifstream::failure e) {
                std::cout << "Error: Failed to read shader file" << std::endl;
            }

            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            // Compile and link
            unsigned int vertexShader, fragmentShader;
            int successVertex;
            char infoLogVertex[512];
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vShaderCode, NULL);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
            if (!successVertex) {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
                std::cout << "Error: Failed to compile vertex shader" << infoLogVertex << std::endl;
            }

            int successFragment;
            char infoLogFragment[512];
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
            if (!successFragment) {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragment);
                std::cout << "Error: Failed to compile fragment shader" << infoLogFragment << std::endl;
            }
            
            int successLinker;
            char infoLogLinker[512];
            ID = glCreateProgram();
            glAttachShader(ID, vertexShader);
            glAttachShader(ID, fragmentShader);
            glLinkProgram(ID);
            glGetProgramiv(ID, GL_LINK_STATUS, &successLinker);
            if (!successLinker) {
                glGetProgramInfoLog(ID, 512, NULL, infoLogLinker);
                std::cout << "Error: Failed to link shader program" << infoLogLinker << std::endl;
            }

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        };

        // Use shader
        void use() {
            glUseProgram(ID);
        };

        // Uniforms
        void setBool(const std::string &name, bool value) const {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        };
        void setInt(const std::string &name, int value) const {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        };
        void setFloat(const std::string &name, float value) const {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        };
        void setVec2(const std::string &name, glm::vec2 &value) const {
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        };
        void setVec2(const std::string &name, float x, float y) const {
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
        };
        void setVec3(const std::string &name, glm::vec3 &value) const {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        };
        void setVec3(const std::string &name, float x, float y, float z) const {
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
        };
        void setVec4(const std::string &name, glm::vec4 &value) const {
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        };
        void setVec4(const std::string &name, float x, float y, float z, float w) const {
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
        };
        void setMat2(const std::string &name, glm::mat2 &mat) const {
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        };
        void setMat3(const std::string &name, glm::mat3 &mat) const {
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        };
        void setMat4(const std::string &name, glm::mat4 &mat) const {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        };
};

#endif