#include "Stdafx.h"

/*std::string FormatOutputString(const char * Prefix, const char * Description, bool useTimeStamp)
{
	char p[MAX_PATH];
	p[0] = 0;
	time_t t = time(NULL);
	tm * a = gmtime(&t);
	strcat(p, Prefix);
	strcat(p, "/");
	strcat(p, Description);
	if(useTimeStamp)
	{
		char ftime[100];
		snprintf(ftime, 100, "-%-4d-%02d-%02d %02d-%02d-%02d", a->tm_year+1900, a->tm_mon+1, a->tm_mday, a->tm_hour, a->tm_min, a->tm_sec);
		strcat(p, ftime);
	}

	strcat(p, ".log");
	return std::string(p);
}*/

initialiseSingleton( Log );

static const char* colorstrings[TBLUE+1] = 
{
	"",
	"\033[22;31m",
	"\033[22;32m",
	"\033[01;33m",
	//"\033[22;37m",
	"\033[0m",
	"\033[01;37m",
	"\033[22;34m",
};

Log::Log()
{
	m_loggingEnabled = false;
}

void Log::outString( LogType to, LogLevel level, const char * str, ... )
{
	if(!m_loggingEnabled)
		return;
	
	try
	{
		char buffer[250];
		bool bufferFilled = false;

		if(to & LOGTYPE_CONSOLE)
		{
			if(m_consoleLogLevel & level)
			{
				bufferFilled = true;
				va_list ap;
				va_start(ap, str);
				vsprintf(buffer, str, ap);
				va_end(ap);
				sFontMgr.DrawText(buffer);
			}
		}
		if(to & LOGTYPE_FILE)
		{
			if(m_fileLogLevel & level)
			{
				if(!bufferFilled)
				{
					bufferFilled = true;
					va_list ap;
					va_start(ap, str);
					vsprintf(buffer, str, ap);
					va_end(ap);				
				}
				m_fileMutex.Acquire();
				FILE *fp = fopen(m_logFile.c_str(), "a");
				if(fp)
				{
					fprintf(fp, buffer);
					fflush(fp);
					fclose(fp);
				}
				else
				{
					//Log to gui?
				}
				m_fileMutex.Release();
			}
		}
	}
	catch(...)
	{
		m_fileMutex.Release();
	}
}

void Log::Init(int32 fileLogLevel, int32 consoleLogLevel)
{
	m_consoleLogLevel = consoleLogLevel;
	m_fileLogLevel = fileLogLevel;
}

void Log::SetLogging(bool val)
{
	m_loggingEnabled = val;
}

void Log::SetLogFile(std::string file)
{
	m_logFile = file;
}

void Log::SetScreenLoggingLevel(int32 level)
{
	m_consoleLogLevel = level;
}

void Log::SetFileLoggingLevel(int32 level)
{
	m_fileLogLevel = level;
}
