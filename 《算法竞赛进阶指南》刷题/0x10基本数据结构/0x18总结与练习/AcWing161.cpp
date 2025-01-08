# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

int n, cnt;
char c[10];
int trie[NR][10], s[NR];

void insert()
{
	int now = 0, len = strlen(c);
	for (int i = 0; i < len; i++) {
		int t = c[i] - '0';
		if (trie[now][t] == 0) trie[now][t] = ++cnt;
		now = trie[now][t];
	}
	s[now]++;
}

bool bfs()
{
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i <= 9; i++) {
			int y = trie[x][i];
			if (y == 0) continue;
			s[y] += s[x];
			q.push(y);
		}
	}
	for (int i = 1; i <= cnt; i++)
		if (s[i] > 1) return false;
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		cnt = 0;
		memset(trie, 0, sizeof(trie));
		memset(s, 0, sizeof(s));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%s", c), insert();
		if (bfs()) puts("YES");
		else puts("NO");
	}
	return 0;
}