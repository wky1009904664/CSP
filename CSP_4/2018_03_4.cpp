#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<sstream>
#include<map>
#include<vector>
#include<queue>
#include<math.h>
#include<list>
using namespace std;
int mp[3][3];
bool hok(int h, int f) {
	return mp[h][0] == f && mp[h][0] == mp[h][1] && mp[h][1] == mp[h][2];          //�ж����Ƿ���������
}
bool lok(int l, int f) {
	return mp[0][l] == f && mp[0][l] == mp[1][l] && mp[1][l] == mp[2][l];          //�ж����Ƿ���������
}

int spa() {
	int res = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (!mp[i][j])
				res++;
	return res;
}

int win(int f) {
	int wi = 0, ans = 1;
	if (hok(0, f) || hok(1, f) || hok(2, f))wi = 1;
	if (lok(0, f) || lok(1, f) || lok(2, f))wi = 1;
	if (mp[0][0] == f && mp[0][0] == mp[1][1] && mp[1][1] == mp[2][2])wi = 1;
	if (mp[0][2] == f && mp[0][2] == mp[1][1] && mp[1][1] == mp[2][0])wi = 1;
	if (!wi)return 0;
	ans += spa();
	return (f == 1) ? ans : -ans;
}


int dfs(int peo) {  
	if (!spa())return 0;
	int Max = -10, Min = 10;
	for (int i = 0; i < 3; i++) {
		for (int j = 0, w; j < 3; j++) {
			if (!mp[i][j]) {   
				mp[i][j] = peo + 1;
				w = win(peo + 1);
				if (w) {
					mp[i][j] = 0;
					return w > 0 ? max(Max, w) : min(Min, w);
				}
				if (!peo)Max = max(Max, dfs(1));
				else    Min = min(Min, dfs(0));
				mp[i][j] = 0;
			}
		}
	}
	return peo ? Min : Max;
}

int main(void)
{	/*
	����DFS(i)Ϊ��ǰ�����£���i(i==0��1)�����µ�ʱ�򣬸����ܻ�õ�"���ֵ"��
	������ǰ����Alice�£���ô����Alice���µ�����λ�ã����غ������н�������վ�������ֵ��
	������ǰ��ʱBob�£���ô����Bob���µ�����λ�ã����غ������н�������վ������Сֵ��
	���������ݱȽ�С�����Ҳ��9���Σ�ֱ���������ɣ������ݱȽϴ�ʱ��Ӧ���õ�alpha-beta��֦��
	*/
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int p = 0; p < 3; p++)
			for (int q = 0; q < 3; q++)
				cin >> mp[p][q];
		int x = win(1);
		int y = win(2);
		if (x) {
			cout << x << endl;
			continue;
		}
		if (y) {
			cout << y << endl;
			continue;
		}
		cout << dfs(0) << endl;

	}

	return 0;
}
