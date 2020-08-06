#include <sennet/renderer/shader.hpp>

#include <glad/glad.h>

/*
// Shaders are programs created in a two-step compilation process;
// object compilation and linking.

// Procedure for setting up a shader.

// Step 1: Create shader object.
GLuint glCreateShader(GLenum shaderType);

// GLenum:
// GL_VERTEX_SHADER; GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER,
// GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER, GL_COMPUTE_SHADER

// Step 2: Load GLSL source code.
void glShaderSource(GLuint shader, GLsizei count, const GLchar** string,
	const GLint* length);

// Step 3: Compile shader.
void glCompileShader(GLuint shader);

// Shader compilation status.
GLint success = 0;
glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

// Shader error log.
GLint logSize = 0;
glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
void glGetShaderInfoLog(GLuint shader, GLsizei maxLength,
	GLsizei* length, GLchar *infoLog);

// Step 4: Program setup.
GLuint glCreateProgram();

// Step 5: Attaching shader(s).
void glAttachShader(GLuint program, GLuint shader);

// Step 6: Cleanup / detaching shader(s).
void glDetachShader(GLuint program, GLuint shader);

// Step 7: Cleanup / deleting shader(s)
void glDeleteShader(GLuint shader);
*/

namespace sennet
{

shader::shader(const std::string& vertex_src, const std::string& fragment_src)
{
	// Create an empty vertex shader handle
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar *source = vertex_src.c_str();
	glShaderSource(vertex_shader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertex_shader);

	GLint is_compiled = 0;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
	if(is_compiled == GL_FALSE)
	{
		GLint max_length = 0;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

		// The maxLength includes the NULL character
		std::vector<GLchar> info_log(max_length);
		glGetShaderInfoLog(vertex_shader, max_length, &max_length, 
			&info_log[0]);
		
		// We don't need the shader anymore.
		glDeleteShader(vertex_shader);

		SN_CORE_ERROR("{0}", info_log.data());
		SN_CORE_ASSERT(false, "Vertex shader compilation failure!")
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = fragment_src.c_str();
	glShaderSource(fragment_shader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
	if (is_compiled == GL_FALSE)
	{
		GLint max_length = 0;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

		// The maxLength includes the NULL character
		std::vector<GLchar> info_log(max_length);
		glGetShaderInfoLog(fragment_shader, max_length, &max_length, 
			&info_log[0]);
		
		// We don't need the shader anymore.
		glDeleteShader(fragment_shader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertex_shader);

		SN_CORE_ERROR("{0}", info_log.data());
		SN_CORE_ASSERT(false, "Fragment shader compilation failure!")
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_renderer_id = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(m_renderer_id, vertex_shader);
	glAttachShader(m_renderer_id, fragment_shader);

	// Link our program
	glLinkProgram(m_renderer_id);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint is_linked = 0;
	glGetProgramiv(m_renderer_id, GL_LINK_STATUS, (int *)&is_linked);
	if (is_linked == GL_FALSE)
	{
		GLint max_length = 0;
		glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &max_length);

		// The maxLength includes the NULL character
		std::vector<GLchar> info_log(max_length);
		glGetProgramInfoLog(m_renderer_id, max_length, &max_length, 
			&info_log[0]);
		
		// We don't need the program anymore.
		glDeleteProgram(m_renderer_id);

		// Don't leak shaders either.
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		SN_CORE_ERROR("{0}", info_log.data());
		SN_CORE_ASSERT(false, "Shader link failure!");
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_renderer_id, vertex_shader);
	glDetachShader(m_renderer_id, fragment_shader);
}

shader::~shader()
{
	glDeleteProgram(m_renderer_id);
}

void shader::bind() const
{
	glUseProgram(m_renderer_id);
}

void shader::unbind() const
{
	glUseProgram(0);
}

}
