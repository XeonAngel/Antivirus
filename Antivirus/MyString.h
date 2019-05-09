#pragma once

#include "Exceptions.h"
#include "MyList.h"


class MyString
{
	friend class Database;

	char* m_Content;

	public:

	enum class Types {
		Txt,
		Exe,
		Unknown
	};

	const char*  GetMyString()const;
	Types GiveMeYourExtension();
	const int MyStrlen()const;

	void Devide(MyList<MyString>&List);
	bool Compare(MyString& DBWord, float Percent);


	MyString();
	MyString(const MyString &Source);
	MyString(const char* Source);
	~MyString();


	friend ostream& operator<<(ostream& out, const MyString& Content);
	MyString& operator= (const MyString& Source);
	bool operator==(const MyString& MyDB);
};