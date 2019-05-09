#pragma once

#include <iostream>
#include <fstream>


using std::ofstream;
using std::ifstream;
using std::fstream;
using std::ios;

using std::ostream;

#define FileOpenFailed 0
#define WorkerNotAvaible 1
#define MemAllocationFailed 2
#define EmptyDataBase 3
#define UnkownExtension 4

using std::cout;
using std::endl;


class Exceptions
{
	const int m_ErrorNumber;
	const char* m_Message;

	public:

	void PrintMessage()const;

	Exceptions(const int ErrorNumber,const char* Message);
	~Exceptions();
};