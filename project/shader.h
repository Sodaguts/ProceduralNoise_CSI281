#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>


// shader class code used from learnopengl.com
class Shader
{
    public:
        unsigned int ID;

        Shader()
        {
            
        };

        unsigned int createShader(const char* vertexPath, const char* fragmentPath)
        {
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try
            {
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
            catch(std::ifstream::failure e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
            }

            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            //compile shaders
            unsigned int vertex,fragment;
            int success;
            char infoLog[512];

            //vertex shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);

            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                char infoLog[512];
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                printf("Failed to compile shader: %s", infoLog);
            }

            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                char infoLog[512];
                glGetShaderInfoLog(fragment, 512, NULL, infoLog);
                printf("Failed to compile shader: %s", infoLog);
            }

            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);

            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if(!success){
                char infoLog[512];
                glGetProgramInfoLog(ID, 512, NULL, infoLog);
                printf("Failed to link shader program: %s", infoLog);
            }

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            return ID;
        };

        void use() 
        {
            glUseProgram(ID);            
        };
        void setBool(const std::string &name, bool value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        };
        void setInt(const std::string &name, int value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        };
        void setFloat(const std::string &name, float value) const
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        };

        void setVec2(const std::string &name, float x, float y)
        {
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
        };

        private:
        //std::string vertexShaderSource;

};