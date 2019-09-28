#include<stdio.h>
#include<iostream>
#include<cmath>
#include<fstream> 
#include<stdlib.h>
using namespace std;
int Sudoku[10][10];
int result[10000];
int outnum = 0;
void input(int m, int a[10][10])
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			Sudoku[i][j] = a[i][j];
		}
	}
}
void save(int m)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			result[outnum] = Sudoku[i][j];
			outnum++;
		}
	}
}
void output(int m)
{
	int i;
	ofstream outfile;
	outfile.open("output.txt");
	if (!outfile.is_open())
		cout << "error" << endl;
	cout << endl;
	outfile << endl;
	int q = m * m;
	for (i = 0; i < outnum; i++)
	{
		cout << result[i];
		outfile << result[i];
		if ((i + 1) % m == 0)
		{
			if ((i + 1) % q == 0)
			{
				cout << endl;
				outfile << endl;
			}
			cout << endl;
			outfile << endl;
		}
		else
		{
			cout << " ";
			outfile << " ";
		}

	}

}
bool rightSudoku(int num, int m)
{
	int a, b, i, j, row, col;
	row = num / m; col = num % m;
	for (i = 0; i < m; i++)
	{
		if (Sudoku[row][i] == Sudoku[row][col] && i != col)
			return false;
	}//每行遍历 
	for (i = 0; i < m; i++)
	{
		if (Sudoku[i][col] == Sudoku[row][col] && i != row)
			return false;
	}//每列遍历 
	int x, y;
	if (m == 5 || m == 7)
		return true;
	else
	{
		if (m == 9 || m == 4 || m == 3)
		{
			a = int(sqrt(m));
			b = int(sqrt(m));
		}

		if (m == 6)
		{
			a = 2; b = 3;
		}
		x = row / a * a;
		y = col / b * b;
		for (i = x; i < x + a; i++)
		{
			for (j = y; j < y + a; j++)
			{
				if (Sudoku[row][col] == Sudoku[i][j] && i != row && j != col)
					return false;
			}
		} //每宫遍历 
	}
	return true;
}

void back(int num, int m)
{
	if (num == m * m)
		save(m);
	int i;
	int row = num / m;
	int col = num % m;//得到坐标 
	if (Sudoku[row][col] == 0)
	{
		for (i = 1; i <= m; i++)
		{
			Sudoku[row][col] = i;
			if (rightSudoku(num, m) == 1)
				back(num + 1, m);//数字符合要求判断下一位 
		}
		Sudoku[row][col] = 0;//不符合要求则回溯
	}
	else back(num + 1, m);
}
int main(int argc, char**argv)
{
	int n, m, i, j;
	m = atoi(argv[2]);
	n = atoi(argv[4]);
	int a[10][10];
	char c;
	ifstream infile;
	infile.open("input.txt");
	if (!infile.is_open())
		cout << "error" << endl;
	for (n; n > 0; n--)
	{
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < m; j++)
			{
				infile >> c;
				a[i][j] = c - 48;
			}
		}
		input(m, a);
		back(0, m);
	}
	infile.close();
	output(m);
	getchar();
	return 0;
}