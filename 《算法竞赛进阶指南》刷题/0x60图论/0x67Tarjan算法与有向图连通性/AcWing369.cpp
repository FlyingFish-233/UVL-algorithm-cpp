# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e5 + 10, MR = 2e5 + 10;
const int mod = 1e9 + 7, INF = 0x3f3f3f3f;

int n, m, S, T, Q;
int u[MR], v[MR], w[MR];

struct Edge
{
    int to, next, w;
};

int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int z)
{
    g[++gsz] = (Edge) {y, fte[x], z};
    fte[x] = gsz;
}

queue<int> q;
int in[NR], cnt[2][NR];
int dis[NR], pre[NR];

void topSort(int s, bool op)
{
    memset(cnt[op], 0, sizeof(cnt[op])), cnt[op][s] = 1;
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    memset(pre, 0, sizeof(pre));
    for (int i = 1; i <= n; i++)
        if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            (cnt[op][y] += cnt[op][x]) %= mod;
            if (dis[y] > dis[x] + g[i].w) dis[y] = dis[x] + g[i].w, pre[y] = i;
            if (--in[y] == 0) q.push(y);
        }
    }
}

bool bridge[MR];
int len, a[NR], b[NR];
int s1[NR], s2[NR];
int f[3][NR];

void dp(int op, int k)
{
    for (int i = 1; i <= len; i++)
        s1[i] = s1[i - 1] + a[i], s2[i] = s2[i - 1] + b[i];
    memset(f[op], 0, sizeof(f[op]));
    for (int l = 0, r = 1; r <= len; r++) {
        while (s1[r] - s1[l] > k) l++;
        f[op][r] = max(f[op][r - 1], s2[r] - s2[l]);
        if (l > 0 && s2[l] - s2[l - 1] > 0)
            f[op][r] = max(f[op][r], (s2[r] - s2[l]) + k - (s1[r] - s1[l]));
    }
}

int main()
{
    int L;
    scanf("%d", &L);
    while (L--) {
        scanf("%d%d%d%d%d", &n, &m, &S, &T, &Q), S++, T++;
        for (int i = 1; i <= m; i++)
            scanf("%d%d%d", &u[i], &v[i], &w[i]), u[i]++, v[i]++;

        memset(fte, 0, sizeof(fte)), gsz = 0;
        memset(in, 0, sizeof(in));
        for (int i = 1; i <= m; i++)
            addEdge(v[i], u[i], w[i]), in[u[i]]++;
        topSort(T, 1);

        memset(fte, 0, sizeof(fte)), gsz = 0;
        memset(in, 0, sizeof(in));
        for (int i = 1; i <= m; i++)
            addEdge(u[i], v[i], w[i]), in[v[i]]++;
        topSort(S, 0);
        if (dis[T] == INF) { printf("-1\n"); continue; }

        memset(bridge, false, sizeof(bridge));
        for (int i = 1; i <= m; i++)
            if (1ll * cnt[0][u[i]] * cnt[1][v[i]] % mod == cnt[0][T]) bridge[i] = true;

        len = 0;
        for (int y = T; y != S; y = u[pre[y]])
            a[++len] = g[pre[y]].w, b[len] = bridge[pre[y]] * g[pre[y]].w;
        dp(1, Q), reverse(f[1], f[1] + len + 1);
        reverse(a + 1, a + len + 1), reverse(b + 1, b + len + 1), dp(0, Q), dp(2, 2 * Q);
        int ans = f[2][len];
        for (int i = 1; i <= len; i++)
            ans = max(ans, f[0][i] + f[1][i]);
        printf("%d\n", s2[len] - ans);
    }
    return 0;
}