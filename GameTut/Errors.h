#pragma once
#include<string>
#include<iostream>


typedef std::string str;

using std::cout;
using std::endl;

class Errors
{
public:
	Errors();
	~Errors();
	void fatalErr(const str& err);
	void fatalErrShader(const str&err, const str&type);
	void fatalErrFile(const str&filePath);
};

