
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FASTUDX_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FASTUDX_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifndef FASTUDX_H
#define FASTUDX_H

#define UDXMAXVER	2
#define UDXSLAVER	206



// //// //// //// //// //// //// //// //
// 1.84 ��Ҫ���ں˸ĳ��˶��̣߳����պͷ�����IO,�߼��϶����ֿ��ˣ�����֧�ָ��ã���Ӧ�ٶ����
// 1.86	�����ں˵�һ�θ������Ż����޸�BUG,���ȶ��汾
// 1.87 �޸��˶�ʱ����bug,����ÿ�����������ˣ�UdxTrackData,����30���û�����������������Ϊsizeof(UINT64)*30
// 1.88 �޸���64λ�����bug,���Ӿ�̬64λlib,.a�ļ�
// 1.90 ��չ����󴰿�Ϊ16k���ڸ��ӳ٣�GM���١����ӳ�������������������ACK��Ƭ���ܡ�ȱ�㣨��֧������1.90��ǰ�汾��
// 1.91 ��ӵ�����ƽ������Ż�������ack����Ƶ�ʵ�������ֹ����Ҫ���ش�
// 1.92 �Ż��ڴ�ػ��գ�����СBUG���������绺����Ʋ���
// 1.93 ȥ�����ļ�����ӿڵ�Accept�������Ѿ���ʱ�������ˣ�����ʵ����cancel��������ǰ�汾û��ʵ��,�������������ӳ�ʱ�¼����ܴ�����BUG
// 1.94 ����IMulcardUdx֧�ֶ�����磨����,3G��)��һ��UDX���󣬽��е��������շ�����Ҫ�����ƶ��豸������ϵͳ��
// 1.95 �޸�1.93��������ӳ�ʱ���ܴ����¼���bug. ȥ�������ظ����õı���
// 1.96 �޸����ڴ�COPY��Ч�����⣬������һ��COPY���������5% CPUִ��Ч�ʣ����̵߳��ȣ����������ͷŹ��̣��������ȶ���
// 1.97 ��ǿ���ļ�������У�����ͬ���ļ�ʱ���������ط��ͳɹ��������޸�������̽�����
// 1.98 IFastUdx�ӿ��������Ƿ��Ƭѡ�����ѻص��¼�������������ȫ��Ӱ�죬���ݰ����������
// 1.991 �����˶��̲߳��м�����ԣ��޸�����SetFloatSize����16MBʱ��ACK����1500�ֽڵ�BUG������IMediaPush�ӿڷ�������Ƶ����ֹ����,���ٶȼ����㷨
// 1.992 �޸��Ǻϲ������BUG,�������ļ�У�����
// 1.993 �޸�linux������fork�ӽ���ʱ��ʱ�ӱ���ǰ�ͷ�����
// 1.994 �޸�OnStreamNeedMoreData(this)->OnStreamNeedMoreData(this,needdata),����IMediaPush�ص�OnMediaPushFrameEvent�������ͻ�����ʱ����ʾ����Ƶ�ж����컺�壬��ͨ���������壬�����ӳ�
//		 �����¼�OnStreamFinalRelease�������ӱ��ͷ�ǰ���ص���������һЩ�����û��Զ�������
// 1.995 �Է��Ͷ��й�����һЩ�����Ż������¼����������е������޸�IMediaPush�İ�ͷ�ṹ��SID��short�ĳ�int,��Ϸֲ�ʽ����
//		 �������������ӹ��򣬶��ڴ���������ƣ�����log��ֹ���ܣ��������������
// 1.996 ����1.995�У�ΪCBuffmaplist���Ż����Ͷ�����������ͻ�����bug��
// 1.997 ����ACK�з�Ƭ����
// 1.998 �޸�IMulcardUdx��ʵ�֣�ȫ��֧�ֶ࿨
// 1.999 �Ż��˰�ͷ��ȥ����ԴID,����תID��������4�ֽڣ���ԭ���İ�ͷ14�ֽڣ���Ϊ10�ֽ�,�����Ż��˶�̬����Ϊocx��activex�˳����⡣
//       �Ż���ack�����Ĵ�С��200KB����������ACK��������2K, 10MB������ACK����5KB
// 2.0   �Ż���ͳ�����ڣ�Ԥ���������������Զ��������ͻ���
// 2.002 ��ͷ��ȡ�����㷨����ֹ����ǽ��������������UDP����
// 2.003 �������ӳٹر����ԣ��ܽ���tcp.close֮ǰ�����ݷ�����ɣ�Ȼ���ͷ�tcp���ӣ����ڷ���һЩ����ǳ�����(Ĭ���ӳ�10��)��
// 2.004 ����������ʱЭ����չ���ݣ�����С��1K
// 2.005 �Ż��˶Ͽ����̣������ӶϿ�ʱ������ɾ��UDXʱ���Ͽ�������û�з��ͳ�ȥ��Ŀǰ�������������Ի��ᣬ���ӶϿ���Ϣ���͵ĳɹ��ʣ�
//

// 2.101 ���FEC��֧�֣�����2.005������֧��IPV6������Ϣͨ���ĳɿ���ͨ�����������γ�RTP+FEC��ʽ�������ʺ���������
// 2.102 ����ͨ���Ƴ�FEC��֧�֣���Ϣͨ���շ����õ����߳�,����֧��FEC
// 2.103-4 ӵ���㷨�Ż������շ��߳����¹滮���������ʻ���
// 2.105 �Ż�4G��P2P�����Ӵ�͸�ɹ���
// 2.106 ����ͨ������FECģʽ��FECģʽ�У�FEC���С�Զ���Ӧ
// 2.107 �޸ķ����ٶȲ��ԣ�ӵ�����۸�һ��������ȷ����������̱�1.0
// 2.109 �޸ķ����ٶȲ��ԣ�ӵ�����۸�һ��������ȷ����������̱�2.0
// 2.200 �Ż��ٶȣ�RTT������ԣ��������ݾ�ȷ����,��̬�ָ�
// // 
// 2.201 �Ż������ٶȣ��޸��ڴ�
// 2.202 �Ż�FEC�����ٶȣ��޸�FECΪ��̬FEC���������䣬Ҳ�����ڲ���̬�������»���
// 2.203 �Ż�FEC�����ʱ������������75%����Ҫ��FEC������㣬��Ϊ��������պ󣬿����ڸ���ʱ���ڻ��гٵ�����������ݰ�������������ǲ���ҪFEC�����
// 2.204 �Ż���������������500����������5000���ӣ������շ�
// 2.205 �Ż���P2P���ӹ��̣��ͻ��������ˣ��ͻ���ͬʱ����P2P��TS�������P2P���Զ��л���֧��������ӦFEC��������FEC)�����󣬴˹��܌�ը��
// 2.206 �޸���������30%����ʱFEC�ڴ�й¶���⣬�����ڴ�ռ��

// MS VC++ 10.0 _MSC_VER = 1600
// MS VC++ 9.0 _MSC_VER = 1500
// MS VC++ 8.0 _MSC_VER = 1400
// MS VC++ 7.1 _MSC_VER = 1310
// MS VC++ 7.0 _MSC_VER = 1300
// MS VC++ 6.0 _MSC_VER = 1200
// MS VC++ 5.0 _MSC_VER = 1100


