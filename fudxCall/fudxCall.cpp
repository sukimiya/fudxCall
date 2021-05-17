// fudxCall.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "fudxCall.h"

onConnected _connectedListener;
onStreamRead _streamReadListener;

FUDXCALL_API void delegate(onConnected connectedListener, onStreamRead streamReadListener)
{
    _connectedListener = connectedListener;
    _streamReadListener = streamReadListener;
}

FUDXCALL_API void registServer(char* server, int port, char* name) {
    udxTcpSink_P2p.initUdx();
    udxTcpSink_P2p.Register(server, port, name);
    if (_connectedListener != NULL) {
        (*_connectedListener)(0);
    }
    if (_streamReadListener != NULL) {
        udxTcpSink_P2p.SetStreamReadListener(_streamReadListener);
    }
}

FUDXCALL_API void connectDevice(char* name)
{
    udxTcpSink_P2p.P2pConnectDevice(name);
}

