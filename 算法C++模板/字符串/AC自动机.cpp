// P5357 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 2e5 + 10, MR = 2e6 + 10;

struct Node
{
	int next[30], fail, cnt;
	vector <int> id;
};

int n, now;
char s[MR];
Node tree[NR];
int q[NR], ans[NR];

void insert(int x)
{
	int rt = 0, len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (tree[rt].next[s[i] - 'a'] == 0) tree[rt].next[s[i] - 'a'] = ++now;
		rt = tree[rt].next[s[i] - 'a'];
	}
	tree[rt].id.push_back(x);
}

void build()
{
	int l = 1, r = 0;
	for (int i = 0; i < 26; i++)
		if (tree[0].next[i]) q[++r] = tree[0].next[i];
	while (l <= r) {
		int rt = q[l++];
		for (int i = 0; i < 26; i++) {
			if (tree[rt].next[i] == 0) {
				tree[rt].next[i] = tree[tree[rt].fail].next[i];
				continue;
			}
			tree[tree[rt].next[i]].fail = tree[tree[rt].fail].next[i];
			q[++r] = tree[rt].next[i];
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%s", s), insert(i);
	build();
	scanf("%s", s);
	int rt = 0, len = strlen(s);
	for (int i = 0; i < len; i++)
		rt = tree[rt].next[s[i] - 'a'], tree[rt].cnt++;
	for (int i = now; i >= 1; i--) {
		for (int j = 0; j < (int) tree[q[i]].id.size(); j++)
			ans[tree[q[i]].id[j]] = tree[q[i]].cnt;
		tree[tree[q[i]].fail].cnt += tree[q[i]].cnt;
	}
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
    return 0;
}