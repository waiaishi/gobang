#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<chess.h>
#include<chessplayer.h>
#include"ctime"
using namespace std;
using namespace cv;

class atkCompare
{
public:
	bool operator()(Chess chess1, Chess chess2)
	{
		return chess1.atkValue > chess2.atkValue;
	}
};
class defCompare
{
public:
	bool operator()(Chess chess1, Chess chess2)
	{
		return chess1.defValue > chess2.defValue;
	}
};

class Chessboard
{
public:

	Chessboard();						// ���캯��
	void Show(Mat image, string name)
	{
		namedWindow(name, WINDOW_FREERATIO);
		imshow(name, image);
	}
	void Getnewboard(Chess chess);					// ����������
	Chess FindRightAxis();							// Ѱ�ҵ�������Ӷ�Ӧ���̵�λ��
	void Firstplayer();								// �����ж�
	void Play();									// �������
	void AiPlay();									// AI����
	void Findend();									// �����ж�
	bool Gameend();									// ��Ϸ����
	//~Chessboard();								// ��������
	Mat chessboard;									// ����
	Point mouse;									// �����������
	int now;										// �ж�˭���壬0Ϊ��ң�1Ϊai	
	bool end = false;								// ��¼�Ƿ����
private:

	int rows;						// ���� 
	int cols;						// ����	
	int sequence = -1;				// ��������,-1Ϊ���壬1Ϊ����	
	vector<vector<Chess>> Axis;		// ��Ӧ����λ��,-1Ϊ���壬1Ϊ����
};


