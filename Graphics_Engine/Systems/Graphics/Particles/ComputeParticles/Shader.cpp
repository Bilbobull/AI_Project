
#include "Shader.h"
#include <iostream>
#include <fstream>

namespace ComputeShaders
{
  // Shader sources
  // Shader sources
  static const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec2 position;"
    "in vec4 color;"
    "in vec2 texcoord;"
    "out vec4 Color;"
    "out vec2 Texcoord;"
    "void main() {"
    "   Color = color;"
    "   Texcoord = texcoord;"
    "   gl_Position = vec4(position, 0.0, 1.0);"
    "}";
  static const GLchar* fragmentSource =
    "#version 150 core\n"
    "in vec4 Color;"
    "in vec2 Texcoord;"
    "out vec4 outColor;"
    "uniform sampler2D tex;"
    "void main() {"
    "   outColor = Color;"
    "}";


  Shader::Shader(const char* vs, const char* fs, const char* gs/*= NULL*/)
  {
    vertexShader = Create_Shader(vs, GL_VERTEX_SHADER);
    fragmentShader = Create_Shader(fs, GL_FRAGMENT_SHADER);
    shaderProgram = Create_Program("", vertexShader, fragmentShader, geometryShader);
  }


  Shader::~Shader()
  {
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
  }


  std::string Shader::Read_Shader(const char* filename)
  {
    std::ifstream shaderFile(filename);

    if (!shaderFile.good())
    {
      std::cout << "File cannot be loaded...  " << filename;
      return NULL;
    }

    return std::string(std::istreambuf_iterator<char>(shaderFile),
      std::istreambuf_iterator<char>());
  }


  GLuint Shader::Create_Shader(const char* filename, GLenum shaderType)
  {
    std::string shaderSource;
    shaderSource = Read_Shader(filename);
    const char* source = shaderSource.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    char log[1000];
    glGetShaderInfoLog(shader, 1000, NULL, log);

    std::cout << filename << "\nCompile Status...\n" << log << "\n--------------" << std::endl;

    return shader;
  }


  GLuint Shader::Create_Shader(const char* filename, std::string shaderSource, GLenum shaderType)
  {
    const char* source = shaderSource.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    char log[1000];
    glGetShaderInfoLog(shader, 1000, NULL, log);

    std::cout <<  filename <<  "\nCompile Status...\n" << log << "\n--------------" << std::endl;

    return shader;
  }


  GLuint Shader::Create_Program(std::string name, GLuint _vertexShader, GLuint _fragmentShader, GLuint _geometryShader /*= 0*/)
  {
    GLuint program = glCreateProgram();
    glAttachShader(program, _vertexShader);
    glAttachShader(program, _fragmentShader);
    if (_geometryShader != 0)
      glAttachShader(program, _geometryShader);
    //glBindFragDataLocation (shaderProgram, 0, "outColor");
    glLinkProgram(program);
    char log[1000];
    glGetProgramInfoLog(program, 1000, NULL, log);
    std::cout << "\n" << name << "\nLink Status...\n" << log << "\n--------------" << std::endl;

    return program;
  }

  GLuint Shader::Create_Program(std::string name, GLuint _fragmentShader)
  {
    GLuint program = glCreateProgram();
    glAttachShader(program, _fragmentShader);
    glLinkProgram(program);
    char log[1000];
    glGetProgramInfoLog(program, 1000, NULL, log);
    std::cout << "\n" << name << "\nLink Status...\n" << log << "\n--------------" << std::endl;

    return program;
  }

  GLuint Shader::Create_Shader_From_String(std::string& vs, std::string& fs)
  {
    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);

    return shaderProgram;
  }

}
