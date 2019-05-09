#include "Exceptions.h"



void Exceptions::PrintMessage()const
{
	try {
		ofstream ExceptionReport("ExceptionReport.txt", ios::app);
		if (!ExceptionReport.is_open())
		{
			throw new Exceptions(FileOpenFailed, "Error on Exception file opening!");
		}
		ExceptionReport << "Error Number: " << m_ErrorNumber << endl;
		ExceptionReport << m_Message << endl;
		ExceptionReport.close();
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();
		exit(0);
	}
}


Exceptions::Exceptions(const int ErrorNumber,const  char* Message)
	:m_ErrorNumber(ErrorNumber), m_Message(Message)
{
}


Exceptions::~Exceptions()
{
}