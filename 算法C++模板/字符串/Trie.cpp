// AcWing142 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

struct Node
{
	int next[26], cnt;
};

int n, m;
char s[NR];

int cnt;
Node trie[NR];

void insert()
{
	int now = 0, len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (trie[now].next[s[i] - 'a'] == 0) trie[now].next[s[i] - 'a'] = ++cnt;
		now = trie[now].next[s[i] - 'a'];
	}
	trie[now].cnt++;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", s), insert();
	while (m--) {
		scanf("%s", s);
		int ans = 0, now = 0, len = strlen(s);
		for (int i = 0; i < len; i++) {
			if (trie[now].next[s[i] - 'a'] == 0) break;
			now = trie[now].next[s[i] - 'a'];
			ans += trie[now].cnt;
		}
		printf("%d\n", ans);
	}
	return 0;
}