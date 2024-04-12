#include<chess.h>

Chess::Chess()	// ¹¹Ôìº¯Êý
{
	this->cols = -1;
	this->rows = -1;
}

Chess::Chess(int rows, int cols, int color)
{
	this->rows = rows;
	this->cols = cols;
	this->color = color;
	if (this->rows < 1 || this->rows > 15 || this->cols < 1 || this->cols > 15)
	{
		this->isBoundry = 1;
	}
}
