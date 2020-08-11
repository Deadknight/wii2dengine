#include "StdAfx.h"

bool TaskExecutor::run()
{
	Task * t;
	//__try
	try
	{
		while(starter->running)
		{
			t = starter->GetTask();
			if(t)
			{
				t->execute();
				t->completed = true;
				starter->RemoveTask(t);
				delete t;
			}
			else
				//Sleep(20);
				usleep(20000);
		}
	}
	//__except(NULL) { }
	catch(...) { }
	return true;
}
