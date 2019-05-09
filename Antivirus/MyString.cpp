#include "MyString.h"



const char* MyString::GetMyString() const
{
	return this->m_Content;
}


MyString::Types MyString::GiveMeYourExtension()
{
	char* Data = new char[(*this).MyStrlen()];
	strcpy(Data, this->GetMyString());
	char* CharPointer;

	CharPointer = strtok(Data, ".");
	while (CharPointer != NULL)
	{
		CharPointer = strtok(NULL," ");
		if (strcmp(CharPointer, "txt") == 0)
			return Types::Txt;
		else if (strcmp(CharPointer, "exe") == 0)
			return Types::Exe;
		else
			return Types::Unknown;
	}
	return Types::Unknown;
}


const int MyString::MyStrlen()const
{
	return strlen((*this).m_Content) + 1;
}


void MyString::Devide(MyList<MyString>& List)
{
	try
	{
		char *Data = new char[(*this).MyStrlen()];
		if (Data == nullptr)
		{
			throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
		}
		strcpy(Data, this->GetMyString());
		char * CharPointer;

		CharPointer = strtok(Data, " ");
		while (CharPointer != NULL)
		{
			MyString Aux(CharPointer);
			List.PushBack(Aux);
			CharPointer = strtok(NULL, " ");
		}
	}
	catch (Exceptions* Except)
	{
		Except->PrintMessage();
		exit(0);
	}
}


bool MyString::Compare(MyString & DBWord, float Percent)
{
	int Length = DBWord.MyStrlen();
	Length = (Length*Percent) / 100;

	if (Length <= 0)
		return false;

	int MatchLength = 0;

	const char* ToScanAux = (*this).GetMyString();
	const char* DBWordAux = DBWord.GetMyString();

	for (int i = 0; i < Length; i++)
	{
		if (ToScanAux[i] == DBWordAux[i])
			MatchLength++;
		else
			return false;
	}
	
	return true;
}


MyString::MyString()
{
	m_Content = nullptr;

}


MyString::MyString(const MyString& Source)
{
	try
	{
		this->m_Content = new char[Source.MyStrlen()];
		if (this->m_Content == nullptr)
		{
			throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
		}
		strcpy(this->m_Content, Source.GetMyString());
	}
	catch (Exceptions* Except)
	{
		Except->PrintMessage();
		exit(0);
	}
}


MyString::MyString(const char* Source)
{
	try {

		m_Content = new char[strlen(Source) + 1];
		if (this->m_Content == nullptr)
		{
			throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
		}
		strcpy(m_Content, Source);
	}
	catch (Exceptions* Except)
	{
		Except->PrintMessage();
		exit(0);
	}
}


MyString::~MyString()
{
	delete[] m_Content;
}


MyString & MyString::operator=(const MyString & Source)
{
	if (this == &Source)
		return *this;

	if (m_Content)
		delete[]m_Content;

	if (!Source.m_Content)
		return *this;

	m_Content = new char[Source.MyStrlen()];
	strcpy(m_Content, Source.GetMyString());

	return *this;
}


bool MyString::operator==(const MyString & MyDB)
{
	if (strcmp(this->GetMyString(), MyDB.GetMyString()) == 0)
		return true;
	return false;
}


ostream& operator<<(ostream& out, const MyString& Content)
{
	cout << Content.m_Content << endl;
	return out;
}