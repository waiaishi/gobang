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

	Chessboard();						// 构造函数
	void Show(Mat image, string name)
	{
		namedWindow(name, WINDOW_FREERATIO);
		imshow(name, image);
	}
	void Getnewboard(Chess chess);					// 更新新棋盘
	Chess FindRightAxis();							// 寻找点击的棋子对应棋盘的位置
	void Firstplayer();								// 先手判定
	void Play();									// 玩家下棋
	void AiPlay();									// AI下棋
	void Findend();									// 结束判定
	bool Gameend();									// 游戏结束
	//~Chessboard();								// 析构函数
	Mat chessboard;									// 棋盘
	Point mouse;									// 储存鼠标点击点
	int now;										// 判定谁下棋，0为玩家，1为ai	
	bool end = false;								// 记录是否结束
private:

	int rows;						// 列数 
	int cols;						// 行数	
	int sequence = -1;				// 黑棋先下,-1为黑棋，1为白棋	
	vector<vector<Chess>> Axis;		// 对应棋盘位置,-1为黑棋，1为白棋
};


