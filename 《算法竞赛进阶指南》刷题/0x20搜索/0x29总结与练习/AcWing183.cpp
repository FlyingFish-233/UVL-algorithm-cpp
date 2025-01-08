# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = (1 << 9) + 10;
const int lim = (1 << 9) - 1;

const int a[10][10] = { {0, 0, 0, 1, 1, 1, 2, 2, 2},
				  		{0, 0, 0, 1, 1, 1, 2, 2, 2},
				  		{0, 0, 0, 1, 1, 1, 2, 2, 2},
				  		{3, 3, 3, 4, 4, 4, 5, 5, 5},
				  		{3, 3, 3, 4, 4, 4, 5, 5, 5},
				  		{3, 3, 3, 4, 4, 4, 5, 5, 5},
				 		{6 ,6 ,6, 7, 7, 7, 8, 8, 8},
				 		{6 ,6 ,6, 7, 7, 7, 8, 8, 8},
				 		{6 ,6 ,6, 7, 7, 7, 8, 8, 8} };

const int score[10][10] = { {6, 6, 6, 6, 6, 6, 6, 6, 6},
				  			{6, 7, 7, 7, 7, 7, 7, 7, 6},
				  			{6, 7, 8, 8, 8, 8, 8, 7, 6},
				  			{6, 7, 8, 9, 9, 9, 8, 7, 6},
				  			{6, 7, 8, 9,10, 9, 8, 7, 6},
				  			{6, 7, 8, 9, 9, 9, 8, 7, 6},
				 			{6, 7, 8, 8, 8, 8, 8, 7, 6},
				 			{6, 7, 7, 7, 7, 7, 7, 7, 6},
				 			{6, 6, 6, 6, 6, 6, 6, 6, 6} };

int num[10][10];
int row[10], col[10], block[10];
int cnt[NR], pos[NR];
int ans = -1;

int lowbit(int x)
{
	return x & (-x);
}

void change(int x, int y, int t)
{
	row[x] ^= 1 << t;
	col[y] ^= 1 << t;
	block[a[x][y]] ^= 1 << t;
}

void solve(int sum)
{
	int x = -1, y = -1, v = -1;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (num[i][j] == -1) {
				int now = row[i] & col[j] & block[a[i][j]];
				if (v == -1 || cnt[now] < cnt[v]) x = i, y = j, v = now;
			}
	if (v == -1) {
		ans = max(ans, sum);
		return;
	}
	for (int i = v; i > 0; i -= lowbit(i)) {
		int t = pos[lowbit(i)];
		change(x, y, num[x][y] = t);
		solve(sum + (t + 1) * score[x][y]);
		change(x, y, t), num[x][y] = -1;
	}
}

int main()
{
	for (int i = 0; i < 9; i++)
		row[i] = col[i] = block[i] = lim;
	for (int i = 0; i <= lim; i++)
		for (int j = i; j > 0; j -= lowbit(j))
			cnt[i]++;
	for (int i = 0; i < 9; i++)
		pos[1 << i] = i;
	int sum = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			scanf("%d", &num[i][j]);
			sum += num[i][j] * score[i][j];
			if (--num[i][j] >= 0) change(i, j, num[i][j]);
		}
	solve(sum);
	printf("%d\n", ans);
	return 0;
}