#ifdef WIN32
	#if _MSC_VER >= 1600 // for vc8, or vc9 vs 2008 ~ vs2013

#include <WinSock2.h>
#include <windows.h>

#include <MMSystem.h>
#include <assert.h>

#ifndef _cplusplus
#include <atlbase.h>
#endif

#include <fcntl.h>

#include <io.h>

typedef unsigned int UDP_LONG ;
typedef unsigned short UDP_SHORT ;
typedef BYTE UDP_BYTE ; 
typedef long UDX_LONG;
typedef unsigned long UUDX_LONG;

#pragma comment(lib,"ws2_32.lib")
#include <map>
#include <vector>
#include <string>
#include <list>
using namespace std;


	#else
		#include "udxos.h"
	#endif
#else
	#include "udxos.h"
#endif


enum ERROCODE
{
	//errocode : 0,�ɹ���1���µ����ӵ�����2��Զ�ܾ̾�����,3��ʱ
	UDX_CON_SUCCEED,
		UDX_CON_NEWCON,
		UDX_CON_EJECT,
		UDX_CON_TIMEOUT,
		UDX_CON_SERVEREXIT
};


#include "mntypedef.h"

#define UDX_P2P_REGISTER_MSG_LINK_FLAG	1//UDX P2P ��Ϣ����
#define UDX_P2P_DATATRANS_LINK_FLAG	2//UDX P2P ��������

#ifdef WIN32
#pragma pack( push, 1 )

	#ifndef UDXPACKED
	#define UDXPACKED 
	#endif
#else

	#ifndef UDXPACKED
	#define UDXPACKED	__attribute__((packed, aligned(1)))
	#endif

#endif


typedef void* UFASTUDX;
typedef void* UDXTCP;

typedef void (CALLBACK UDXPRC)(int eventtype, int erro, UDXTCP s, BYTE* pData, int len);
typedef void (CALLBACK UDXP2PPRC)(char* user1,char* user2,UINT64 dwuser);

typedef UDXPRC FAR *LPUDXPRC;
typedef UDXP2PPRC FAR *LPUDXP2PPRC;



	//�Ե�ַ��һЩת����һ�㲻��ʹ��
class IUdxTools
{
public:
	virtual UINT64 Addr2Int64(SOCKADDR* pAddr,UDP_LONG streamId) = 0;//����ַ��һ��WORDת��Ϊһ��64λ����
	virtual void TraceAddr(SOCKADDR* pAddr) = 0;//��ӡ
	virtual void GetSpeedStr(char * buff,UINT64 speed  ) = 0;//�õ����ͻ���յ��ٶ��ַ���
	virtual void Trace(const char* strLog) = 0;
	virtual int GetMD5( BYTE* pData,int len,char * pStrMD5Out ) = 0;
	virtual UDP_LONG GetHashLong(char* strKey) = 0;
	virtual void LimitDate(int y,int m,int d) = 0;
	virtual UDP_SHORT CheckSum(BYTE* pData,int len) = 0;
	virtual long GetUdxBuffCount() = 0;
	virtual void GetAddrString(char* addrbuff,SOCKADDR* pAddr) = 0;
	virtual void SetThreadName(char* szName) = 0;
	virtual void GetHostIPAddr(char* szHost,unsigned short port,SOCKADDR*pDesAddr,BOOL bSelfIPv4 ) = 0;
	virtual void GetBuildString(char* strVer,int len) = 0;
	virtual void UdxSleep(int ms ) = 0;
	virtual void DBGStr(const char* szInfo,...) = 0;
	virtual char* GetBuffSizeInfo() = 0; 

};

#define UDXCHANNELCOUNT	2	//ͨ������
#define MSGID	0			//��Ϣͨ��
#define DATAID	1			//����ͨ��
#define UDXFILECHANNEL		65530//UDX�ļ�ͨ��

class IUdxInfo									//udx��ǰ��Ϣ���󲿷���ϢΪ��ͨ����Ϣ
{
public:
	UINT64 m_dwRead;								//��ǰ���յ������ݳ���,�Ѿ�ȷ�ϵ�
	UINT64 m_dwWrite;							//��ǰ�ӷ��͵����ݳ���,�Ѿ�ȷ�ϵ�
	UINT64 m_ReadCount;							//��ǰ���յ��İ���,�Ѿ�ȷ�ϵ�
	UINT64 m_WriteCount;							//��ǰ�ӷ��͵İ���,�Ѿ�ȷ�ϵ�
	UINT64 m_SendTotalCount;						//�ܹ����͵��ܰ���,�����ش�����
	UINT64 m_ReSendCount;						//�����ش��İ���

	UINT64 m_dwDumpCount;						//�յ����ذ���
	UINT64 m_dwOutRange;							//�յ���,���ڽ��մ����еİ���
	DWORD m_start;						//��ǰ��ʼʱ��
	DWORD s1,e1,s2,e2;				//��ǰ�շ�����ʼ���,����ǰ�������еĴ�����������
	DWORD m_ackcount;							//�յ���ACK����
	UINT64 m_currentspeedread;					//��ǰ�����ٶ�,�ֽ�/��,�Ѿ�ȷ�ϵ�
	UINT64 m_currentspeedsend;					//��ǰ�����ٶ�,�ֽ�/��,�Ѿ�ȷ�ϵ�
	DWORD m_lastUpdateTime;						//�ϴθ���udxinfoʱ�� 
	
	int m_ttl;									//��ǰ������ʱ��
	int m_minttl;								//�����ֵ���СRTT
	int m_SecSendSize;							//ÿ��ͳ�����ڷ��͵ĳ���
	int m_SecReSendSize;						//ÿ��ͳ�������ط������ݳ���
	
	UINT64 m_SendBewControl;						//ÿ��ͳ�����ڷ��͵��ٶ�
	UINT64 m_WillBeSendSize;						//��ʹ��Ҫ���͵��ٶȣ�����

	int m_sendsyncount;							//���͵�ͬ��������
	int m_readsyncount;							//���յ���ͬ��������

	UINT64 m_SendBuffCount[UDXCHANNELCOUNT];		//�ɹ�����sendbuff�Ĵ���
	UINT64 m_WriteBuffCount[UDXCHANNELCOUNT];	//���ͳɹ��Ĵ���
	UINT64 m_ReadBuffCount[UDXCHANNELCOUNT];		//���յ���sendbuff�����Ľ��հ�����
	UINT64 m_FecDecoderCount;		//���յ���sendbuff�����Ľ��հ�����
	
	virtual void GetSpeedStr(char * buff,BOOL bSend = TRUE,BOOL bCurrent = FALSE)=0;			//�õ�ʵʱ/ƽ���ٶ�,�ַ���
	virtual DWORD GetCurrentSpeed(BOOL bSend = TRUE)=0;											//�õ���ǰ�ٶ�
	virtual DWORD GetSpeed(BOOL bSend = TRUE)=0;												//�õ�ƽ���ٶ�
	virtual char* GetInfo()=0;																	//�õ��ַ���,��ǰ������Ϣ
	virtual void Reset()=0;																		//���¼�ʱ
	virtual void UpDateCurrentSpeed()=0;														//ˢ�¸�����Ϣ
	virtual float GetLostRate() = 0;															//��ǰ������
	virtual float GetLostRate2() = 0;															//ʵʱ������
	virtual DWORD GetLastAvgSendSpeed() = 0;
	
