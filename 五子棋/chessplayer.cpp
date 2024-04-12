#include<chessplayer.h>


Chessplayer::Chessplayer()	// 构造函数
{

}

Chessplayer::Chessplayer(vector<vector<Chess>> Axis)
{
	this->Axis = Axis;
}

int Chessplayer::getAtkvalue(Chess chess)				// 计算进攻分数
{
	int atk = 0;
	int fuhao = chess.color;
	int help = 0;
	for (int i = 0; i < 4; i++)	//方向
	{
		vector<vector<Chess>> tag;
		for (int j = 0; j < 4; j++) // 位置
		{
			if (!this->fourChain(chess, i, j).empty())
			{
				tag.push_back(this->fourChain(chess, i, j));
			}
		}	
		for (int j = 0; j < 5; j++) // 位置
		{
			if (!this->fiveChain(chess, i, j).empty())
			{
				tag.push_back(this->fiveChain(chess, i, j));
			}
		}
		for (int j = 0; j < 6; j++) // 位置
		{
			if (!this->sixChain(chess, i, j).empty())
			{
				tag.push_back(this->sixChain(chess, i, j));
			}
		}
		for (int j = 0; j < 7; j++) // 位置
		{
			if (!this->sevenChain(chess, i, j).empty())
			{
				tag.push_back(this->sevenChain(chess, i, j));
			}
		}
		vector<vector<int>> qixing;
		for (int x = 0; x < tag.size(); x++)
		{
			vector<int> temp;// 临时存储棋形
			for (int y = 0; y < tag[x].size(); y++)
			{
				temp.push_back(tag[x][y].color * fuhao);
			}
			qixing.push_back(temp);
		}
		for (int x = 0; x < qixing.size(); x++)
		{
			vector<vector<int>>::iterator itlianwu = find(lianwu.begin(), lianwu.end(), qixing[x]);			
			if (itlianwu != lianwu.end())
			{
				atk += 100000;
				break;
			}
			vector<vector<int>>::iterator ithuoshi = find(huoshi.begin(), huoshi.end(), qixing[x]);
			if (ithuoshi != huoshi.end())
			{
				atk += 1000;
				break;
			}			
			vector<vector<int>>::iterator ithuoshan = find(huoshan.begin(), huoshan.end(), qixing[x]);
			if (ithuoshan != huoshan.end())
			{
				atk += 250;
				if (help >= 1)
				{
					atk += 500;
				}
				help++;
				break;
			}
			vector<vector<int>>::iterator itchongshi = find(chongshi.begin(), chongshi.end(), qixing[x]);
			if (itchongshi != chongshi.end())
			{
				atk += 150;			
				if (help >= 1)
				{
					atk += 700;
				}
				help++;
				break;
			}
			vector<vector<int>>::iterator itmiansan = find(miansan.begin(), miansan.end(), qixing[x]);
			if (itmiansan != miansan.end())
			{
				atk += 75;
				break;
			}
			vector<vector<int>>::iterator ithuoer = find(huoer.begin(), huoer.end(), qixing[x]);
			if (ithuoer != huoer.end())
			{
				if (ithuoer == huoer.begin())
				{
					atk += 64;
					break;
				}
				atk += 60;
			}
			vector<vector<int>>::iterator itmianer = find(mianer.begin(), mianer.end(), qixing[x]);
			if (itmianer != mianer.end())
			{
				atk += 8;
				break;
			}
		}
	}
	return atk;
}

int Chessplayer::getDefvalue(Chess chess)				// 计算防守分数
{
	int def = 0;
	int fuhao = chess.color;
	int help = 0;
	
	for (int i = 0; i < 4; i++)	//方向
	{	
		vector<vector<Chess>> tag;
		for (int j = 0; j < 4; j++) // 位置
		{
			if (!this->fourChain(chess, i, j).empty())
			{
				tag.push_back(this->fourChain(chess, i, j));
			}
		}
		for (int j = 0; j < 5; j++) // 位置
		{
			if (!this->fiveChain(chess, i, j).empty())
			{
				tag.push_back(this->fiveChain(chess, i, j));
			}
		}
		for (int j = 0; j < 6; j++) // 位置
		{
			if (!this->sixChain(chess, i, j).empty())
			{
				tag.push_back(this->sixChain(chess, i, j));
			}
		}
		for (int j = 0; j < 7; j++) // 位置
		{
			if (!this->sevenChain(chess, i, j).empty())
			{
				tag.push_back(this->sevenChain(chess, i, j));
			}
		}
		vector<vector<int>> qixing;
		//cout << "方向："<< i <<" 棋形: ";
		for (int x = 0; x < tag.size(); x++)
		{
			vector<int> temp;// 临时存储棋形
			for (int y = 0; y < tag[x].size(); y++)
			{				
				temp.push_back(tag[x][y].color * fuhao);
			}
			//for (int a = 0; a < temp.size(); a++)
			//{
			//	cout << temp[a];
			//}
			//cout << "  ";
			qixing.push_back(temp);	
		}
		//cout<< endl;
		for (int x = 0; x < qixing.size(); x++)
		{
			vector<vector<int>>::iterator itlianwu = find(lianwu.begin(), lianwu.end(), qixing[x]);
			if (itlianwu != lianwu.end())
			{
				def += 10000;
				break;
			}
			vector<vector<int>>::iterator ithuoshi = find(huoshi.begin(), huoshi.end(), qixing[x]);
			if (ithuoshi != huoshi.end())
			{
				def += 900;
				break;
			}
			vector<vector<int>>::iterator ithuoshan = find(huoshan.begin(), huoshan.end(), qixing[x]);
			if (ithuoshan != huoshan.end())
			{
				def += 150;
				if (help >= 1)
				{
					def += 600;
				}
				help++;
				break;
			}
			vector<vector<int>>::iterator itchongshi = find(chongshi.begin(), chongshi.end(), qixing[x]);
			if (itchongshi != chongshi.end())
			{
				def += 100;
				if (help >= 1)
				{
					def += 700;
				}
				help++;
				break;
			}
			vector<vector<int>>::iterator itmiansan = find(miansan.begin(), miansan.end(), qixing[x]);
			if (itmiansan != miansan.end())
			{
				if (itmiansan == miansan.begin() || itmiansan == miansan.begin() + 1)
				{
					def += 100;
				}
				else
				{
					def += 50;				
				}
				break;
			}
			vector<vector<int>>::iterator ithuoer = find(huoer.begin(), huoer.end(), qixing[x]);
			if (ithuoer != huoer.end())
			{
				def += 10;
				break;
			}
			vector<vector<int>>::iterator itmianer = find(mianer.begin(), mianer.end(), qixing[x]);
			if (itmianer != mianer.end())
			{
				def += 1;
				break;
			}
		}		
	}
	return def;
}

