/*****************************************************************************************
*
*				  ȥ�룺RemoveNoise
*				 By ������ 2015/10/15
*
*****************************************************************************************/
#ifndef REMOVENOISE_H
#define REMOVENOISE_H

#include "Global.h"

class RemoveNoise
{
public:
	RemoveNoise();
	~RemoveNoise();
	//ȥ�����С��area����ͨ�򣨱���������������Ч��
	void LessConnectedRegionRemove(IplImage* image,int area);

	//ȥ�����Ƽ��ͼ�еĸ����������������Ƽ�⣩
	//���룺image-->���Ƽ������ֵ��ͼ��area-->�����������(���ߵ���С���),lineLength-->�ߵ���С����
	//����ֵ������������������������
	int RemoveCrackImageNoise(IplImage* image,int area,int lineLength);
private:
};
#endif