	//��ע:
	//�����ӽ����Ժ�,���ֲ��������Զ���UDX�ڲ�ȥ���ϸ���,����,Ӧ�ò�Ҳ���Ե���reset�������¼���,���ǵ���RESET������
	//��UDX�ڲ�����,ֻ����ΪӦ�ò�Ĳο�����.
}UDXPACKED;


struct IUdxCfg									//����UDX��һЩ����
{
	int mode;//����Fastudx.cfg.mode=1;��ʾ���������ɵ�UDXTCP����CPY ȫ�����ã�����Ĭ��������
	int maxdatabuffwnd[2];						// 
	int submss;									//��ǰ���ӵ�MSS,ĿǰĬ��Ϊ1024�����Ϊ1400��һ������²���Ҫ�������ֵ��
	int maxlostrate;							//��󶪰��ʣ�default(350/1000==35% ),���뷶Χ(1~1000)
	int expectbew;					//�̶�������B/�룩��
	int maxsendbew;					//���������������(B/S)
	int minsendbew;					//�����������
	int gamemode;			//����������
	int mergeframe;					//�Ƿ�ϲ�������

	int brokenframe;				//����

	int fastmode;					//����
	int fixbew;						//����
	int filetransmode;				//����
	int delaytosend;				//����

	int segmentspace;				//ʧ������Ĭ����3����1~5)���������޸�

	int maxackcheckcount;			//����

	int maxlocalackchecktime;		//����
	int maxremoteackchecktime;		//����
}UDXPACKED;

class IUdxLogSink
{
public: 
	virtual void Log(char* str) = 0;//�ڲ�UDXд��־����Ϣ��ͨ������ӿڵ�����Ӧ�ò���Դ����������дLOG
};

struct IUdxGlobalCfg
{
	IUdxGlobalCfg(){memset(this,0,sizeof(IUdxGlobalCfg));};
	int bInit;
	int mastver;
	int slaverver;
	int udxclock;				//udx�ڲ�ʱ��,Ĭ��25ms
	int udxcheckacktimer;		//udx�ڲ�ack�ذ�Ƶ��,Ĭ��35����
	int udxmintimeout;			//udx�ڲ���С��ʱ300ms
	int udxmaxtimeout;			//udx�ڲ����ʱ10000ms
	int udxackcount;			//���ٸ�����Ӧһ��ACK
	int udxdebug;
	DWORD maxsendbew;			//ȫ���ϴ��������������İ�
	char ext[10];
	IUdxLogSink* pLog;
	int bDisableLog;
}UDXPACKED;

struct UdxConnectInfo
{
	UDP_SHORT linktype;
	UDP_SHORT linkindex;
	UDP_BYTE rtpmode:1;
	UDP_BYTE linksubtype:7;
	UDP_BYTE internaltype:4;//�ڲ���������
	UDP_BYTE notused1:4;
	UDP_BYTE notused2;
	UDP_BYTE notused3;
	UDP_BYTE notused4;
}UDXPACKED;

#define P2PIDLEN	64

class IUdxBuff;
struct Udx_P2p_TS_Info
{
	int bCaller;
	UDP_SHORT p2pindex;
	UdxConnectInfo coninfo;
	char self[P2PIDLEN];			//�û�1,һ�����Լ����û�ID����
	char des[P2PIDLEN];			//�û�2���Է���ID,����
	char dessn[P2PIDLEN];			//�û�2���Է���ID
	char p2pserver[P2PIDLEN];		//p2p������IP
	char tsserver[P2PIDLEN];		//TS������IP
	UDP_SHORT p2pport;		//
	UDP_SHORT tsport;		//
	UINT64 userdata;
	IUdxBuff* pInitData;
}UDXPACKED;

class IUdxUnkownPackSink		//���ڷ�UDX��UDP��������������ص��󣬻�ص�����Щ������Ӧ�ô���
{
public:
	virtual void OnUnkownData(SOCKADDR * pAddr,BYTE* pData,long len){};
	virtual void OnThreadExit(){};
};

class IWaitEvent				//UDXͨ���Ƿ�ɷ������¼�֪ͨ
{
public:
	virtual int Wait(DWORD ms) = 0;
	virtual void SetEvent() = 0;
};


struct FileInfo
{
	UINT64 len;
	char name[256];
	UDP_BYTE context1[10];
	UDP_BYTE context2[10];
	UDP_BYTE context3[10];
}UDXPACKED;


class IUdxFSink					//�ļ��ص��ӿ�
{
public:
	//��Զ�����µ��ļ����������¼�
	virtual int OnNewFile(FileInfo * pInfo,BOOL bContinued){return bContinued + 1;};//1 save new file ,2 continue,else cancel
	//�����շ�ͬ�⣬���俪ʼ����Դ��䷽
	virtual void OnTransFileBegin(char* filename,BOOL bSend){} ;
	//Զ��ȡ��Ϣ����
	virtual int OnRemoteCancel(BOOL bSend){return 0;} ;
	//�ļ��������
	virtual void FileTransmitDone(char* filename,BOOL bSend){};//bSend = falseʱΪ���գ����յ����¼�ʱ����ʾ�ļ�������ɣ���������ɾ����UDX����
	//���������ʱ���ᷢ��һ��֪ͨ�����ͷ����������ͷ���FileTransmitDone��Ϣ������Ĺص�����UDX,�ᵼ�·��ͷ��ղ�����������¼���
	//���ԣ����ļ�����ʱ��Ӧ�õ����ͷ��յ�FileTransmitDone�¼�ʱ�ٹص�UDX�����Ա�֤���߶������յ����¼�������֤�ļ���������
	
	//�ļ����ݷ���������
	virtual void OnFileContinue(UINT64 startpoint,BOOL bSend){};
	//�ļ����ݵ�������
	virtual void OnFileReadByts(DWORD dwSize){};
	//�ļ����ݷ��Ͷ���
	virtual void OnFileWriteByts(DWORD dwSize){};
	
	//�ṩ���ܽӿ�
	virtual void OnEncoderByts(BYTE*pData,DWORD dwSize){};
	
	//�ṩ���ܽӿ�
	virtual void OnDecoderByts(BYTE*pData,DWORD dwSize){};

	//���շ���һ��ͬ���ļ�������1����ʾǿ�����´� ��������ʾ��������, ����������̾ͻ�ȡ��ǰ10����10���м�10���ֽڣ�����������ȶԣ�������ͬ����Ϊ��ͬһ���ļ����������سɹ�
	virtual int OnCheckSameNameFile(FileInfo * pInfo){return 0;} ;

	//������Ϣ
	virtual void OnTransFileErro(int errocode){};

	virtual void OnCancelAck(BOOL bSend){};//��ʾ�Է��ɹ�Ӧ�����cancel����

	virtual int OnReciveNewFileRequest(FileInfo * pInfo){return 1;};//���ط�1����ʾ�ܾ�
};

