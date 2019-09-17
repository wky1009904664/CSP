#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N = 500 + 10;
const ll inf = 1e18; //��Ҫ��long long����Ȼ���������1e6�����м�ֵ��Ȼ���ܱ�int������Ϊ���80�֣������� 
bool vis[N];
int que[N];
ll dist[N], dist0[N]; //ǰ��Ϊ��·��ǰ��ΪС·�ֱ������� 
ll g[N][N], g0[N][N]; //��·�ڽӾ����С·�ڽӾ��� 
void SPFA(int start, int n)
{
	int front = 0, rear = 0;
	for (int v = 1; v <= n; v++)
	{
		if (v == start)
		{
			que[rear++] = v;
			vis[v] = true;
			dist[v] = dist0[v] = 0;
		}
		else
		{
			vis[v] = false;
			dist[v] = dist0[v] = inf;
		}
	}
	while (front != rear)
	{
		int u = que[front++];
		vis[u] = false;
		if (front >= N)front = 0;
		for (int i = 1; i <= n; i++)
		{
			ll v = g[u][i];
			if (dist[i] > dist[u] + v) //�ߴ�· 
			{
				dist[i] = dist[u] + v;
				if (!vis[i])
				{
					vis[i] = true;
					que[rear++] = i;
					if (rear >= N)rear = 0;
				}
			}
			if (dist[i] > dist0[u] + v) //�ߴ�· 
			{
				dist[i] = dist0[u] + v;
				if (!vis[i])
				{
					vis[i] = true;
					que[rear++] = i;
					if (rear >= N)rear = 0;
				}
			}
			if (g0[u][i] != inf) //���С·�ܵ��� 
			{
				v = g0[u][i] * g0[u][i];
				if (dist0[i] > dist[u] + v) //��С· ��ǰ��ΪС·ʱ������С· 
				{
					dist0[i] = dist[u] + v;
					if (!vis[i])
					{
						vis[i] = true;
						que[rear++] = i;
						if (rear >= N)rear = 0;
					}
				}
			}
		}
	}
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	ll t, a, b, c;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			g[i][j] = g0[i][j] = inf;
	for (int i = 0; i < m; i++)
	{
		scanf("%lld%lld%lld%lld", &t, &a, &b, &c);
		if (t&&g0[a][b] > c) g0[a][b] = g0[b][a] = c;
		if (!t&&g[a][b] > c) g[a][b] = g[b][a] = c;
	}
	for (int i = 1; i <= n; i++) //������floyd���ȼ����ֻ��С·ʱ������֮�����̾���
		for (int j = i + 1; j <= n; j++)
		{
			for (int k = 1; k <= n; k++)
			{
				if (k == i || k == j) continue;
				if (g0[i][j] > g0[i][k] + g0[k][j]) g0[i][j] = g0[j][i] = g0[i][k] + g0[k][j];
			}
		}
	SPFA(1, n); //spfa 
	printf("%lld\n", min(dist[n], dist0[n]));
	return 0;
}