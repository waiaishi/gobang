#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>


using namespace std;
using namespace cv;

class Chess
{
public:
	Chess();								// 构造函数
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
	int rows;				// 列数
	int cols;				// 行数
	int color = 0;			// 颜色，-1为黑，1为白
	int atkValue = 0;		// 进攻得分
	int defValue = 0;		// 防守的分
	bool isBoundry = 0;		// 是否在边界
};