class IUdxFileTransmitor 
{
public:
	//�õ���ǰ�շ��˰ٷֱ�
	virtual float GetPercent(BOOL bSend) = 0;
	//�����ļ�
	virtual int SendFile(char* filename) = 0;
	//�����Ƿ����,�����շ�������ʱ����������ɾ��UDX���󣬱�֤�ڷ��ͷ�����ɾ��UDX����
	virtual BOOL IsDone(BOOL bSend) = 0;
	//���ñ����ļ�·��Ŀ¼
	virtual void SetSaveFileDir(char* savedir) = 0;
	//���ñ����ļ���������·��
	virtual void SetSaveFileName(char* savename) = 0;
	//�����ļ��¼��ص��ӿ�
	virtual void SetFSink(IUdxFSink * pSink) = 0;
	//ȡ�����ͻ����ȡ�����ͻ����
	virtual void Cancel(BOOL bSend) = 0;
	//�õ��򿪵��ļ����ܳ���
	virtual UINT64 GetTotalSendfileLen() = 0;
	virtual UINT64 GetTotalReadfileLen() = 0;	
	//���öϵ������ȣ����lBpС��1024�ֽڣ�����൱��lBp = 1024.Ĭ����2M��ÿ2M����дһ���ļ�
	virtual void SetBPLength(long lBp) = 0;
	//�õ�BP����
	virtual long GetBPLength() = 0;

	virtual char * GetSendFileName() = 0;
	virtual char * GetReadFileName() = 0;
	//�����ļ�
	virtual void SendFileW(wchar_t* filename) = 0;
	virtual void ResetState(BOOL bSend) = 0;//�����շ�״̬��bsend = true���ͣ���֮����״̬
};

class IUdxBuff;
class IUdxP2pSink
{
public:
	virtual void OnP2pFaild(char* user1,char*user2,INT64 userdata,UdxConnectInfo* pInfo ,IUdxBuff* pInitData){};
};
class IUdxP2pClient//P2P����ӿ�
{
public:
	virtual void SetNatServer(char*mip,long mport) = 0;
	virtual void SetTimeOut(DWORD ms = 30000) = 0;
	virtual BOOL ConnectServer(char* user1,char* user2,char* szDesID,UINT64 dwUser,BOOL bCaller,UdxConnectInfo* pInfo = NULL,IUdxBuff* pInitData = NULL) = 0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Clear() = 0;//�������֮ǰ���ӵ��û���Ҳ���Բ��ܣ��ڲ��ᶨʱ����
	virtual void SetSink(IUdxP2pSink*pSink) = 0;//����P2P �ص�ָ��
	virtual void SetCB(LPUDXP2PPRC pCB) = 0;//����P2P �ص�ָ��
};
#define UdxTrackData_Len	30

struct UdxTrackData
{
	UINT64 data[UdxTrackData_Len];
};


struct UdxFifoArrayBuffHead
{
	UDP_SHORT cmd;
	UDP_SHORT buffcount;
}UDXPACKED;


#ifdef WIN32
#pragma pack( pop)
#endif


class IMediaPush
{
public:
	//UDX��ģʽ��������Ƶ����������
	//ÿһ�����ݣ��� UDX������һ��UdxFrameType��ͷ�����ڶ��촦��������ʶ��
	virtual void SendFrame(UDP_LONG sid,UDP_SHORT sbid,BYTE* pData,int len,int type1/* AUDIOFRAME_A or VIDEOFRAME_I or VIDEOFRAME_P */,int type2,UDP_BYTE JumpFrameMode = 0) = 0;

	//��ŵר�з��ͽӿ�
	virtual void ZNSendFrame(UDP_LONG sid,UDP_SHORT sbid,Media_FrameInfo &FrameInfo) = 0;

	//������󻺳����Ƶ������������ӵ��ʱ���ܻ�������������û����Ը��ݣ��ɼ������� * maxcount = ��������ӳ�ʱ��
	virtual void SetAudioFrameMaxCount(int maxcount) = 0;

	virtual void SendFrames() = 0;
	//������������Ƶ���ݣ��ָ�����ʹ״̬����ʱ����ǿ�Ʊ���������I�죬���л�������Ƶ
	virtual void Reset() = 0;

	//ֻ����Ƶ
	virtual void OnlyAuido(BOOL bOnly) = 0;

};

