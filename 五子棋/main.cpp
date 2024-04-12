#include<opencv2/opencv.hpp>
#include<iostream>
#include<chessboard.h>
#include<chess.h>
using namespace std;
using namespace cv;

Chessboard chessgame;

void findpoint(int event, int x, int y, int flags, void* userdata)	// ��ȡ������ĵ��λ��
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
	// �������ʼ����յ�λ��	
	namedWindow("������", WINDOW_FREERATIO);						// ����һ�����ɴ�С�Ĵ���
	imshow("������", image);										// ��ʾͼƬ��һ��Ҫͬ��	
	setMouseCallback("������", findpoint, (void*)(&image));		// ��ͼƬ����������
}

int main()
{
	Gamebegin(chessgame.chessboard);
	waitKey();				// ����ֹͣ�����������system("pause")
	destroyAllWindows();	// �������򴴽������д���  
	system("pause");
	return 0;
}