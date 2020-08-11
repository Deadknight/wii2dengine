#ifndef COMMON_H
#define COMMON_H

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef uint32_t DWORD;

#define SERVER_DECL
#define NOT_MOBILE
#define HAVE_DARWIN
#define DEDOSAN_INLINE inline
#define MULTITHREAD false
#define MAXGMFILE 80
#define MAXLUAFILE 80
#define USING_BIG_ENDIAN

/*uint32 GUID_HIPART( uint64 GUID )
{
	uint32 higuid = *( reinterpret_cast< const uint32* >( &GUID ) + 1 );
	return higuid;
}
uint32 GUID_LOPART( uint64 GUID )
{
	uint32 loguid = *( reinterpret_cast< const uint32* >( &GUID ) );
	return loguid;
}*/

#ifndef WIN32
#ifndef USING_BIG_ENDIAN
#define GUID_LOPART(x) ( ( x >> 32 ) )
#define GUID_HIPART(x) ( ( x & 0x00000000ffffffff ) )
#else
#define GUID_HIPART(x) ( ( x >> 32 ) )
#define GUID_LOPART(x) ( ( x & 0x00000000ffffffff ) )
#endif
#else
#define GUID_HIPART(x) (*(((uint32*)&(x))+1))
#define GUID_LOPART(x) (*((uint32*)&(x)))
#endif

#ifdef WIN32

#define I64FMT "%016I64X"
#define I64FMTD "%I64u"
#define SI64FMTD "%I64d"
#define snprintf _snprintf
#define atoll __atoi64

#else

#define stricmp strcasecmp
#define strnicmp strncasecmp
#define I64FMT "%016llX"
#define I64FMTD "%llu"
#define SI64FMTD "%lld"

#endif

#ifndef WIN32
#include <sys/timeb.h>
#endif

DEDOSAN_INLINE uint32 now()
{	
#ifdef WIN32
	return GetTickCount();
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
}

#ifdef WIN32
__forceinline uint32 getMSTime() { return GetTickCount(); }
#else
DEDOSAN_INLINE uint32 getMSTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return (tv.tv_sec * 1000) + (uint32)(tv.tv_usec / 1000);
}
#endif

#ifdef WIN32
__forceinline uint32 getNanoTime() { return GetTickCount(); }
#else
DEDOSAN_INLINE uint32 getNanoTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000) + (tv.tv_usec);
}
#endif

#ifndef WIN32
#define FALSE   0
#define TRUE	1
#endif

#ifndef WIN32
#define Sleep(ms) usleep(1000*ms)
#endif

extern SERVER_DECL time_t UNIXTIME;		/* update this every loop to avoid the time() syscall! */
extern SERVER_DECL tm g_localTime;

#define ADDFLAG(val, flag) val |= flag
#define REMOVEFLAG(val, flag) val &= ~flag

#endif