class IUdxBuff;
class IUdxFifoList;
class IFastUdx;
class IUdxTcp : public IUdxFileTransmitor //==============    UDX �������ӽӿ�       ====================
{
public:
	virtual long AddLife() = 0;							//�������������ü�����������com��������������ڵڶ����߳��в���������ӣ������������
	virtual void Destroy() = 0;							//�Ͽ��������
	virtual BOOL IsConnected() = 0;						//�����Ƿ�����
	virtual BOOL IsFullBuffs(int ich) = 0;				//�����Ƿ��ܷ�������
	virtual void SetBuffWindow(int ich,DWORD size) = 0;	//���û����С�����ֽ�Ϊ��λ,���峤�����û�����SetFloatDataSize������
	virtual void SetMaxDataWindowSize(int ich,DWORD size) = 0;//���ô��ڴ�С���԰�����Ϊ��λ������Ϊ��8��16��32��64��...��8092~ ���8092*2����
	virtual BOOL SendBuff(BYTE* pData,int len) = 0;		//�����棬��ʾ��ָ�������Ѿ��ɹ�������UDX�����У����峤�����û�����SetFloatDataSize������
	virtual BOOL SendMsg(BYTE* pData,int len) = 0;		//������Ϣ
	virtual IUdxInfo* GetUdxInfo() = 0;					//�õ��ڲ�һЩ��Ϣ
	virtual IUdxCfg * GetUdxCfg() = 0;					//�������ӵģ����������
	virtual UDP_SHORT GetStreamID() = 0;				//���ص���ID
	virtual UDP_SHORT GetDesStreamID() = 0;				//���ӳɹ���Զ�˵ı�����ID
	virtual UINT64 GetUserData() = 0;					//�����ӹ������û����ݣ�������ָ�룬�Զ�������
	virtual void SetUserData(UINT64 dwUser) = 0; 
	virtual IWaitEvent* GetWaitEvent() = 0;				//���ӣ��������ݿɷ�ʱ���¼�����ָ��
	virtual SOCKADDR *GetRemoteAddr() = 0;				//���ӳɹ���Զ�˵�IP��Ϣ
	virtual int __DSendUdxBuff(SOCKADDR * pAddr ,BYTE* pData,int len) = 0;		//�����������ͷǿɿ�����
	virtual int __DSendUdxBuff2(SOCKADDR * pAddr ,BYTE* pData,int len) = 0;		//�����������ͷǿɿ����ݣ����ǻᴥ��
	virtual DWORD GetAppBuffAndUdxWndBuffSize() = 0;	//�õ���ǰ������udx�ڲ������ݳ��ȣ���Щ���ݻ�û�еõ�ȷ��
	virtual DWORD GetBuffWindow(int ich) = 0;			//�õ�Ӧ�ò����õĻ��峤�ȣ�����������ڲ������к��еĳ���
	virtual void SetTimeOut(int con,int hardbeat,int contimeout) = 0;		//���ó�ʱ���ֱ�Ϊ�����ӳ�ʱ����������������ӱ���ʱ�䣬��Ϊ��λ
	virtual UdxTrackData* GetUdxTrackData() = 0;		//�õ�����������ӹ�����ڴ����
	virtual void SetFloatDataSize(int floatdatasize) = 0;		//����Ӧ�û��峤��,���û������ʱΪ0��������Ĭ�ϻ��峤��8M��ֻ�������ͨ����Ч����Ϣͨ���������Ӱ��
	virtual INT64 GetFloatDataSize() = 0;					//�õ�֮ǰ���õĻ����С��
	virtual void Close(BOOL bDelay = FALSE) = 0;		//�������������������£���Ͽ����ӣ�����ʲôҲ������,���bdely = true,��Ὣ��û�з�����ɵ����ݣ�������ɺ�ر����ӣ����������ر�
	virtual long ReleaseLife() = 0;						//������addlife����ļ���
	virtual void DetectReadedBuffSize(long &readsize,long &writesize) = 0;	//�û���⣬��û�д���OnStreamwrite/OnStreamRead�¼��е�δ��������ݳ���
	virtual IMediaPush* GetMediaPush() = 0;				//�õ�push�ӿ�,�ô˽ӿ�����������Ƶ�죬���Է�ֹ����
	virtual IFastUdx * GetFastUdx() = 0;				//����IFastUdx����
	virtual BOOL IsTransLink() = 0;//�����Ƿ�Ϊ��ת����
	virtual SOCKADDR *GetTransServerAddr() = 0;//���ص�ǰ�ߵ���תIP
	virtual UDP_SHORT GetLinkType() = 0;//����ʱ��ͨ��UdxConnectInfoָ������������1
	virtual UDP_SHORT GetLinkIndex() = 0;//����ʱ��ͨ��UdxConnectInfoָ������������2
	virtual void EnableAutoAjustBuffs(BOOL bEnable) = 0;//��UDX�Զ��������ͻ��峤��
	virtual int GetLinkDirect() = 0;//1����ʾ���ӷ��𷽣�0��ʾ���ӽ��ܷ�
	virtual int GetUncheckedUserBuffCount(int ich) = 0;//���ض��ٸ�Ӧ�ò����û�б�����
	virtual BOOL PutLocalConnectInitData(BYTE* pData,int len) = 0;//���ñ������ӳ�ʼ������
	virtual IUdxBuff* GetRemoteConnectInitData() = 0;//�õ�Զ�̳�ʼ����������
	virtual IUdxBuff* GetLocalConnectInitData() = 0;//�õ��������ӳ�ʼ������
	virtual BOOL IsAllSendDone(int ch) = 0;//���е������Ƿ�����
	virtual void ClearNoSendData() = 0;//���Ŀǰ��û�б����͵����ݣ���UDX���������
	virtual void PostEvent(IUdxTcp *pDesTcp,int iEvent,UINT64 userdata) = 0;//���������ӷ���һ���Լ�����ִ�лص���pDesTcp��ص�OnPostEvent(IUdxTcp*src,int iEvent,UINT64 userdata);
	virtual void ChangeToRTPMode(BOOL bRTP,int sizemode) = 0;//����Ϣͨ���ĳ�FEC + RTPģʽ������������Ƶ���������������ӳ�,sizemode 0~6
	virtual BOOL SendBuffList(IUdxFifoList * pList) = 0;//sendbuff������ӿڣ�֧����������Ƭ���ݣ���������췢��
	virtual BOOL SendMsgList(IUdxFifoList * pList) = 0;		//sendmsg������ӿڣ�֧����������Ƭ���ݣ���������췢��
	virtual int WaitForClose() = 0;//�˺���Ϊ�������ã�����1��ʾ���Է��ɹ��յ��Ͽ���Ϣ��������ʾ��ʱ����,��ʱʱ��ĿǰΪ���500ms.
	virtual void DisableFec() = 0;//��ֹFEC
	virtual int BlockSendBuff(int ich,BYTE* pData,int len,int ms = 0) = 0;//�������ͣ�ֱ��������ɣ����ط��ͳ��ȣ����߷���-1����ʾ���ӶϿ�
	virtual int SetFecParam(int ch,int k,int n) = 0;//����FEC������
	virtual long GetSpendTime(BOOL bSend) = 0;//�����շ��ļ����ѵ�ʱ�䣬�����������ݽӿ�
	virtual BOOL LinkCpyRoute(IUdxTcp* pTcp,BOOL bAndClose) = 0;//����ת�е�ֱ��ģʽ���˽ӿڱ���Ҫ���ش��ڣ�һ��TS���Ӻ�ֱ������
	virtual UDP_SHORT P2pConnectTo(char* szDesSN,UdxConnectInfo * pConnectInfo) = 0;
	virtual SOCKADDR *Get3wAddr() = 0;
	virtual void DownloadP2pUserLists() = 0;
	virtual UDP_BYTE GetLinkSubType() = 0;//��ȡ��������Ϣ
	virtual UDP_BYTE GetLinkInternalType() = 0;//��ȡ��������Ϣ
	virtual int GetLinkLost() = 0;
};

//=======================================���׻����ļ�������==========================================//

//Close();//�Ͽ����ӣ����������仯���Է�����broken,���ز��ᴥ��broken
//
//WaitForClose();//�Ͽ����ӣ��������仯--���Է�����broken,���ز��ᴥ��broken���ȴ�1.5�룬�Է�������Ӧbroken
//
//Destroy();//�Ͽ����ӣ��������仯--���Է�����broken,���ز��ᴥ��broken
//
//ReleaseLife();//���仯--

//���ɣ�
// Q1 ���߳��У�����Ҵ�����TCP���󣬵�����AddLife
// �ر�ʱ �ҿ���
// 1.1 �ȵ���ReleaseLifeȻ�����Close��
// 1.2 �ȵ���Close Ȼ�����ReleaseLife
// 1.3 ֱ�ӵ���Destory��
// 
// Q2 ���߳������ �Ҵ�����TCP����û�е���AddLife
// �ر�ʱ ����destroy,�����ϸ����ؼ�������Ϊû�еڶ����̷߳���ͬһ������
// 
// Q3 ���߳��У�����븴��TCP����ô�м����̣߳���Ҫ����
// ����AddLife��������Ҫ����ͬ���߳��˳�ǰ���Ե���Destory ��
// ����ReleaseLife�����Ǳ�����һ���߳�����Ҫ���ùرռ���
//    Destory ���� Close + ReleaseLife

//==================================================================================================//

class IMultCardTcp;
class IUdxTcpSink
{
public:
	virtual void OnStreamPreConnect(SOCKADDR *pAddr,IUdxTcp * pTcp,UdxConnectInfo * pInfo){};	//��������ص��˽ӿڣ������ø������
	virtual void OnStreamConnect(IUdxTcp * pTcp,int erro){};
	virtual void OnFileStreamConnect(IUdxTcp * pTcp,int erro){};				//0,��ʾ�µ�һ���ļ�����Ự��1���Ự����
	virtual void OnStreamBroken(IUdxTcp * pTcp){};								//�Ͽ�
	virtual void OnStreamRead(IUdxTcp * pTcp,BYTE* pData,int len){};			//��
	virtual void OnStreamWrite(IUdxTcp * pTcp,BYTE* pData,int len){};			//д
	virtual void OnStreamMsgRead(IUdxTcp * pTcp,BYTE* pData,int len){};			//��Ϣ�Ķ�
	virtual void OnStreamMsgWrite(IUdxTcp * pTcp,BYTE* pData,int len){};		//��Ϣ��д
	virtual void OnStreamNeedMoreData(IUdxTcp *pTcp,int needdata){};			//���Է����µ�д,��needdata(<=0��ʾ���Է�����)�ֽڿռ乩���ͣ����һ���������ݱ�ȷ�Ϻ󴥷�
																				//����ص��е����������֪ͨ�����ֻ���а���ȷ�ϵ�֪ͨ�����ԣ�Ӧ�ò�������������ϵĽ���Ͷ��
																				//������Ҫ����������߳�����ɷ��͡���һ��sendbuff�����ͨ������¼����ϵ��ӷ��͡�
	virtual void OnUnSafeStreamRead(IUdxTcp * pTcp,BYTE*pData,int len){};		//�������ӵĲ��ɿ����ݣ�һ������������Ƶ

