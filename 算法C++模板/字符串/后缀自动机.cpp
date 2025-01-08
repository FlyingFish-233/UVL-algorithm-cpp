# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 2e6 + 10;

struct Node
{
    int next[30];
    int len, fa;
};

int tot = 1, last = 1;
Node tree[NR];
int sz[NR];

void add(int c)
{
    int p = last, np = last = ++tot; sz[np] = 1;
    tree[np].len = tree[p].len + 1;
    for ( ; p && tree[p].next[c] == 0; p = tree[p].fa)
        tree[p].next[c] = np;
    if (p == 0) { tree[np].fa = 1; return; }
    int q = tree[p].next[c];
    if (tree[q].len == tree[p].len + 1) { tree[np].fa = q; return; }
    int nq = ++tot; tree[nq] = tree[q];
    tree[nq].len = tree[p].len + 1;
    tree[q].fa = tree[np].fa = nq;
    for ( ; p && tree[p].next[c] == q; p = tree[p].fa)
        tree[p].next[c] = nq;
}

char str[NR];
vector<int> g[NR];
long long ans;

void dfs(int x)
{
    for (int i = 0; i < (int) g[x].size(); i++)
        dfs(g[x][i]), sz[x] += sz[g[x][i]];
    if (sz[x] != 1) ans = max(ans, 1ll * sz[x] * tree[x].len);
}

int main()
{
    scanf("%s", str);
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        add(str[i] - 'a');
    for (int i = 2; i <= tot; i++)
        g[tree[i].fa].push_back(i);
    dfs(1);
    printf("%lld\n", ans);
    return 0;
}