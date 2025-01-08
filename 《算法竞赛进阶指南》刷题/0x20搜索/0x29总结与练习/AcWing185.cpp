# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int n;
int c[10][10];
int a[10], b[10], face[10];

bool empty()
{
	for (int i = 0; i < 5; i++)
		if (c[i][0]) return false;
	return true;
}

void drop()
{
	for (int i = 0; i < 5; i++) {
		int cnt = 0;
		for (int j = 0; j < 7; j++)
			if (c[i][j]) c[i][cnt++] = c[i][j];
		for (int j = cnt; j < 7; j++)
			c[i][j] = 0;
	}
}

bool remove()
{
	static bool flag[10][10];
	memset(flag, false, sizeof(flag));
	bool is_change = false;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++) {
			if (i - 1 >= 0 && i + 1 < 5 && c[i][j] != 0 && c[i][j] == c[i - 1][j] && c[i][j] == c[i + 1][j])
				is_change = flag[i][j] = flag[i - 1][j] = flag[i + 1][j] = true;
			if (j - 1 >= 0 && j + 1 < 7 && c[i][j] != 0 && c[i][j] == c[i][j - 1] && c[i][j] == c[i][j + 1])
				is_change = flag[i][j] = flag[i][j - 1] = flag[i][j + 1] = true;
		}
	if (!is_change) return false;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++)
			if (flag[i][j]) c[i][j] = 0;
	return true;
}

void change(int x, int y, int k)
{
	swap(c[x][y], c[x + k][y]), drop();
	while (remove()) drop();
}

void dfs(int step)
{
	if (step > n) {
		if (!empty()) return;
		for (int i = 1; i <= n; i++)
			printf("%d %d %d\n", a[i], b[i], face[i]);
		exit(0);
	}
	int save[10][10];
	memcpy(save, c, sizeof(c));
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++)
			for (int k = 1; k >= -1; k -= 2) {
				if (i + k < 0 || i + k >= 5 || c[i][j] == 0 || c[i][j] == c[i + k][j]) continue;
				if (k == -1 && c[i + k][j]) continue;
				change(a[step] = i, b[step] = j, face[step] = k);
				dfs(step + 1);
				memcpy(c, save, sizeof(save));
			}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0, x; i < 5; i++)
		for (int j = 0; scanf("%d", &x) && x; j++)
			c[i][j] = x;
	dfs(1);
	printf("-1\n");
	return 0;
}