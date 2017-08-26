#include "ShaderLoader.h"

namespace ShaderUtil
{
	GLuint LoadShaders(const char* VertexPath, const char* FragmentPath)
	{
		using namespace std;

		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		//Loading Vertex Shader
		string VertexShaderSource;
		ifstream VertexShaderStream(VertexPath, ios::in);
		if (VertexShaderStream.is_open())
		{
			string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderSource += "\n" + Line;
			VertexShaderStream.close();
		}
		else
		{
			cout << "Failed to load " << VertexPath << endl;
			return NULL;
		}

		//Loading Fragment Shader
		string FragmentShaderSource;
		ifstream FragmentShaderStream(FragmentPath, ios::in);
		if (FragmentShaderStream.is_open())
		{
			string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderSource += "\n" + Line;
			VertexShaderStream.close();
		}
		else
		{
			cout << "Failed to load " << FragmentPath << endl;
			return NULL;
		}

		char const* VertexSourcePointer = VertexShaderSource.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		char const* FragmentSourcePointer = FragmentShaderSource.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		return ProgramID;
	}
}
