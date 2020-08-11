#include "Stdafx.h"

extern WPads Wiimote[WPAD_MAX_WIIMOTES];

SERVER_DECL time_t UNIXTIME;
SERVER_DECL tm g_localTime;
#define SLEEP_TIME_FPS_LIMIT 20

int main(int argc, char **argv) 
{
	ML_Init();
	ML_EnableNunchuk(true);

	ML_InitFAT();
	ML_SetBackgroundColor(GX_COLOR_WHITE); // Background is now white

	time_t curTime;

	// Startup banner
	UNIXTIME = time(NULL);
	g_localTime = *localtime(&UNIXTIME);
	
	std::vector<Object*> objectList;
	PhysicsMgr *pm = new PhysicsMgr();
	pm->SetDebugRender(true);
	pm->CreateCollisionData();
	pm->SetCollisionData(0.9f, 0.4f);
	pm->SetMaxCollisionCount(1000);
	pm->CreateContactResolver();	
	new Log();
	/*sLog.SetLogging(true);
	sLog.SetLogFile("sd:/error.txt");
	sLog.SetFileLoggingLevel(LOGLEVEL_INFO | LOGLEVEL_ERROR | LOGLEVEL_DEBUG);
	sLog.SetScreenLoggingLevel(LOGLEVEL_INFO | LOGLEVEL_ERROR | LOGLEVEL_DEBUG);*/
	new EventMgr();
	new ResourceMgr();
	new FontMgr();
	new SoundMgr();
	new GUIMgr();

#ifdef DEBUG

	s32 ret;

	char localip[16] = {0};
	char gateway[16] = {0};
	char netmask[16] = {0};

	printf ("\nlibogc network demo\n");
	printf("Configuring network ...\n");

	// Configure the network interface
	ret = if_config ( localip, netmask, gateway, TRUE);
	if (ret>=0) {
		printf ("network configured, ip: %s, gw: %s, mask %s\n", localip, gateway, netmask);
	}

#endif

#ifdef DEBUG
	DEBUG_Init(100, 5656);

	_break();
#endif

	ScriptSystem = new ScriptEngine();
	//ScriptSystem->Reload("sd:/scripts/");
	sLuaMgr.Startup();

	Map *m = new Map();

	m->Load("sd:/uu.map");
	
	GUIProgressBar *gpBar = new GUIProgressBar("asd");
	gpBar->Load(0xFFFF0000, 0xFF000000);
	gpBar->SetPosition(5, 440);
	gpBar->SetSize(100, 20);
	gpBar->SetBorderLength(2, 2);
	sGUIMgr.Add("asd", gpBar);
	GUILabel*gLabel = new GUILabel("lab");
	gLabel->Load("name");
	gLabel->SetColor(0x00, 0x00, 0x00, 0xFF);
	gLabel->SetPosition(57, 456);
	sGUIMgr.Add("lab", gLabel);

	int32 val = 1;

	uint32 start;
	/*uint32 last_time = now();
	uint32 etime;*/
	uint32 timeLastFrame = getMSTime();
	while(1)
	{
		int fps = ML_GetFPS();
		if(fps == 0)
			continue;
		/*if(fps != 0)
			pm->Simulate(1/fps);
		else
			pm->Simulate(1/0.00002);*/

		start = now();
		/*if(! ((++loopcounter) % 10000) )		// 5mins
		{
			ThreadPool.ShowStats();
			ThreadPool.IntegrityCheck();
		}*/

		/* since time() is an expensive system call, we only update it once per server loop */
		curTime = time(NULL);
		if( UNIXTIME != curTime )
		{
			UNIXTIME = time(NULL);
			g_localTime = *localtime(&curTime);
		}

		uint32 timeCurrentFrame = getMSTime();
		
		
		uint32 timeSinceLastFrame = timeCurrentFrame - timeLastFrame;
		timeLastFrame = timeCurrentFrame;
		
		
		Real updateDuration = 1.0f/static_cast<Real>(fps);
		
		m->Update(updateDuration);
		m->Render(updateDuration);
		
		sFontMgr.Update();
		
		val++;
		if(val > 1000)
			val = 10;
		
		gpBar->SetValue(val/10);
		std::wstringstream ss;
		ss << (int32)val/10 << _TEXT("-100");
		gLabel->SetText(ss.str());
		
		sGUIMgr.Draw(updateDuration);
		
		pm->Simulate(0.05f);
	
		if(Wiimote[0].Held.Home) { ML_Exit(); }
		
		/*Sleep(SLEEP_TIME_FPS_LIMIT);

		// UPDATE 
		last_time = now();
		etime = last_time - start;

		if( SLEEP_TIME_FPS_LIMIT > etime )
		{
#ifdef WIN32
			WaitForSingleObject( hThread, SLEEP_TIME_FPS_LIMIT - etime );
#else
			Sleep( SLEEP_TIME_FPS_LIMIT - etime );
#endif
		}*/
		
		ML_Refresh();
	}

	//Cleanup
	delete pm;

	return 0;
}
