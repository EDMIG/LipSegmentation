/*****************************************************************************************
*
*					  ȥ�룺RemoveNoise
*					By ������ 2015/10/15
*
*****************************************************************************************/

#include "RemoveNoise.h"

RemoveNoise::RemoveNoise(){}

RemoveNoise::~RemoveNoise(){}

//ȥ�����С��area����ͨ�򣨱���������������Ч��
void RemoveNoise::LessConnectedRegionRemove(IplImage* image,int area)
{
	IplImage* src = cvCloneImage(image);
	CvMemStorage* storage = cvCreateMemStorage(0);  
	CvSeq* contour = 0; 
	//��ȡ����   
	cvFindContours( src, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE ); 
	cvZero( image );//���
	double minarea = (double)area;  
	for( ; contour != 0; contour = contour->h_next )  
	{  

		double tmparea=fabs(cvContourArea(contour));  
		if(tmparea < minarea)   
		{  
			cvSeqRemove(contour,0); //ɾ�����С���趨ֵ������   
			continue;  
		}  
  
		CvScalar color = CV_RGB( 255, 255,255 );  

		//max_level �������������ȼ�������ȼ�Ϊ0�����Ƶ��������������Ϊ1��������������������ͬ�ļ�����������   
		//���ֵΪ2�����е�����������ȼ�Ϊ2����������ͬ�����������е�һ��������������֡�   
		//���ֵΪ����������������ͬ�������������������ֱ������Ϊabs(max_level)-1����������    
		cvDrawContours( image, contour, color, color, -1, CV_FILLED, 8 , cvPoint(0, 0));//�����ⲿ���ڲ�������   
	}  

	//release
	cvReleaseImage(&src);
	cvReleaseMemStorage(&storage);  
}

//ȥ�����Ƽ��ͼ�еĸ����������������Ƽ�⣩
//���룺image-->���Ƽ������ֵ��ͼ��area-->�����������(���ߵ���С���),lineLength-->�ߵ���С����
//����ֵ������������������������
int RemoveNoise::RemoveCrackImageNoise(IplImage* image,int area,int lineLength)
{
	IplImage* src = cvCloneImage(image);
	CvMemStorage* storage = cvCreateMemStorage(0);  
	CvSeq* contour = 0; 
	//��ȡ����   
	cvFindContours( src, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE ); 
	cvZero( image );//���
	double minarea = (double)area;  
	int nCracks = 0;//��������
	for( ; contour != 0; contour = contour->h_next )  
	{  
		CvRect rect=cvBoundingRect(contour);//����㼯�������棨up-right�����α߽� 
		int len = rect.height>rect.width ? rect.height : rect.width;
		double tmparea=fabs(cvContourArea(contour));  
		if(tmparea < minarea || len < lineLength)   
		{  
			cvSeqRemove(contour,0); //ɾ�����С���趨ֵ������   
			continue;  
		}  
		nCracks++;
		CvScalar color = CV_RGB( 255, 255,255 );  

		//max_level �������������ȼ�������ȼ�Ϊ0�����Ƶ��������������Ϊ1��������������������ͬ�ļ�����������   
		//���ֵΪ2�����е�����������ȼ�Ϊ2����������ͬ�����������е�һ��������������֡�   
		//���ֵΪ����������������ͬ�������������������ֱ������Ϊabs(max_level)-1����������    
		cvDrawContours( image, contour, color, color, -1, CV_FILLED, 8 , cvPoint(0, 0));//�����ⲿ���ڲ�������   
	}  

	//release
	cvReleaseImage(&src);
	cvReleaseMemStorage(&storage);  
	return nCracks;
}