#pragma once

#include "ScanManager.h"

class Antivirus
{
	ScanManager* m_Core;

	public:

	void Scan(float Percent);
	void SetMaxWorkers(int MaxWorkers);
	void CheckIfUpdate();

	Antivirus(const MyString* Files, const MyString* TextUpdate, const char* BinaryUpdate);
	~Antivirus();
};