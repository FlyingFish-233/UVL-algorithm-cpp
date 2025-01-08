# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 31 * 1e5 + 10;

int n, ans;
int cnt, trie[NR][2];

void insert(int x)
{
	int now = 0;
	for (int i = 31; i >= 0; i--) {
		int t = x >> i & 1;
		if (trie[now][t] == 0) trie[now][t] = ++cnt;
		now = trie[now][t];
	}
}

int getmax(int now, int x, int k)
{
	if (k < 0) return 0;
	int t = x >> k & 1;
	if (trie[now][!t]) return (1 << k) | getmax(trie[now][!t], x, k - 1);
	return getmax(trie[now][t], x, k - 1);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		ans = max(ans, getmax(0, x, 31));
		insert(x);
	}
	printf("%d\n", ans);
	return 0;
}