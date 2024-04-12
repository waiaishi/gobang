#include<chessboard.h>


Chessboard::Chessboard()	// ���캯��
{
	// ͼƬ��������
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
	if (this->now == 1) // AI�����������º���
	{
		Chess chess(8, 8, this->sequence);
		this->Getnewboard(chess);
		now = 0;
	}
}

void Chessboard::Getnewboard(Chess chess)	// ����������
{
	circle(this->chessboard, Point(chess.rows * 10, chess.cols * 10), 5, Scalar(0, 0, 0), chess.color, LINE_4, 0);
	this->Axis[chess.cols - 1][chess.rows - 1] = chess;
	this->sequence = 0 - chess.color;
	this->Show(this->chessboard, "������");
}

Chess Chessboard::FindRightAxis()	// Ѱ�Ҷ�Ӧ����λ��
{
	int y = (int)(this->mouse.y + 6) / 10;
	int x = (int)(this->mouse.x + 6) / 10;
	Chess fchess(x, y, this->sequence);
	return fchess;
}

void Chessboard::Firstplayer()	// �����ж�
{
	srand((unsigned)time(NULL));
	this->now = rand() % 2;
	if (this->now == 0)
	{
		cout << "���ִ��������" << endl;
	}
	else if (this->now == 1)
	{
		cout << "AIִ��������" << endl;
	}
}

void Chessboard::Play()	// �������
{
	Chess chess = this->FindRightAxis();
	if (this->Axis[chess.cols - 1][chess.rows - 1].color == 0 && !this->Gameend())
	{
		this->Getnewboard(chess);
		this->now = 1;			// �ȴ���������
		this->Findend();
		if (!this->Gameend())
		{
			this->AiPlay();
			this->now = 0;		// �������������
			this->Findend();
		}
		this->Gameend();
	}
}

void Chessboard::AiPlay()	// AI����
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
				//cout << "��λ��"<< Defchess.rows<< " " << Defchess.cols << "\t�÷�: " << Defchess.defValue << endl;
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
	// ��������������Ӱ������÷ֺͷ��ص÷ִӴ�С��������
	sort(Atkvalue.begin(), Atkvalue.end(), atkCompare());
	sort(Defvalue.begin(), Defvalue.end(), defCompare());
	cout << "������: " << Atkvalue[0].atkValue << " " << "\t�����֣� " << Defvalue[0].defValue << endl;
	Chess right;
	if (Atkvalue[0].atkValue >= Defvalue[0].defValue)
	{
		vector<Chess> vAtk;// ��ʱ��ſ�����ͬ���ķֵ�����
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
		vector<Chess> vDef;// ��ʱ��ſ�����ͬ���ķֵ�����
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

void Chessboard::Findend()	// �����ж�
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
				this->Show(this->chessboard, "������");
				this->end = true;
			}
			else if (abs(Axis[i][j - 2].color + Axis[i][j - 1].color + Axis[i][j].color + Axis[i][j + 1].color + Axis[i][j + 2].color) == 5)
			{
				Point p1(Axis[i][j - 2].rows * 10, Axis[i][j - 2].cols * 10);
				Point p2(Axis[i][j + 2].rows * 10, Axis[i][j + 2].cols * 10);
				line(chessboard, p1, p2, Scalar(0, 0, 255), 1, LINE_AA, 0);
				this->Show(this->chessboard, "������");
				this->end = true;
			}
			else if (abs(Axis[i - 2][j - 2].color + Axis[i - 1][j - 1].color + Axis[i][j].color + Axis[i + 1][j + 1].color + Axis[i + 2][j + 2].color) == 5)
			{
				Point p1(Axis[i - 2][j - 2].rows * 10, Axis[i - 2][j - 2].cols * 10);
				Point p2(Axis[i + 2][j + 2].rows * 10, Axis[i + 2][j + 2].cols * 10);
				line(chessboard, p1, p2, Scalar(0, 0, 255), 1, LINE_AA, 0);
				this->Show(this->chessboard, "������");
				this->end = true;
			}
			else if(abs(Axis[i + 2][j - 2].color + Axis[i + 1][j - 1].color + Axis[i][j].color + Axis[i - 1][j + 1].color + Axis[i - 2][j + 2].color) == 5)				
			{
				Point p1(Axis[i + 2][j - 2].rows * 10, Axis[i + 2][j - 2].cols * 10);
				Point p2(Axis[i - 2][j + 2].rows * 10, Axis[i - 2][j + 2].cols * 10);
				line(chessboard, p1, p2, Scalar(0, 0, 255), 1, LINE_AA, 0);
				this->Show(this->chessboard, "������");
				this->end = true;
			}
		}
	}
}

bool Chessboard::Gameend()	// ��Ϸ����
{
	if (this->end)
	{
		if (now == 0)
		{
			cout << "��Ϸ����,���Ի�ʤ" << endl;
		}
		else if (now == 1)
		{
			cout << "��Ϸ����,��һ�ʤ" << endl;
		}
		return end;
	}
	return false;
}



