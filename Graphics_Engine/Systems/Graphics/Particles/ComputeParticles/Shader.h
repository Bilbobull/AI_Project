#pragma once

#include "../../Graphics_Headers.h"
#include <string>
#include <cassert>

namespace ComputeShaders
{

  class Shader
  {
  public:
    Shader(const char* vs, const char* fs, const char* gs = 0);
    ~Shader();


    inline GLuint Shader::Get_ID();
    inline void Use();
    inline void Disable();
    inline GLint attribLocation(const char* attrib);
    inline GLint uniLocation(const char *varName);

    // Useful glAttrib* methods
    inline void enableVertexAttribArray(GLint attr);
    inline void vertexAttribPtr(GLint index, GLint size, GLenum type, GLboolean normalized, GLint stride, GLint offset);
    inline void bindAttribLocation(GLint location, const char* attribName);
    // Useful glUniform* methods, returns false when no 'varName' found in shader

    inline bool uni1i(const char* varName, int value);
    inline bool uni1f(const char* varName, float value);
    inline bool uni2f(const char* varName, float x, float y);
    inline bool uni3f(const char* varName, float x, float y, float z);
    inline bool uni4f(const char* varName, float x, float y, float z, float w);
    inline bool uni1fv(const char* varName, GLuint count, float *values);
    inline bool uni2fv(const char* varName, const float* value);
    inline bool uni3fv(const char* varName, const float* values, const int count = 0);
    inline bool uni4fv(const char* varName, const float* values);

    //
    // uniform matrix
    //

    /// sends single 3x3 matrix
    inline bool uniMat3(const char *varName, float *mat, bool transpose = false);
    /// sends single 4x4 matrix
    inline bool uniMat4(const char *varName, const float*mat, bool transpose = false);

    friend class Resources;
    friend class ComputeShader;
    friend class Sprite;

  private:
    Shader() {}
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint geometryShader;
    GLuint shaderProgram;
    std::string Read_Shader(const char* filename);
    GLuint Create_Shader(const char* filename, GLenum shaderType);
    GLuint Create_Shader(const char*, std::string, GLenum shaderType);
    GLuint Create_Shader_From_String(std::string& vs, std::string& fs);
    GLuint Create_Program(std::string name, GLuint _vertexShader, GLuint _fragmentShader, GLuint _geometryShader = 0);
    GLuint Create_Program(std::string name, GLuint _fragmentShader);
  };


  //////////////////////////////////////////////////////////////////////////
  // Inline Methods
  //////////////////////////////////////////////////////////////////////////

  inline GLint Shader::attribLocation(const char* attribName)
  {
    GLint _attribLoc = glGetAttribLocation(shaderProgram, attribName);
    //
    //#ifdef _DEBUG
    //    if (_attribLoc == -1)
    //      std::cout << "ATTRIB " << attribName << " NOT FOUND!\n";
    //#endif

    return _attribLoc;
  }


  inline GLint Shader::uniLocation(const char *varName)
  {
    assert(shaderProgram > 0 && "create the program id first!");
    GLint i = glGetUniformLocation(shaderProgram, varName);

    //    // log msg only in the DEBUG version
    //#ifdef _DEBUG
    //    if (i == -1)
    //      std::cout << "uniform" << varName << "does not exist!\n";
    //#endif

    return i;
  }

  inline void Shader::bindAttribLocation(GLint location, const char* attribName)
  {
    glBindAttribLocation(shaderProgram, location, attribName);
  }


  inline void Shader::enableVertexAttribArray(GLint attr)
  {
    glEnableVertexAttribArray(attr);
  }


  inline void Shader::vertexAttribPtr(GLint index, GLint size, GLenum type, GLboolean normalized, GLint stride, GLint offset)
  {
    glVertexAttribPointer(index, size, type, normalized, stride, (const void*)offset);
  }


  // Useful Uniforms

  inline bool Shader::uni1i(const char *varName, int value)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniform1i(i, value);
    return true;
  }

  inline bool Shader::uni1f(const char *varName, float value)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniform1f(i, value);
    return true;
  }

  inline bool Shader::uni2f(const char *varName, float x, float y)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniform2f(i, x, y);
    return true;
  }

  inline bool Shader::uni3f(const char *varName, float x, float y, float z)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniform3f(i, x, y, z);
    return true;
  }

  inline bool Shader::uni4f(const char *varName, float x, float y, float z, float w)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniform4f(i, x, y, z, w);
    return true;
  }

  inline bool Shader::uni1fv(const char *varName, GLuint count, float *values)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniform1fv(i, count, values);
    return true;
  }

  inline bool Shader::uni2fv(const char* varName, const float* values)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniform2fv(i, 1, values);
    return true;
  }

  inline bool Shader::uni3fv(const char* varName, const float* values, const int count /*= 0*/)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniform3fv(i, count, values);
    return true;
  }

  inline bool Shader::uni4fv(const char *varName, const float *values)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniform4fv(i, 1, values);
    return true;
  }

  inline bool Shader::uniMat3(const char *varName, GLfloat *mat, bool transpose)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniformMatrix3fv(i, 1, transpose, mat);
    return true;
  }

  inline bool Shader::uniMat4(const char *varName, const float*mat, bool transpose /*= false*/)
  {
    GLint i = uniLocation(varName);
    if (i == -1) return false;

    glUniformMatrix4fv(i, 1, transpose, mat);
    return true;
  }

  inline void Shader::Use()
  {
    glUseProgram(shaderProgram);
  }

  inline void Shader::Disable()
  {
    glUseProgram(0);
  }

  inline GLuint Shader::Get_ID()
  {
    return shaderProgram;
  }
}