vector<Chess> Chessplayer::fourChain(Chess chess, int dir, int loc)
{
	vector<vector<Chess>> axis = Axis;				// 虚拟棋盘
	axis[chess.cols - 1][chess.rows - 1] = chess;
	vector<Chess> four;
	if (dir == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			Chess tag(chess.rows + i - loc, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				four.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				four.clear();
				break;
			}
		}
	}
	else if (dir == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			Chess tag(chess.rows, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				four.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				four.clear();
				break;
			}
		}
	}
	else if (dir == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			Chess tag(chess.rows - i + loc, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				four.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				four.clear();
				break;
			}
		}
	}
	else if (dir == 3)
	{
		for (int i = 0; i < 4; i++)
		{
			Chess tag(chess.rows - i + loc, chess.cols, chess.color);
			if (tag.isBoundry != 1)
			{
				four.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				four.clear();
				break;
			}
		}
	}
	return four;
}

vector<Chess> Chessplayer::fiveChain(Chess chess, int dir, int loc)
{
	vector<vector<Chess>> axis = Axis;				// 虚拟棋盘
	axis[chess.cols - 1][chess.rows - 1] = chess;
	vector<Chess> five;
	if (dir == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			Chess tag(chess.rows + i - loc, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				five.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				five.clear();
				break;
			}
		}
	}
	else if (dir == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			Chess tag(chess.rows, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				five.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				five.clear();
				break;
			}
		}
	}
	else if (dir == 2)
	{
		for (int i = 0; i < 5; i++)
		{
			Chess tag(chess.rows - i + loc, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				five.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				five.clear();
				break;
			}
		}
	}
	else if (dir == 3)
	{
		for (int i = 0; i < 5; i++)
		{
			Chess tag(chess.rows - i + loc, chess.cols, chess.color);
			if (tag.isBoundry != 1)
			{
				five.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				five.clear();
				break;
			}
		}
	}
	return five;
}

vector<Chess> Chessplayer::sixChain(Chess chess, int dir, int loc)
{
	vector<vector<Chess>> axis = Axis;				// 虚拟棋盘
	axis[chess.cols - 1][chess.rows - 1] = chess;
	vector<Chess> six;
	if (dir == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			Chess tag(chess.rows + i - loc, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				six.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				six.clear();
				break;
			}
		}
	}
	else if (dir == 1)
	{
		for (int i = 0; i < 6; i++)
		{
			Chess tag(chess.rows, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				six.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				six.clear();
				break;
			}
		}
	}
	else if (dir == 2)
	{
		for (int i = 0; i < 6; i++)
		{
			Chess tag(chess.rows - i + loc, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				six.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				six.clear();
				break;
			}
		}
	}
	else if (dir == 3)
	{
		for (int i = 0; i < 6; i++)
		{
			Chess tag(chess.rows - i + loc, chess.cols, chess.color);
			if (tag.isBoundry != 1)
			{
				six.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				six.clear();
				break;
			}
		}
	}
	return six;
}

vector<Chess> Chessplayer::sevenChain(Chess chess, int dir, int loc)
{
	vector<vector<Chess>> axis = Axis;				// 虚拟棋盘
	axis[chess.cols - 1][chess.rows - 1] = chess;
	vector<Chess> seven;
	if (dir == 0)
	{
		for (int i = 0; i < 7; i++)
		{
			Chess tag(chess.rows + i - loc, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				seven.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				seven.clear();
				break;
			}
		}
	}
	else if (dir == 1)
	{
		for (int i = 0; i < 7; i++)
		{
			Chess tag(chess.rows, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				seven.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				seven.clear();
				break;
			}
		}
	}
	else if (dir == 2)
	{
		for (int i = 0; i < 7; i++)
		{
			Chess tag(chess.rows - i + loc, chess.cols + i - loc, chess.color);
			if (tag.isBoundry != 1)
			{
				seven.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				seven.clear();
				break;
			}
		}
	}
	else if (dir == 3)
	{
		for (int i = 0; i < 7; i++)
		{
			Chess tag(chess.rows - i + loc, chess.cols, chess.color);			
			if (tag.isBoundry != 1)
			{
				seven.push_back(axis[tag.cols - 1][tag.rows - 1]);
			}
			else
			{
				seven.clear();
				break;
			}
		}
	}
	return seven;
}

