#include "Errors.h"



Errors::Errors()
{
}


void Errors::fatalErr(const str& err)
{
	cout << err << endl;
	while(true){};
}

void Errors::fatalErrShader(const str&err, const str&type)
{
	cout << err  << "Of Type : " << type << endl;
	while (true) {};
}

void Errors::fatalErrFile(const str&filePath)
{
	cout << "Could Not Load : " << filePath << endl;
	while(true){};
}
Errors::~Errors()
{
}
