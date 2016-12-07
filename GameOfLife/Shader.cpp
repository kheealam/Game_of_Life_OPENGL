#include "Shader.h"

string Shader::textFileRead(const char * filename) {
	string str, ret = "";
	ifstream in;
	in.open(filename);
	if (in.is_open()) {
		getline(in, str);
		while (in) {
			ret += str + "\n";
			getline(in, str);
		}
		//    cout << "Shader below\n" << ret << "\n" ; 
		return ret;
	}
	else {
		cout<<"Unable to Open File " << filename << "\n";
		throw 2;
	}
}
GLuint Shader::getShaderObject(){
	return m_shaderObject;
}

GLuint Shader::getShaderType(){

	return m_shaderType;

}

void Shader::init(){

	m_shaderObject = glCreateShader(m_shaderType);
	m_source = textFileRead(m_filePath.c_str());
	GLchar * source = new GLchar[m_source.size() + 1];
	const GLchar *constSource = source;
	strcpy_s(source,m_source.size()+1, m_source.c_str());
	glShaderSource(m_shaderObject, 1, &constSource, NULL);
	glCompileShader(m_shaderObject);
	string msg;
	m_compileStatus = compileShader(m_shaderObject, msg);
	std::cout << msg << std::endl;
}
GLint Shader::compileShader(GLuint shaderObject, string &errMsg){

	glCompileShader(shaderObject);
	GLint isCompiled;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &isCompiled); 
	if (!isCompiled){
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
		errMsg = infoLog;
	}
	return isCompiled;
}

Shader::~Shader()
{
}