	virtual void OnInteranlThreadExit(){};										//�ڲ��߳��ͷ�ʱ��������һ�����java,com,jni��ʹ�ã������ͷ���Դ
	virtual void OnStreamLinkIdle(IUdxTcp *pTcp){};								//����·���֣�����Ӧ�ò�û�����ݿɷ�ʱ��
																				//���յ����������������Ĵ����ڣ��û����Դ�ӡ������Ϣ��֤������������һ�㲻����
	virtual void OnStreamChancetoFillBuff(IUdxTcp *pTcp){};						//UDX�ڲ������߳��ṩ���ᣬ���з�������,ÿ50MS�̶�Ƶ�ʵ���
	virtual void OnMediaPushFrameEvent(IUdxTcp * pTcp,UDP_LONG sid,UDP_SHORT sbid,int type,int framecount){};		//sid,������ʱ������SendFrameʧ��ʱ���ص�������ʵ�ʻ����˶���������,0������1��Ƶ��
	virtual void OnStreamFinalRelease(IUdxTcp * pTcp){};						//ÿ����������ͷ��¼������Դ���һЩ�����Ķ����ͷ�,��ͬ��OnStreamBrokenָ�յ��Ͽ���Ϣ�ͻ���ã�broken�¼����ǿ���(�������������releaselife)��ʹ�����OnStreamFinalRelease
																				//�����ڲ����ܻ��п������������˶�Ӧ�����ӵ���Ϣ�������������ͷŶ���������ͬ��������
																				//����ص���ÿһ�����ӵ�����ͷ���ڣ�������Ӧ�ò���������û�������ñ���(addlife)
	virtual void OnMultCardConnect(IMultCardTcp * pTcp,int erro,int linkcount){};
	virtual void OnMultCardBroken(IMultCardTcp * pTcp){};
	virtual void OnMultCardRead(IMultCardTcp * pTcp,BYTE*pData,int len){};
	virtual void OnLocalFastDestroy(IUdxTcp* pTcp){};//����������IFastUdx�ӿڶ����ǻص���Ӧ�ò㣬���ͷŶ�Ӧ��Դ
	virtual void OnFastUdxTimer(){};//udx��ʱ����ÿ50MS����������ʱ�����ܱ�����
	virtual void OnPostEvent(IUdxTcp*src,int iEvent,UINT64 userdata){};//��src������¼��������Ļص���userdata,Ϊ�Լ���ָ�������Լ���չ
	virtual void OnFastUdxFinalRelease(){};//��IFastUdx->Destory()�����ĵط������,�����ڻص��ͷ�sink����
	virtual void OnTcpCongestionNotify(IUdxTcp* pTcp,float lost,UINT64 speed,int rtt){};
	virtual char*OnGetServerP2pConfigJson(IUdxTcp* pSrc,IUdxTcp* pDes){return "{}";};//pSrc����P2P��pDes;
	virtual void OnP2pTsFaild(BYTE bCaller,UDP_SHORT p2pindex,char * szDesSn,UINT64 userdata,char* szErroMsg = NULL){};//P2PTS����ʧ��
	virtual void OnLoopClientsEvent(int type,IUdxBuff* pData,IUdxTcp* pTcp){};//��Ӧ������ѯ�¼�
	virtual void OnTsLinkChange(IUdxTcp* pTsTcp){};//TS����ת����P2P����
};

class IUdxTrans
{
public:
	virtual void OpenChannel(char*ip,UDP_SHORT port,char* strCName) = 0;		//��һ����תͨ��,ͨ�������õ��ڻ򳬹�25���ַ�
	virtual void CloseChannel(char*ip,UDP_SHORT port,char* strCName) = 0;		//�ص�һ����תͨ��
	virtual void CloseAllChannels() = 0;										//�ص����е���תͨ��
};

struct IFastPreCfg : public IUdxCfg//������һ��IUdxTcp�ӿ�ʱ��Ԥ�����õ�һЩ�������� 
{
};
class IUdxUdpIOBase
{
public:
	virtual int InputUdxData( struct sockaddr * from,BYTE* pData,int len) = 0;//���from��data,lenΪpData�ṩ�Ļ��峤��
	virtual int OutputUdxData( struct sockaddr * adrrto,BYTE* pData,int len) = 0;//���͵�ַ�������͵����ݼ�����
};


class IFastUdx//UDXʵ������ ==============    UDX ���Ķ���       ====================
{
public:
	virtual BOOL Create(char* ip = NULL,UDP_SHORT port = 0) = 0;//����udp socket,��ָ���˿ڰ���ɼ���
	virtual BOOL AddBinding(char* ip,UDP_SHORT port,char* szName) = 0;//��Ӷ�IPʱ����IP�İ���ɼ���
	virtual IUdxTcp* Connect(char* ip,UDP_SHORT port,BOOL bSync = FALSE,
		UINT64 dwUser = 0,UINT64 expectbew = 0,int lostrat = 100,
		char*strCName = NULL,UdxConnectInfo*pInfo = NULL,IUdxBuff * pInitBuff = NULL,BOOL bAutoRelase = TRUE) = 0;


