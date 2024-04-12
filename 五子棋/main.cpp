#include<opencv2/opencv.hpp>
#include<iostream>
#include<chessboard.h>
#include<chess.h>
using namespace std;
using namespace cv;

Chessboard chessgame;

void findpoint(int event, int x, int y, int flags, void* userdata)	// 读取鼠标点击的点的位置
{
	Mat image = *((Mat*)userdata);
	if (event == EVENT_LBUTTONDOWN)
	{
		if (x >= 4 && x <= 153 && y >= 4 && y <= 153 && chessgame.now == 0 && !chessgame.end)
		{
			chessgame.mouse.x = x;
			chessgame.mouse.y = y;
			chessgame.Play();
		}
		else if (chessgame.end)
		{
			chessgame.Gameend();
		}
	}
}

void Gamebegin(Mat image)
{
	// 鼠标点击初始点和终点位置	
	namedWindow("五子棋", WINDOW_FREERATIO);						// 创建一个自由大小的窗口
	imshow("五子棋", image);										// 显示图片，一定要同名	
	setMouseCallback("五子棋", findpoint, (void*)(&image));		// 对图片进行鼠标操作
}

int main()
{
	Gamebegin(chessgame.chessboard);
	waitKey();				// 程序停止在这里。类似于system("pause")
	destroyAllWindows();	// 消除程序创建的所有窗口  
	system("pause");
	return 0;
}