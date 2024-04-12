#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>


using namespace std;
using namespace cv;

class Chess
{
public:
	Chess();								// ���캯��
	Chess(int rows, int cols, int color);
	Chess& operator=(const Chess& chess)
	{
		this->color = chess.color;
		this->atkValue = chess.atkValue;
		this->defValue = chess.defValue;
		this->rows = chess.rows;
		this->cols = chess.cols;
		this->isBoundry = chess.isBoundry;
		return *this;
	}	
	int rows;				// ����
	int cols;				// ����
	int color = 0;			// ��ɫ��-1Ϊ�ڣ�1Ϊ��
	int atkValue = 0;		// �����÷�
	int defValue = 0;		// ���صķ�
	bool isBoundry = 0;		// �Ƿ��ڱ߽�
};