	virtual	BOOL Attach(SOCKET s) = 0;											//���Ѿ����ڵ�UDP�׽���
	virtual int Dettach() = 0;
	virtual void Destroy() = 0;													//����UDX����
	virtual void SetUnkownPackSink(IUdxUnkownPackSink *pUnkownPackSink) = 0;	//���÷�UDX��UDP��ʱ�ص���
	virtual void SetSink(IUdxTcpSink * pSink) = 0;								//���û����¼��Ļص���
	virtual void SetServerBlockSize(int size) = 0;								//�����ڲ��������̴����߳��������磬�߼����������¼��ص��߳�����IO�߳�����
	virtual SOCKADDR *GetLocalAddr() = 0;										//�õ�Ĭ��UDX�˿�ռ����Ϣ
	virtual IUdxP2pClient* GetP2pClient() = 0;									//�õ�P2P�ӿ�
	virtual int __DSendUdxBuff(SOCKADDR * pAddr ,BYTE* pData,int len) = 0;		//ֱ����ָ���ĵ�ַ���ͷ�UDX ԭʼ���ݰ�
	virtual IUdxTrans* GetUdxTrans() = 0;										//�õ���ת����ӿ�
	virtual void SetUdpSendThreadCount(int count) = 0;							//�����ڲ�����UDP���߳���
	virtual void SetConnectTimeOut(int secs) = 0;								//���������ӳ�ʱ
	virtual void Enable_DONTFRAGMENT(BOOL bEanble) = 0;							//���õײ�UDP�Ƿ������Ƭ��Ĭ�ϲ������Ƭ
	virtual int GetClientsCount() = 0;											//�����ܵ������������������������ʵʱ��
	virtual IUdxCfg* GetPreCreateUdxTcpCfg() = 0;								//����һ��Ԥ�����õ�����
	virtual void SetCB(LPUDXPRC pcb) = 0;
	virtual IMultCardTcp* CreateMultCard() = 0;
	virtual void SetUserData(UINT64 dwUser) = 0;									//���ù������û�����ָ��
	virtual UINT64 GetUserData() = 0;											//��ȡ�������û�����ָ��
	virtual void LowCost() = 0;													//ȡС��������������udx���߳̿���������
	virtual int GetTransFromLinkCount() = 0;									//��ȡת����·��
	virtual void EnableTimer(BOOL bEnable) = 0;									//�򿪻�ر�udx���������timer
	virtual void SendUdpBrocast(BYTE* pData,int len) = 0;
	virtual void EnableUdpBrocast() = 0;
	virtual void SetDeviceID(char* szID) = 0;
	virtual void ThreadDestroy() = 0;											//�����߳̽��йرգ��ȹ��ܵ�ͬDestroy,��������������в���ɾ��sink,���ر���ɺ��ص�sink->OnFastUdxFinalRelease����������԰�ȫ�ͷŻص�����sink
	virtual void SetSocketWindowSize(int wtype,int wsize) = 0;					//wtype = 0 SENDBUFF, = 1 RECVBUFF,��СֵΪ1MB(1024*1024)�ֽ�
	virtual void SetSameSrcMaxCount(int maxcount = 5) = 0;						//����Դ��ַ��ͬ�����������
	virtual void EnableWriteEvent(BOOL bEnable) = 0;							//	����д�¼��ص������ڽ�ԼCPU,�ڴ�
	virtual BOOL IsIPv6() = 0;													//����Ĭ��ռ�õ�ַ�ǲ���ipv6
	virtual BOOL LinkCpyRoute(UDP_SHORT src,UDP_SHORT des,BOOL bAndClose) = 0;	//��ַ�л�
	virtual void P2PMsgConnectRegister(char* szMsgServerIP,UDP_SHORT port,Udx_P2p_TS_Info* pP2pInfo) = 0;//ע��P2P�û�
	virtual void PostP2pRequest(Udx_P2p_TS_Info* pP2pInfo) = 0;					//����P2P����
	virtual void SetUdxUdpBase(IUdxUdpIOBase* pIOBase) = 0;						//����UDP�շ�ԭʼ�ӿ�
	virtual void PostLoopClientsEvent(int type,IUdxBuff* pData) = 0;			//Ͷ��һ���ͻ�����ѯ
	virtual void EnableFileTransmit(BOOL bEnable) = 0;
};

class IMultCardTcp																//������� �󶨺�ͬʱΪһ�����������ݣ����������
{
public:
	virtual BOOL AddBinding(int index,char* ip,UDP_SHORT port) = 0;				//���Ӱ�IP
	virtual BOOL Connect(char*ip,UDP_SHORT port) = 0;							//ͨ��ָ����IP���ӶԷ�IP + port
	virtual void Close() = 0;													//�Ͽ�����
	virtual void Destroy() = 0;
	virtual BOOL SendBuff(BYTE* pData,int len) = 0;
	virtual void AddLife() = 0;
	virtual BOOL IsConnected() = 0;
	virtual UDP_SHORT GetMultCardID() = 0;										//ȡ�ñ����ӵ�ID��
	virtual UDP_SHORT GetMultCardDesID() = 0;									//ȡ�ñ����ӵĶԶ�ID��
	virtual void SetFloatSize(int floatsize ) = 0;								//���û�����
	virtual BOOL GetRemoteIPList(char* pList,int &bufflen) = 0;					//��IP:PORT�ո� ip-port,����false��ʾ���岻����bufflen������Ҫ�ĳ���,�ո�ָ�
	virtual BOOL GetLocalIPList(char* pList,int &bufflen) = 0;					// ip-port,����false��ʾ���岻����bufflen������Ҫ�ĳ���,�ո�ָ�
	virtual IWaitEvent* GetWaitEvent() = 0;
};


class IUdxLock//Ϊ���ڱ�д��ƽ̨����ʱ���ṩ����
{
public:
	virtual void Lock() = 0;
	virtual void Unlock() = 0;
	virtual void Destroy() = 0;
};

class IUdxEvent //�¼�����
{
public:
	virtual void SetEvent() = 0;
	virtual void ResetEvent() = 0;
	virtual BOOL Wait(int ms) = 0;
	virtual void Destroy() = 0;
};

class IUdxBuff
{
public:
	virtual BYTE* ChangePoint(int iLen,int bNoCpy = 1) = 0;									//��̬��չ�����С
	virtual BYTE* GetBuff(void) = 0;											//ȡ�û���ͷָ��
	virtual int GetLen(void) = 0;												//���ػ���ʵ��ʹ�ó���
	virtual int GetMaxLen(void) = 0;											//������󻺳峤��
	virtual void Zero() = 0;													//��0
	virtual void FreeMem() = 0;													//�ͷ��ڴ�
	virtual void Reset() = 0;													//��0������ʹ�ó�����0
	virtual void Bind(BYTE* pData,int len) = 0;									//��ָ���ڴ�copy����������
	virtual BOOL Pop(BYTE* pData,int len) = 0;									//��ָ��ͷ������ָ������len�����ݣ�����cpy��pData�У�ԭ���峤�Ȼ����len
	virtual void AppendBuff(BYTE* pData,int iLen) = 0;							//׷��һ���ֻ���
	virtual void Destroy() = 0;													//�ͷ��Լ�
	virtual long AddLife() = 0;													//�������ü���
	virtual BOOL Drop(int left,int len) = 0;									//�����������ݣ�����߻����ұ�
	virtual void ExternDataPoint(BYTE* pData,int len) = 0;								//������չ����
	virtual void GetExternDataPoint(BYTE* pData,int len) = 0;								//��ȡ��չ����ָ��
	virtual void InitPtSize(int size) = 0;
	virtual void SetPoint(int index,void* pt) = 0;
	virtual void* GetPoint(int index) = 0;
	virtual SOCKADDR* GetFrom() = 0;

};

