#include "FrameWork.h"

using namespace std;

int main()
{
	//Initialize the FrameWork
	FrameWork * frameWork = new FrameWork();
	frameWork->Initialize();

	//Update our FrameWork
	frameWork->Run();

	delete frameWork;
	frameWork = NULL;

	return 0;
}