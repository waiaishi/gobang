#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<chess.h>

using namespace std;
using namespace cv;

class Chessplayer
{
public:

	// 构造函数
	Chessplayer();									
	Chessplayer(vector<vector<Chess>> Axis);	
	int getAtkvalue(Chess chess);	// 计算进攻分数	
	int getDefvalue(Chess chess);	// 计算防守分数			
	/* 获取所有长度为4、5、6、7的棋链
	 棋链方向定义：0、1、2、3分别对应：左上、上、右上、右
	 判断点的位置以左上、上、右上、右作为0位。
	*/
	vector<Chess> fourChain(Chess chess, int dir, int loc);
	vector<Chess> fiveChain(Chess chess, int dir, int loc);
	vector<Chess> sixChain(Chess chess, int dir, int loc);
	vector<Chess> sevenChain(Chess chess, int dir, int loc);
	// 五子棋棋形
	vector<vector<int>> lianwu{ { 1, 1, 1, 1, 1 } };
	vector<vector<int>> huoshi{ { 0, 1, 1, 1, 1, 0 } };
	vector<vector<int>> chongshi{ { 1, 0, 1, 1, 1 }, { 1, 1, 1, 0, 1 }, { 1, 1, 0, 1, 1 }, { 0, 1, 1, 1, 1, -1 }, { -1, 1, 1, 1, 1, 0 } };
	vector<vector<int>> huoshan{ { 0, 1, 1, 1, 0 } };
	vector<vector<int>> miansan{ { 1, 0, 1, 1 }, { 1, 1, 0, 1 }, { -1, 1, 1, 1, 0, 0 }, { 0, 0, 1, 1, 1, -1 },  
								 { 1, 0, 0, 1, 1, }, { 1, 1, 0, 0, 1 }, { 1, 0, 1, 0, 1 }, { -1, 0, 1, 1, 1, 0, -1 } };
	vector<vector<int>> huoer{ { 0, 0, 1, 1, 0, 0 }, { 0, 1, 0, 1, 0 } };

	vector<vector<int>> mianer{ { 0, 0, 0, 1, 1, -1 }, { 0, 0, 1, 0, 1, -1 }, {0, 1, 0, 0, 1, -1},
								{ -1, 1, 1, 0, 0, 0 }, { -1, 1, 0, 1, 0, 0 }, {-1, 1, 0, 0, 1, 0},
								{ 1, 0, 0, 0, 1 } , { 1, 0, 0, 1 } };
	vector<vector<Chess>> Axis;
};
