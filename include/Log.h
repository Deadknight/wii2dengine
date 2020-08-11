#ifndef LOG_H
#define LOG_H

#define TRED 1
#define TGREEN 2
#define TYELLOW 3
#define TNORMAL 4
#define TWHITE 5
#define TBLUE 6

enum LogType
{
	LOGTYPE_CONSOLE = 0x1,
	LOGTYPE_FILE = 0x2,
	LOGTYPE_ALL = LOGTYPE_CONSOLE | LOGTYPE_FILE
};

enum LogLevel
{
	LOGLEVEL_INFO = 0x1,
	LOGLEVEL_ERROR = 0x2,
	LOGLEVEL_DEBUG = 0x4
};

//std::string FormatOutputString(const char * Prefix, const char * Description, bool useTimeStamp);

class Log : public Singleton< Log > 
{
public:
	Log();
	void outString( LogType to, LogLevel level, const char * str, ... );

	void SetLogging(bool val);

	void Init(int32 fileLogLevel, int32 consoleLogLevel);
	void SetLogFile(std::string file);
	void SetFileLoggingLevel(int32 level);
	void SetScreenLoggingLevel(int32 level);

private:
	bool m_loggingEnabled;
	std::string m_logFile;
	int32 m_fileLogLevel;
	int32 m_consoleLogLevel;
	Mutex m_fileMutex;
};

#define sLog Log::getSingleton()

#endif
