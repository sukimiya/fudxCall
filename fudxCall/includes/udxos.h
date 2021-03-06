#pragma once

#ifndef WIN32
	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <errno.h>
	#include <dirent.h>
	#include <stdarg.h>
	#include <ctype.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <pthread.h>


	#ifdef __LITEOS__
		#include <lwip/netdb.h>

		#ifndef SIOCGIFCONF
			#define SIOCGIFCONF	0x8912		/* get iface list		*/
		#endif

		#ifndef AI_PASSIVE
			#define AI_PASSIVE     0x1  /* Socket address will be used in bind() call */
		#endif

	#else
		#include<netinet/ip.h>
		#include <arpa/inet.h> 
		#include <netdb.h>
	#endif


	#include <sys/time.h>
	#include <assert.h>
	#include <unistd.h>
	#include <sys/ioctl.h> 
	#include <net/if.h> 

	#ifndef PHOSTENT
		typedef struct hostent *PHOSTENT;
	#endif

	#ifndef SOCKADDR_IN
		typedef struct sockaddr_in SOCKADDR_IN;
	#endif


	#define INFINITE            0xFFFFFFFF  // Infinite timeout

#else

	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif

	#if _WIN32_WINNT < 0x0500
	#define _WIN32_WINNT 0x0500
	#endif

	#pragma warning(disable : 4786)

	#include <windows.h>
	#include <MMSystem.h>
	#include <assert.h>


	#include <fcntl.h>
	#include <WinSock2.h>
	#include <process.h>
	#include <io.h>
	#include <time.h>

	#ifndef SIO_UDP_CONNRESET
	#define SIO_UDP_CONNRESET           _WSAIOW(IOC_VENDOR,12)
	#endif


	#pragma comment(lib,"ws2_32.lib")
	#pragma comment(lib,"winmm.lib")

	typedef int		socklen_t;

#endif

#ifdef __cplusplus
#include <assert.h>
#include <math.h>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include <vector>
using namespace std;
#endif


#ifndef WIN32
	typedef unsigned long			PointerSizedInt;
	typedef unsigned char   		UInt8;
	typedef char					Int8;
	typedef unsigned short  		UInt16;
	typedef short					Int16;
	typedef unsigned int			UInt32;
	typedef int						Int32;
	typedef long long				Int64;
	typedef unsigned long long  	UInt64;
	typedef float               	Float32;
	typedef double              	Float64;

	typedef unsigned long			ulong;
	typedef void*					Handle;
	typedef unsigned long 			DWORD;
	typedef unsigned int			UINT_PTR;
	typedef UInt8					BYTE;
	typedef Int64					INT64;
	typedef Int32					INT32;
	typedef unsigned int				UINT32;
	typedef UInt16					WORD;
	typedef unsigned long long		UINT64;
	typedef unsigned int			UINT;
	typedef UInt8					*PBYTE;
	typedef int						SOCKET;

	typedef unsigned long long uint64;
#ifndef ARM_FUHAN_RTOS
	typedef signed int   int32_t;
#endif
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;

	typedef unsigned char byte;
	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int   uint32;
	typedef short   int16;
	typedef int      int32;
	typedef char *LPSTR;

	#if !defined( __LITEOS__)

		#ifndef BOOL
			typedef long					BOOL;
		#endif

		#ifndef TRUE
			#define TRUE			1
			#define FALSE			0
		#endif
	#endif

	#define MAX_TIMEOUT		0xFFFFFFFF
	#define INVALID_SOCKET	-1
	#define SOCKET_ERROR	-1

	#ifndef CALLBACK
		#define CALLBACK
	#endif

	#ifndef FAR
		#define FAR
	#endif

	#ifdef WIN32
		#ifndef WINAPI
			#define WINAPI __stdcall
		#endif
	#else
		#ifndef WINAPI
		#define WINAPI
		#endif
	#endif



	#ifndef SOCKADDR
		typedef struct sockaddr SOCKADDR;
	#endif

	#define MAX_PATH          260

	#define __max(a,b)	(((a) > (b)) ? (a) : (b))
	#define __min(a,b)	(((a) < (b)) ? (a) : (b))

#else
// Windows compability
	typedef HANDLE pthread_t;
	typedef HANDLE pthread_mutex_t;
	typedef HANDLE pthread_cond_t;
	typedef DWORD pthread_key_t;
	typedef __int64      int64;
	typedef unsigned __int64 QWORD;

#endif


typedef unsigned int UDP_LONG ;
typedef unsigned short UDP_SHORT ;
typedef BYTE UDP_BYTE ; 
typedef long UDX_LONG;
typedef unsigned long UUDX_LONG;


#ifdef ARM_FUHAN_RTOS
struct sockaddr_in6 {
	u8_t            sin6_len;      /* length of this structure    */
	sa_family_t     sin6_family;   /* AF_INET6                    */
	in_port_t       sin6_port;     /* Transport layer port #      */
	u32_t           sin6_flowinfo; /* IPv6 flow information       */
	struct in6_addr sin6_addr;     /* IPv6 address                */
	u32_t           sin6_scope_id; /* Set of interfaces for scope */
};
#endif


//#define ARM_UDX_SDK
