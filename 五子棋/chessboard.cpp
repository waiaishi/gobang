#include<chessboard.h>


Chessboard::Chessboard()	// 构造函数
{
	// 图片绘制棋盘
	this->cols = 161;
	this->rows = 161;
	Axis.resize(this->cols / 10 - 1);
	for (int i = 0; i < Axis.size(); i++)
	{
		this->Axis[i].resize(this->rows / 10 - 1);
	}
	this->chessboard = Mat::zeros(this->cols, this->rows, CV_8UC3);
	bitwise_not(chessboard, chessboard);
	for (int i = 0; i <= this->rows; i += 10)
	{
		line(chessboard, Point(i, 0), Point(i, 160), Scalar(0, 0, 0), 1, LINE_AA, 0);
	}
	for (int i = 0; i <= this->cols; i += 10)
	{
		line(chessboard, Point(0, i), Point(160, i), Scalar(0, 0, 0), 1, LINE_AA, 0);
	}
	this->Firstplayer();
	if (this->now == 1) // AI在棋盘中央下黑棋
	{
		Chess chess(8, 8, this->sequence);
		this->Getnewboard(chess);
		now = 0;
	}
}

void Chessboard::Getnewboard(Chess chess)	// 更新新棋盘
{
	circle(this->chessboard, Point(chess.rows * 10, chess.cols * 10), 5, Scalar(0, 0, 0), chess.color, LINE_4, 0);
	this->Axis[chess.cols - 1][chess.rows - 1] = chess;
	this->sequence = 0 - chess.color;
	this->Show(this->chessboard, "五子棋");
}

Chess Chessboard::FindRightAxis()	// 寻找对应棋盘位置
{
	int y = (int)(this->mouse.y + 6) / 10;
	int x = (int)(this->mouse.x + 6) / 10;
	Chess fchess(x, y, this->sequence);
	return fchess;
}

void Chessboard::Firstplayer()	// 先手判定
{
	srand((unsigned)time(NULL));
	this->now = rand() % 2;
	if (this->now == 0)
	{
		cout << "玩家执黑棋先手" << endl;
	}
	else if (this->now == 1)
	{
		cout << "AI执黑棋先手" << endl;
	}
}

void Chessboard::Play()	// 玩家下棋
{
	Chess chess = this->FindRightAxis();
	if (this->Axis[chess.cols - 1][chess.rows - 1].color == 0 && !this->Gameend())
	{
		this->Getnewboard(chess);
		this->now = 1;			// 等待电脑下棋
		this->Findend();
		if (!this->Gameend())
		{
			this->AiPlay();
			this->now = 0;		// 重新让玩家下棋
			this->Findend();
		}
		this->Gameend();
	}
}

void Chessboard::AiPlay()	// AI下棋
{
	vector<Chess> Defvalue;
	for (int i = 0; i < this->Axis.size(); i++)
	{
		for (int j = 0; j < this->Axis[0].size(); j++)
		{
			if (Axis[i][j].color == 0)
			{				
				Chessplayer AI(Axis);
				Chess Defchess(j + 1, i + 1, 0 - this->sequence);
				Defchess.defValue = AI.getDefvalue(Defchess);
				Defvalue.push_back(Defchess);
				//cout << "点位："<< Defchess.rows<< " " << Defchess.cols << "\t得分: " << Defchess.defValue << endl;
				//cout << endl;
			}
		}
	}
	vector<Chess> Atkvalue;
	for (int i = 0; i < this->Axis.size(); i++)
	{
		for (int j = 0; j < this->Axis[0].size(); j++)
		{
			if (Axis[i][j].color == 0)
			{
				Chessplayer AI(Axis);
				Chess Atkchess(j + 1, i + 1, this->sequence);  
				Atkchess.atkValue = AI.getAtkvalue(Atkchess);
				Atkvalue.push_back(Atkchess);
			}
		}
	}
	// 对容器里面的棋子按进攻得分和防守得分从大到小进行排序
	sort(Atkvalue.begin(), Atkvalue.end(), atkCompare());
	sort(Defvalue.begin(), Defvalue.end(), defCompare());
	cout << "进攻分: " << Atkvalue[0].atkValue << " " << "\t防御分： " << Defvalue[0].defValue << endl;
	Chess right;
	if (Atkvalue[0].atkValue >= Defvalue[0].defValue)
	{
		vector<Chess> vAtk;// 临时存放可能相同最大的分的棋子
		for (int i = 0; i < Atkvalue.size(); i++)
		{
			if (Atkvalue[i].atkValue == Atkvalue[0].atkValue)
			{
				vAtk.push_back(Atkvalue[i]);
			}
		}
		srand((unsigned)time(NULL));
		right = vAtk[rand() % vAtk.size()];
	}
	else if (Atkvalue[0].atkValue < Defvalue[0].defValue)
	{
		vector<Chess> vDef;// 临时存放可能相同最大的分的棋子
		for (int i = 0; i < Defvalue.size(); i++)
		{
			if (Defvalue[i].defValue == Defvalue[0].defValue)
			{
				vDef.push_back(Defvalue[i]);
			}
		}
		srand((unsigned)time(NULL));
		right = vDef[rand() % vDef.size()];
	}
	right.color = this->sequence;
	this->Getnewboard(right);

}

