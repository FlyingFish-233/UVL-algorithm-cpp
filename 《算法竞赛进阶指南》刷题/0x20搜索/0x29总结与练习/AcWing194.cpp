# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int nxt[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int n, dep;
int a[10][10];
bool vis[10][10];

inline int read()
{
	int num = 0;
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		num = (num << 3) + (num << 1) + c - 48;
		c = getchar();
	}
	return num;
}

inline int f()
{
	static bool flag[10];
	memset(flag, false, sizeof(flag));
	for (register int i = 1; i <= n; i++)
		for (register int j = 1; j <= n; j++)
			if (!vis[i][j]) flag[a[i][j]] = true;
	int val = 0;
	for (register int i = 0; i <= 5; i++)
		val += flag[i];
	return val;
}

inline bool color(int c)
{
	static int l, r, q[100][2];
	l = 1, r = 0;
	for (register int i = 1; i <= n; i++)
		for (register int j = 1; j <= n; j++)
			if (vis[i][j]) q[++r][0] = i, q[r][1] = j;
	bool flag = false;
	while (l <= r) {
		int x = q[l][0], y = q[l][1]; l++;
		for (register int i = 0; i < 4; i++) {
			int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
			if (x0 >= 1 && y0 >= 1 && x0 <= n && y0 <= n && !vis[x0][y0] && a[x0][y0] == c)
				vis[x0][y0] = flag = true, q[++r][0] = x0, q[r][1] = y0;
		}
	}
	return flag;
}

inline bool dfs(int step)
{
	if (step + f() > dep) return false;
	if (f() == 0) return true;
	bool save[10][10];
	memcpy(save, vis, sizeof(vis));
	for (register int i = 0; i <= 5; i++) {
		if (!color(i)) continue;
		if (dfs(step + 1)) return true;
		memcpy(vis, save, sizeof(save));
	}
	return false;
}

int main()
{
	while (scanf("%d", &n) && n) {
		for (register int i = 1; i <= n; i++)
			for (register int j = 1; j <= n; j++)
				a[i][j] = read();
		memset(vis, false, sizeof(vis));
		vis[1][1] = true, color(a[1][1]);
		for (dep = 0; !dfs(0); dep++);
		printf("%d\n", dep);
	}
	return 0;
}