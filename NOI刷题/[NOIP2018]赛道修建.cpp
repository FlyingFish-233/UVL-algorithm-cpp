// P5021 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <set>

using namespace std;

const int NR = 5e4 + 10;

struct Edge
{
    int to, next, w;
};

int n, m;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
    g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz;
}

int len_max, d[NR];

void getmax(int x, int fa)
{
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y == fa) continue;
        getmax(y, x), len_max = max(len_max, d[x] + d[y] + g[i].w);
        d[x] = max(d[x], d[y] + g[i].w);
    }
}

int cnt[NR], len[NR];
multiset<int> s;

void dfs(int x, int fa, int w)
{
    cnt[x] = len[x] = 0;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y != fa) dfs(y, x, w), cnt[x] += cnt[y];
    }
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y == fa) continue;
        if (len[y] + g[i].w >= w) cnt[x]++;
        else s.insert(len[y] + g[i].w);
    }
    while (!s.empty()) {
        int w1 = *s.begin(); s.erase(s.begin());
        multiset<int>::iterator it = s.lower_bound(w - w1);
        if (it == s.end()) len[x] = max(len[x], w1);
        else cnt[x]++, s.erase(it);
    }
}

bool check(int w)
{
    dfs(1, 0, w);
    return cnt[1] >= m;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, w; i <= n - 1; i++)
        scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
    getmax(1, 0);
    int l = 1, r = len_max, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}