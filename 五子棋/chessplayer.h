#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<chess.h>

using namespace std;
using namespace cv;

class Chessplayer
{
public:

	// ���캯��
	Chessplayer();									
	Chessplayer(vector<vector<Chess>> Axis);	
	int getAtkvalue(Chess chess);	// �����������	
	int getDefvalue(Chess chess);	// ������ط���			
	/* ��ȡ���г���Ϊ4��5��6��7������
	 ���������壺0��1��2��3�ֱ��Ӧ�����ϡ��ϡ����ϡ���
	 �жϵ��λ�������ϡ��ϡ����ϡ�����Ϊ0λ��
	*/
	vector<Chess> fourChain(Chess chess, int dir, int loc);
	vector<Chess> fiveChain(Chess chess, int dir, int loc);
	vector<Chess> sixChain(Chess chess, int dir, int loc);
	vector<Chess> sevenChain(Chess chess, int dir, int loc);
	// ����������
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
