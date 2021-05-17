#include "pch.h"
#include "UdxTcpSink_P2p.h"
#include <iostream>

UdxTcpSink_P2p::UdxTcpSink_P2p() {
    m_pFastUdx = NULL;
	m_bShutdown = FALSE;
	m_pTcpData = NULL;
	m_pTcpRegister = NULL;
	listener = NULL;
	m_port = 0;
	m_pLock = CreateUdxLock();
}

UdxTcpSink_P2p::~UdxTcpSink_P2p()
{
	shutdownloop();

    unInitUdx();

	m_pLock->Destroy();
}


void UdxTcpSink_P2p::SetStreamReadListener(onStreamRead mlistener)
{
	this->listener = mlistener;
}

void UdxTcpSink_P2p::SendFrame(int bvideo,int bkey,BYTE* pData,int len)
{
	{
		UdxLockHelper cs(m_pLock);
		if(!m_pTcpData)
		{
			return;
		}
	}


	if(bvideo)
	{
		if(bkey)
			m_pTcpData->GetMediaPush()->SendFrame(0,0,pData,len,VIDEOFRAME_I,0,0);
		else
			m_pTcpData->GetMediaPush()->SendFrame(0,0,pData,len,VIDEOFRAME_P,0,0);
	}else
	{
		m_pTcpData->GetMediaPush()->SendFrame(0,0,pData,len,AUDIOFRAME_A,0,0);
	}

}


int UdxTcpSink_P2p::P2pConnectDevice(char* szDeviceName)
{
	UdxLockHelper cs(m_pLock);
	if(!m_pTcpRegister)
	{
		GetUdxTools()->DBGStr("P2pConnectDevice === %s failed====\n",szDeviceName);
		return -1;
	}

	m_pTcpRegister->P2pConnectTo(szDeviceName,NULL);

	return 1;

}

void UdxTcpSink_P2p::OnStreamRead(IUdxTcp* pTcp, BYTE* pData, int len)
{
	GetUdxTools()->DBGStr("------------------------------------------\n");
	GetUdxTools()->DBGStr("get udx data size %d\n", len);
	GetUdxTools()->DBGStr("------------------------------------------\n");
	if(pTcp->GetLinkInternalType() == UDX_P2P_REGISTER_MSG_LINK_FLAG)
		return;
	if (len < sizeof(UdxFrameType))
		return;

	GetUdxTools()->DBGStr("-------------start call----------------- %p\n", this->listener);
	UdxFrameType* pFrame = (UdxFrameType*)pData;

	BYTE* pRealData = pData + sizeof(UdxFrameType);
	int reallen = len - sizeof(UdxFrameType);

	pFrame->sid = ntohl(pFrame->sid);
	pFrame->sbid = ntohs(pFrame->sbid);
	(*this->listener)((char*)pData, len, pFrame->type1);
	GetUdxTools()->DBGStr("-------------end call----------------- \n");
	return;
}

void UdxTcpSink_P2p::OnStreamMsgRead(IUdxTcp* pTcp, BYTE* pData, int len)
{
    OnStreamRead(pTcp, pData, len);
}

void UdxTcpSink_P2p::OnStreamConnect(IUdxTcp* pTcp, int erro)
{
    if (pTcp->GetLinkInternalType() == UDX_P2P_REGISTER_MSG_LINK_FLAG)
	{
        if (erro != 0)
		{ // 连接IDM失败
            GetUdxTools()->DBGStr("regist to idm server failed\n");
            this->unInitUdx();

			initUdx();
			Register((char*)m_server.c_str(),m_port,(char*)m_name.c_str());

        } else 
		{ // 连接IDM成功
            GetUdxTools()->DBGStr("==========================================\n");
            GetUdxTools()->DBGStr("regist to idm server succeeded\n");
            GetUdxTools()->DBGStr("==========================================\n");

			m_pLock->Lock();
			if (m_pTcpRegister)
			{
				m_pTcpRegister->Destroy();
			}
			m_pTcpRegister = pTcp;
			pTcp->AddLife();

			m_pLock->Unlock();

        }
    } else
	{
        if (erro != 0)
            return;

		m_pLock->Lock();

		if(m_pTcpData)
		{
			m_pTcpData->Destroy();
		}

		m_pTcpData = pTcp;
		pTcp->AddLife();

		m_pLock->Unlock();

        GetUdxTools()->DBGStr("udx client connect succeeded\n");
    }
}

void UdxTcpSink_P2p::OnStreamBroken(IUdxTcp* pTcp) {
    if (pTcp->GetLinkInternalType() == UDX_P2P_REGISTER_MSG_LINK_FLAG) {
        GetUdxTools()->DBGStr("==========================================\n");
        GetUdxTools()->DBGStr("udx idm server disconnected\n");
        GetUdxTools()->DBGStr("==========================================\n");
        this->unInitUdx(); // 再次发起连接

		initUdx();
		Register((char*)m_server.c_str(),m_port,(char*)m_name.c_str());

    } else {
        GetUdxTools()->DBGStr("==========================================\n");
        GetUdxTools()->DBGStr("udx client disconnected\n");
        GetUdxTools()->DBGStr("==========================================\n");
    }
}

void UdxTcpSink_P2p::OnMediaPushFrameEvent(IUdxTcp* pTcp, UDP_LONG sid, UDP_SHORT sbid, int type, int framecount) {
    GetUdxTools()->DBGStr("OnMediaPushFrameEvent callback, type=%d,frameCount=%d\n", type, framecount);
}


void UdxTcpSink_P2p::OnFastUdxFinalRelease()
{
	if(m_bShutdown)
		return;
	initUdx();
	Register((char*)m_server.c_str(),m_port,(char*)m_name.c_str());
}

void UdxTcpSink_P2p::initUdx() {

	m_pFastUdx = CreateFastUdx();
	m_pFastUdx->SetSink(this);
	m_pFastUdx->Create(NULL, (UDP_SHORT)0);
}

void UdxTcpSink_P2p::unInitUdx() 
{
    if (m_pFastUdx != NULL) 
	{
		if(m_pTcpData)
		{
			m_pTcpData->Destroy();
			m_pTcpData = NULL;
		}
		if(m_pTcpRegister)
		{
			m_pTcpRegister->Destroy();
			m_pTcpRegister = NULL;
		}

		IFastUdx* pTemp = m_pFastUdx;
		m_pFastUdx = NULL;


        pTemp->ThreadDestroy();
    }
}

void UdxTcpSink_P2p::Register(char* ip,int port,char*szName) 
{

	if(m_bShutdown)
		return;

	m_server = ip;
	m_port = port;
	m_name = szName;


    Udx_P2p_TS_Info info;
    memset(&info, 0, sizeof(info));

	strcpy_s(info.self,szName);
	strcpy_s(info.des, "");
	strcpy_s(info.dessn, "");

	strcpy_s(info.p2pserver, ip);
    info.p2pport = port;
	strcpy_s(info.tsserver, ip);
    info.tsport = port;

    GetUdxTools()->DBGStr("==========================================\n");
    GetUdxTools()->DBGStr("try to connect to idm server\n");
    GetUdxTools()->DBGStr("==========================================\n");

    m_pFastUdx->P2PMsgConnectRegister((char*)ip, port, &info);
}

void UdxTcpSink_P2p::shutdownloop()
{
	m_bShutdown = TRUE;
}
