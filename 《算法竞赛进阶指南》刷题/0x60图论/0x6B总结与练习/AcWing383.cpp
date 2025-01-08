# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e3 + 10, MR = 1e4 + 10;

struct Edge
{
    int to, next, w;
};

int n, m, S, T;
int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

struct Node
{
    int x, d;
    bool operator < (const Node &cmp) const {
        return d > cmp.d;
    }
};

int dis[2][NR], cnt[2][NR];
priority_queue<Node> q;

void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis)), dis[0][s] = 0;
    memset(cnt, 0, sizeof(cnt)), cnt[0][s] = 1;
    q.push((Node) {s, 0});
    while (!q.empty()) {
        int x = q.top().x, d = q.top().d; q.pop();
        if (dis[1][x] < d) continue;
        int t = (dis[1][x] == d);
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to, w = d + g[i].w;
            if (dis[0][y] > w) {
                dis[1][y] = dis[0][y], cnt[1][y] = cnt[0][y];
                dis[0][y] = w, cnt[0][y] = cnt[t][x], q.push((Node) {y, w});
            }
            else if (dis[0][y] == w) cnt[0][y] += cnt[t][x];
            else if (dis[1][y] > w) dis[1][y] = w, cnt[1][y] = cnt[t][x], q.push((Node) {y, w});
            else if (dis[1][y] == w) cnt[1][y] += cnt[t][x];
        }
    }
}

int main()
{
    int case_num;
    scanf("%d", &case_num);
    while (case_num--) {
        scanf("%d%d", &n, &m);
        memset(fte, 0, sizeof(fte)), gsz = 0;
        for (int i = 1, x, y, w; i <= m; i++)
            scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
        scanf("%d%d", &S, &T);
        dijkstra(S);
        int ans = cnt[0][T];
        if (dis[1][T] == dis[0][T] + 1) ans += cnt[1][T];
        printf("%d\n", ans);
    }
    return 0;
}