void Chessboard::Findend()	// 结束判定
{
	vector<int> lianwu{ 1, 1, 1, 1, 1 };
	for (int i = 2; i < this->Axis.size() - 2; i++)
	{
		for (int j = 2; j < this->Axis[0].size() - 2; j++)
		{
			if (abs(Axis[i - 2][j].color + Axis[i - 1][j].color + Axis[i][j].color + Axis[i + 1][j].color + Axis[i + 2][j].color) == 5)
			{
				Point p1(Axis[i - 2][j].rows * 10, Axis[i - 2][j].cols * 10);
				Point p2(Axis[i + 2][j].rows * 10, Axis[i + 2][j].cols * 10);
				line(chessboard, p1, p2, Scalar(0, 0, 255), 1, LINE_AA, 0);
				this->Show(this->chessboard, "五子棋");
				this->end = true;
			}
			else if (abs(Axis[i][j - 2].color + Axis[i][j - 1].color + Axis[i][j].color + Axis[i][j + 1].color + Axis[i][j + 2].color) == 5)
			{
				Point p1(Axis[i][j - 2].rows * 10, Axis[i][j - 2].cols * 10);
				Point p2(Axis[i][j + 2].rows * 10, Axis[i][j + 2].cols * 10);
				line(chessboard, p1, p2, Scalar(0, 0, 255), 1, LINE_AA, 0);
				this->Show(this->chessboard, "五子棋");
				this->end = true;
			}
			else if (abs(Axis[i - 2][j - 2].color + Axis[i - 1][j - 1].color + Axis[i][j].color + Axis[i + 1][j + 1].color + Axis[i + 2][j + 2].color) == 5)
			{
				Point p1(Axis[i - 2][j - 2].rows * 10, Axis[i - 2][j - 2].cols * 10);
				Point p2(Axis[i + 2][j + 2].rows * 10, Axis[i + 2][j + 2].cols * 10);
				line(chessboard, p1, p2, Scalar(0, 0, 255), 1, LINE_AA, 0);
				this->Show(this->chessboard, "五子棋");
				this->end = true;
			}
			else if(abs(Axis[i + 2][j - 2].color + Axis[i + 1][j - 1].color + Axis[i][j].color + Axis[i - 1][j + 1].color + Axis[i - 2][j + 2].color) == 5)				
			{
				Point p1(Axis[i + 2][j - 2].rows * 10, Axis[i + 2][j - 2].cols * 10);
				Point p2(Axis[i - 2][j + 2].rows * 10, Axis[i - 2][j + 2].cols * 10);
				line(chessboard, p1, p2, Scalar(0, 0, 255), 1, LINE_AA, 0);
				this->Show(this->chessboard, "五子棋");
				this->end = true;
			}
		}
	}
}

bool Chessboard::Gameend()	// 游戏结束
{
	if (this->end)
	{
		if (now == 0)
		{
			cout << "游戏结束,电脑获胜" << endl;
		}
		else if (now == 1)
		{
			cout << "游戏结束,玩家获胜" << endl;
		}
		return end;
	}
	return false;
}



