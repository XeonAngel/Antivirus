#include "TextScanWorker.h"


void TextScanWorker::SaveWords()
{
	try
	{
		ifstream MyText(m_File.GetMyString());
		if (!MyText.is_open())
		{
			throw new Exceptions(FileOpenFailed, "Error on file opening!");
		}

		char *Words = new char[MaxLength];
		if (Words == nullptr)
		{
			throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
		}

		while (MyText >> Words)
		{
			MyString Aux(Words);
			m_WordsToScan.PushBack(Aux);
		}

		delete[] Words;

		MyText.close();
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();
		m_JobDone = true;
	}
}


void TextScanWorker::Scan()
{
	SaveWords();

	if (m_JobDone == false)
	{
		int VirusFound = 0;

		for (int i = 0; i < m_WordsToScan.GetMyNumberOfElements(); i++)
			for (int j = 0; j < m_TextMalware->GetMyNumberOfElements(); j++)
			{
				if (m_Percent == 0)
				{
					NormalScan(VirusFound, i, j);
				}
				else
				{
					StrictScan(VirusFound, i, j);
				}
			}

		WriteReport(VirusFound);


		m_JobDone = true;
		m_WordsToScan.Clean();
		m_ScanedFiles++;
	}
}


void TextScanWorker::NormalScan(int & NumberOfVirus, int i, int j)
{
	if (m_WordsToScan[i] == (*m_TextMalware)[j])
		NumberOfVirus++;
}


void TextScanWorker::StrictScan(int & NumberOfVirus, int i, int j)
{
	if (m_WordsToScan[i].Compare((*m_TextMalware)[j], m_Percent) == true)
		NumberOfVirus++;
}


TextScanWorker::TextScanWorker(MyString Job, const float Percent, MyList<MyString>* TextDB)
	:ScanWorker(Job, Percent, MyString::Types::Txt), m_TextMalware(TextDB)
{
}


TextScanWorker::~TextScanWorker()
{
}