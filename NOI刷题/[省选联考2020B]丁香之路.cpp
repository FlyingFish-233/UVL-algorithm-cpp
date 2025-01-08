// P6628 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2500 + 10;

struct Edge
{
    int u, v, w;
    bool operator < (const Edge &cmp) const {
        return w < cmp.w;
    }
};

int n, m, s;
int deg[NR];
long long sum;

int fa[NR], fa0[NR];

int find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    fa[find(x)] = find(y);
}

int gsz;
Edge g[NR * NR];

/*
s -> t的路径: 所有点度数均为偶数(在s,t之间补上一条边)
1.先把m条丁香之路和(s,t)连上
2.取所有度数为奇数的点: a1, a2, ... , ak
  连接(a1, a1+1), (a1+1, a1+2), ... , (a2-1, a2)
  同理对(a3, a4), (a5, a6)等进行处理, 这样所有点度数为偶数
3.所有点被分为了几个连通块, 做最小生成树将它们连起来(最小生成树的每条边将被通过2次)
4.ans[t] = m条丁香之路的长度 + 第2步所加边的长度 + 2 * 最小生成树边的长度
*/
int main()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);
        deg[x]++, deg[y]++, merge(x, y);
        sum += abs(x - y);
    }
    memcpy(fa0, fa, sizeof(fa));
    for (int t = 1; t <= n; t++) {
        long long ans = sum;
        memcpy(fa, fa0, sizeof(fa0));
        deg[s]++, deg[t]++, merge(s, t);
        for (int i = 1, pre = 0; i <= n; i++) if (deg[i] & 1) {
            if (pre) {
                ans += i - pre;
                for (int j = pre; j < i; j++)
                    merge(i, j);
                pre = 0;
            }
            else pre = i;
        }
        gsz = 0;
        for (int i = 1, pre = 0; i <= n; i++) if (deg[i]) {
            if (pre && find(pre) != find(i))
                g[++gsz] = (Edge) {pre, i, i - pre};
            pre = i;
        }
        sort(g + 1, g + gsz + 1);
        for (int i = 1; i <= gsz; i++)
            if (find(g[i].u) != find(g[i].v))
                ans += 2 * g[i].w, merge(g[i].u, g[i].v);
        printf("%lld ", ans);
        deg[s]--, deg[t]--;
    }
    return 0;
}