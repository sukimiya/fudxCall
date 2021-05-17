#ifndef _udx_typedef_h_
#define _udx_typedef_h_

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


#define AUDIOFRAME_A	0//��Ƶ֡
#define VIDEOFRAME_I	1//I֡
#define VIDEOFRAME_P	2//P֡
#define DATAFRAME_I		3//����֡

enum Video_Code_Type
{
	Video_Code_264,
		Video_Code_265
};

enum Audio_Code_Type
{
	Audio_Code_AAC,
	Audio_Code_OPUS,
	Audio_Code_ILBC,
	Audio_Code_G711,
	Audio_Code_G711A,
	Audio_Code_G711U,
	Audio_Code_G721
};


struct FrameType
{
	unsigned char type0:1;//����MTS��IDM
	unsigned char type1:2;//����Ƶ������
	unsigned char type2:3;//�����ͣ�type2 = FTypeVer_1ʱ֡ͷ���FrameType2
	unsigned char modestream:1;//�Ƿ�����ʽ����
	unsigned char noused0:1;
	unsigned int  sid;//��ID
	unsigned short sbid;//����ID,short����
	unsigned char jumpmode;//��������,//level 0.vIframe 1.1/2  2.1/4 3.1/6 4.1/8
}UDXPACKED;


#define MD_VIFRAME 0x10
#define MD_VPFRAME0	0x20
#define MD_VPFRAME1	0x40

//����ģʽ
#define MD_1_2	0x1
#define MD_1_4	0x2
#define MD_1_6	0x4
#define MD_1_8	0x8


//������
#define ZN_IFRAME	VIDEOFRAME_I//I֡
#define ZN_PFRAME	VIDEOFRAME_P//P֡
#define ZN_VIFRAME	VIDEOFRAME_I//����I֡
#define ZN_AFRAME	AUDIOFRAME_A//��Ƶ֡
#define ZN_DFRAME	DATAFRAME_I//����֡

struct AVFrameHead //��ţ��Ƶ֡ͷ
{
	unsigned char MN[2];//�̶���"MN"
	unsigned char Co;//��˾����
	unsigned char avframetype:4;//I,P,A������,����VIDEOFRAME_I,VIDEOFRAME_P
	unsigned char code:4;//����Ƶ����Video_Code_Type or Audio_Code_Type
	unsigned int pts;//ʱ���
	unsigned short w;//��
	unsigned short h;//��
	unsigned int rpts;//¼��ʱ��	
	unsigned int datalen;//���ݳ���	
}UDXPACKED;


struct Media_FrameInfo
{
	unsigned char JumpFrameMode;//����ģʽ,�����֧�����죬ֱ������0
	unsigned char FrameType;//�����ͣ�ZN_IFRAME��....
	unsigned long MainIndex;//�����,��JumpFrameMode��Ϊ0ʱ������ָ������ţ������� Ϊ0
	unsigned char bStart;//һ�쿪ʼ��ǣ������͵����ݿ飬Ϊ�������죬bstart����bend����1�����ǵ�һƬ��Ҳ�����һƬ��������Ƿ�Ƭ�������ʱ��bstart = 1��ʾ��һƬ����bend =1��ʾ���һƬ
	unsigned char bLast;//һ��������
	unsigned char codetype;//Video_Code_Type or Audio_Code_Type
	int FrameLen;//��ǰ��Ƭ����
	unsigned char * data;//��ǰ��Ƭ����
};
typedef struct Media_Time
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
}Media_Time;

#ifdef WIN32
#pragma pack( pop)
#endif

#ifndef __cplusplus

typedef struct FrameType FrameType;

#endif

#define UdxFrameType FrameType
// #define UdxFrameType1 FrameType1

#endif