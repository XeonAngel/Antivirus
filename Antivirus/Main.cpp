#include "Antivirus.h"

#define MaxWorkers 2

int main()
{
	MyString TextUpdate("delete virus");
	MyString Files("ExecutableFile1.exe ExecutableFile2.exe NormalText1.txt Altele.txt Adobe.lol ThisWasAPicture(Jpeg).exe");

	Antivirus WindowsDefender(&Files, &TextUpdate, "BinaryUpdate.bin");

	WindowsDefender.SetMaxWorkers(MaxWorkers);

	WindowsDefender.CheckIfUpdate();

	float Percent = 50.0f;//Set Percent to 0.0f for normal Scan
	WindowsDefender.Scan(Percent);

	return 0;
}