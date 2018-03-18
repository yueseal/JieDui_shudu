#include<iostream>
#include<algorithm>
#include <ctime>
#include<fstream>
using namespace std;

int Initial_State[10][10];

bool get_Initial_State(int i, int j)  //搜索第（ i , j ）位置处可以存储的数字,找到解则返回true，否则返回false
{
	if (i > 9 || j > 9)
		return true;

	for (int k = 1; k <= 9; ++k)
	{
		bool can = true;                // can 变量用于记录数字k能否放在 ( i , j ) 处 
		for (int m = 1; m < i; ++m)
			if (Initial_State[m][j] == k)  // 检查同一列是否出现过数字k
			{
				can = false;
				break;
			}
		if (can)
			for (int n = 1; n < j; ++n)
				if (Initial_State[i][n] == k)  // 检查同一行是否出现过数字k
				{
					can = false;
					break;
				}
		if (can)
		{
			int up1 = (i / 3) * 3 + 3; // (i,j)方格所在的3×3小方格i坐标的上限
			int up2 = (j / 3) * 3 + 3;   // (i,j)方格所在的3×3小方格在j坐标的上限

			if (i % 3 == 0)    //这是针对特殊情况的处理
				up1 = i;
			if (j % 3 == 0)
				up2 = j;

			for (int p = up1 - 2; p <= up1; ++p)  /* 检查在3×3的小方格中是否出现了同一个数字 */
			{
				if (can == false)   /* 跳出外层循环 */
					break;
				for (int q = up2 - 2; q <= up2; ++q)
					if (Initial_State[p][q] == k)
					{
						can = false;
						break;
					}
			}
		}
		if (can)
		{
			Initial_State[i][j] = k;
			if (j<9)
			{
				if (get_Initial_State(i, j + 1))   /* 到同一行的下一位置开始搜索 */
					return true;
			}
			else
			{
				if (i < 9)
				{
					if (get_Initial_State(i + 1, 1))    /* 到下一行的第一个空格开始搜索 */
						return true;
				}
				else
					return true;  /* i >= 9  && j >= 9  , 搜索结束 */

			}
			Initial_State[i][j] = 0;   /* 关键这一步：找不到解就要回复原状，否则会对下面的搜索造成影响 */
		}
	}
	return false;  /*  1到9都尝试过都不行，则返回递归的上一步 */
}

void start()
{
	srand(unsigned(time(NULL)));  /* 产生random_shuffle的随机数种子 */
	for (int i = 1; i <= 9; ++i)
		for (int j = 1; j <= 9; ++j)
			Initial_State[i][j] = 0;

	for (int i = 1; i <= 9; ++i)
		Initial_State[1][i] = i;

	random_shuffle(&(Initial_State[1][1]), &(Initial_State[1][10]));  /* 第一行随机排列产生 */

	get_Initial_State(2, 1);  /* 从第二行开始搜索 */
}

void write_into_file(const char *file_name,const char *content,bool over_written) {
	ofstream outfile;
	if (over_written)
	{
		outfile.open(file_name);
	}
	else {
		outfile.open(file_name, ios::app);
	}
	outfile << content;
	outfile.close();

}

int main()
{
	int count;
	cout << "please enter a number" << endl;
	cin >> count;
	for (int k = 0; k < count; k++) {
		char *shudu_txt = new char[200]{'\n'};
		char *buffer = new char[1];
		start();
		for (int i = 1; i <= 9; ++i)
		{
			for (int j = 1; j <= 9; ++j) {
				strcat(shudu_txt, _itoa(Initial_State[i][j], buffer, 10));
				strcat(shudu_txt, " ");
			}
			strcat(shudu_txt, "\n");
		}
		write_into_file("shudu.txt", shudu_txt,k==0);
	}
	return 0;
}