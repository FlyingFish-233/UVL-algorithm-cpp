// P6139 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2e6 + 10;

struct Node
{
    int next[30];
    int len, fa;
};

int n;
char str[NR];

int tot = 1;
Node tree[NR];

void insert()
{
	int rt = 1, len = strlen(str);
	for (int i = 0; i < len; i++) {
		int c = str[i] - 'a'; 
		if (tree[rt].next[c] == 0) tree[rt].next[c] = ++tot;
		rt = tree[rt].next[c];
	}
}

int add(int last, int c)
{
    int np = tree[last].next[c];
    tree[np].len = tree[last].len + 1;
    int p = tree[last].fa;
    for ( ; p && tree[p].next[c] == 0; p = tree[p].fa)
        tree[p].next[c] = np;
    if (p == 0) { tree[np].fa = 1; return np; }
    int q = tree[p].next[c];
    if (tree[q].len == tree[p].len + 1) { tree[np].fa = q; return np; }
    int nq = ++tot;
    // len大于当前节点的节点不能被更新
    for (int i = 0; i < 26; i++)
    	if (tree[tree[q].next[i]].len > 0) tree[nq].next[i] = tree[q].next[i];
    tree[nq].fa = tree[q].fa;
    tree[nq].len = tree[p].len + 1;
    tree[q].fa = tree[np].fa = nq;
    for ( ; p && tree[p].next[c] == q; p = tree[p].fa)
        tree[p].next[c] = nq;
    return np;
}

queue< pair<int,int> > q;

void build()
{
	for (int i = 0; i < 26; i++)
		if (tree[1].next[i]) q.push(make_pair(1, i));
	while (!q.empty()) {
		int last = add(q.front().first, q.front().second); q.pop();
		for (int i = 0; i < 26; i++)
			if (tree[last].next[i]) q.push(make_pair(last, i));
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
    	scanf("%s", str), insert();
    build();
    long long ans = 0;
    for (int i = 2; i <= tot; i++)
    	ans += tree[i].len - tree[tree[i].fa].len;
    printf("%lld", ans);
    return 0;
}