class IUdxFifoList //�Ƚ��ȳ�����
{
public:
	virtual void AddBuff(IUdxBuff * pBuff) = 0;									//����һ��buff����
	virtual IUdxBuff* GetBuff() = 0;											//ȡ��һ��������ibuff����
	virtual void AddBuff(BYTE * pData,int len) = 0;								//ѹ��ָ���ĳ�������
	virtual void GetBuff(BYTE** ppData,int &len) = 0;							//ȡ����ǰһ��������buff����
	virtual void FreeBuff(BYTE* pData) = 0;										//�ͷ���getbuff(BYTE**)ָ����ָ�ڴ�
	virtual int GetBuff(BYTE* pData,int len) = 0;								//����ָ�ȳ��ȵĻ������pData,ԭ�����������len
	virtual int GetBuffSize() = 0;												//����list�е������ܳ���
	virtual int GetBuffCount() = 0;												//����list��IBuff������
	virtual void EnableEvent(BOOL bEnable) = 0;									//�Ƿ����¼�����
	virtual BOOL Wait(int ms) = 0;												//�����¼������󣬵��������ݼ���ʱ���ᴥ���¼�
	virtual void Clear() = 0;													//�����������
	virtual void Destroy() = 0;													//�ͷ��Լ�
	virtual void SetWaitEvent(IUdxEvent* pEvent) = 0;							//�ؽӽ����¼�
	virtual IUdxBuff* BuildOneBuff(UDP_SHORT cmd) = 0;								//����һ�����
	virtual void Attach(BYTE* pData,int len) = 0;								//������
	virtual UDP_SHORT GetCMD() = 0;
	virtual IUdxBuff* TryGetBuff() = 0;											//����ȡ��һ��������ibuff����
	virtual void PopFrontBuff() = 0;											//�ͷŵ�һ��buff
	virtual void PopFrontBuffCount(int count) = 0;								//�ͷŶ�ǰN��BUFF
};

class IUdxTime //ʱ��tick
{
public:
	virtual UUDX_LONG GetTickCount() = 0;
	virtual void Destroy() = 0;
	virtual UINT64 GetUSTickCount() = 0;
};

class IUdxThreadSink //�̻߳ص�
{
public:
	virtual void UdxRun(){};
	virtual void FreeSelf(){};
};
class IUdxThread  //�߳̽ӿ�
{
public:
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void SetCB(IUdxThreadSink* pSink) = 0;								//�����̻߳ص��࣬�������ʵ��UdxRun()
	virtual void Destroy() = 0;
	virtual void StartEx(int stacksize,char* szThName) = 0;										//stacksize = 0��ͬstart()
	virtual BOOL IsAllExit() = 0;
	virtual void AutoRelease(BOOL bAutoRelease) = 0;
};

class IUdxFile  //�ļ������ӿ�
{
public:
	virtual BOOL OpenFile(char* strFile,BOOL app = FALSE) = 0;					//���Ѿ����ڵ��ļ�
	virtual BOOL OpenFileW(wchar_t* strFile,BOOL app = FALSE) = 0;
	virtual BOOL CreateFile(char* strFile) = 0;									//�����ļ�
	virtual void Close(void) = 0;												//�ر�
	virtual BOOL IsOpen(void) = 0;												//�ļ��Ƿ��Ѿ�����
	virtual UINT64 GetFileLength() = 0;											//�����ļ�����
	virtual UINT64 Write(BYTE* pData, int len) = 0;								//д���ļ�
	virtual UINT64 Read(BYTE* pData, int len) = 0;								//���ļ���������������ĳ���
	virtual void Seek(int type = 1) = 0;										//seek��ͷ0����β1
	virtual void SeekTo(int type,UINT64 len) = 0;								//type 0��ͷ��ʼ��1β��ʼ len����Ϊ��ֵ���Ƿ�����
	virtual void Destroy() = 0;													//�ͷ��Լ������ص��ļ�
};

class IUdxRef
{
public:
	virtual long AddRef() = 0;
	virtual long Release() = 0;//�������û�ʧ��
	virtual long Add(long v) = 0;
};

class IUdxBuffPool
{
public:
	virtual IUdxBuff* GetNewBuff(int datalen) = 0;
	virtual void CheckPool() = 0;
	virtual void Destroy() = 0;												
};

class IUdxPing
{
public:
	virtual BOOL Ping(char* szHost,UDP_SHORT port) = 0;
	virtual void SetTimeOut(int ms) = 0;
	virtual BOOL IsIPV6() = 0;
	virtual void Destroy() = 0;
	virtual int GetPingValue() = 0;
};

//UDX ���׹㲥������
class IUdxSimpleBroacastServer
{
public:
	virtual BOOL Init(UDP_SHORT loalport,UDP_SHORT desport) = 0;//�󶨱��ض˿�
	virtual IUdxBuff* Recv(int ms = 10) = 0;//���ձ��˵Ĺ㲥��ͨ������ֵ->GetFrom�õ���ַ
	virtual int Send(SOCKADDR * pDesAddr,BYTE* pData,int len) = 0;//�����ط���Ϣ
	virtual int Broacast(BYTE* pData,int len) = 0;//Ⱥ����Ϣ
	virtual int GetClientsCount() = 0;//���ؿ��Թ㲥������
	virtual int GetClientIPs(char* ips,int bufflen) = 0;//��;'�ָ�IP
	virtual void Destroy() = 0;
};

//UDX�㲥������
class IUdxSimpleBroacastClient
{
public:
	virtual BOOL Init(UDP_SHORT loalport) = 0;//�󶨱��ض˿�
	virtual IUdxBuff* Recv(int ms = 10) = 0;//���ձ��˵Ĺ㲥
	virtual int Send(BYTE* pData,int len) = 0;//�ط����㲥����Ϣ
	virtual void Destroy() = 0;
};




class UdxTcpPtHelper
{
public:
	UdxTcpPtHelper(IUdxTcp* pTcp){_pTcp = pTcp;};
	virtual ~UdxTcpPtHelper(){if(_pTcp)_pTcp->ReleaseLife();};
protected:
	IUdxTcp* _pTcp;
};
class UdxBuffPtHelper
{
public:
	UdxBuffPtHelper(IUdxBuff* pBuff){_pBuff = pBuff;};
	virtual ~UdxBuffPtHelper(){if(_pBuff)_pBuff->Destroy();};
protected:
	IUdxBuff* _pBuff;
};
class UdxListPtHelper
{
public:
	UdxListPtHelper(IUdxFifoList* pList){_pList = pList;};
	virtual ~UdxListPtHelper(){if(_pList)_pList->Destroy();};
protected:
	IUdxFifoList* _pList;
};
class UdxLockHelper
{
public:
	UdxLockHelper(IUdxLock* pLock){_pLock = pLock;pLock->Lock();};
	virtual ~UdxLockHelper(){_pLock->Unlock();};
protected:
	IUdxLock* _pLock;
};


IUdxGlobalCfg* GetUdxGlobalCfg();		//UDX��ȫ�ֱ����ӿڣ���������һЩȫ�ֲ���
IFastUdx* CreateFastUdx();				//����һ��UDX����
IUdxTools* GetUdxTools();				//UDX�ṩ�ĸ������ߣ�һ���ò���
IUdxLock* CreateUdxLock();				//����һ����
IUdxEvent* CreateUdxEvent();			//�����¼�
IUdxFifoList* CreateUdxList();			//����һ���Ƚ��ȳ�����
IUdxTime* CreateUdxTime();				//����tick����
IUdxThread* CreateUdxThread();			//�����̶߳���
IUdxFile* CreateUdxFile();				//����udx�ļ�����
IUdxBuff * CreateUdxBuff(int size);		//����һ��buff����
IUdxRef * CreateUdxRef();				//����һ�����ü�������
IUdxBuffPool * CreateUdxBuffPool();		//����һ��buff��	
IUdxPing * CreateUdxPing();				//ping udx����
IUdxSimpleBroacastServer * CreateUdxSimpleBroacastServer();	//�㲥����			
IUdxSimpleBroacastClient * CreateUdxSimpleBroacastClient();	//�㲥�ͻ���


#endif
