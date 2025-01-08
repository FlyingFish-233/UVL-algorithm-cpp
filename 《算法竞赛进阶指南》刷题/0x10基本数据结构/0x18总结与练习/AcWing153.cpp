# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>

using namespace std;

const int NR = 1e3 + 10;

int n;
int a[NR], a_min[NR];
bool g[NR][NR];
int color[NR];
stack<int> s1, s2;

bool dfs(int x, bool flag)
{
	color[x] = flag;
	for (int y = 1; y <= n; y++) {
		if (!g[x][y]) continue;
		if (color[y] == flag) return false;
		if (color[y] == -1 && !dfs(y, !flag)) return false;
	}
	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	a_min[n + 1] = 2e9;
	for (int i = n; i >= 1; i--)
		a_min[i] = min(a_min[i + 1], a[i]);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (a[i] < a[j] && a_min[j + 1] < a[i])
				g[i][j] = g[j][i] = true;
	memset(color, -1, sizeof(color));
	for (int i = 1; i <= n; i++)
		if (color[i] == -1 && !dfs(i, 0)) {
			printf("0\n");
			return 0;
		}
	int now = 1;
	for (int i = 1; i <= n; i++) {
		if (color[i] == 0) {
			while (!s1.empty() && s1.top() == now)
				s1.pop(), printf("b "), now++;
			s1.push(a[i]), printf("a ");
			continue;
		}
		while (true) {
			if (!s1.empty() && s1.top() == now)
				s1.pop(), printf("b "), now++;
			else if (!s2.empty() && s2.top() == now)
				s2.pop(), printf("d "), now++;
			else break;
		}
		s2.push(a[i]), printf("c ");
	}
	while (true) {
		if (!s1.empty() && s1.top() == now)
			s1.pop(), printf("b "), now++;
		else if (!s2.empty() && s2.top() == now)
			s2.pop(), printf("d "), now++;
		else break;
	}
	puts("");
	return 0;
}