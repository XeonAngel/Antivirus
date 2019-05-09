#include "Antivirus.h"



void Antivirus::Scan(float Percent)
{
	m_Core->Scan(Percent);
}

void Antivirus::SetMaxWorkers(int MaxWorkers)
{
	m_Core->SetMaxWorkers(MaxWorkers);
}

void Antivirus::CheckIfUpdate()
{
	m_Core->CheckIfUpdate();
}

Antivirus::Antivirus(const MyString* Files, const MyString* TextUpdate, const char* BinaryUpdate)
{
	m_Core = ScanManager::GetInstance(Files, TextUpdate, BinaryUpdate);
}


Antivirus::~Antivirus()
{
	m_Core->DestroyInstance();
}