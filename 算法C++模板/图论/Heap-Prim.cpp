// P3366 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 5e3 + 10, MR = 2e5 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
    int to, next, w;
};

int n, m;
int gsz, fte[NR];
Edge g[MR << 1];

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

int dis[NR];
priority_queue<Node> q;
bool flag[NR];

int heap_prim()
{
    memset(dis, 0x3f, sizeof(dis));
    q.push((Node) {1, dis[1] = 0});
    int ans = 0, cnt = 0;
    while (!q.empty()) {
        int x = q.top().x; q.pop();
        if (flag[x]) continue;
        flag[x] = true, ans += dis[x], cnt++;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] > g[i].w)
                q.push((Node) {y, dis[y] = g[i].w});
        }
    }
    if (cnt < n) return -1;
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w), addEdge(y, x, w);
    int ans = heap_prim();
    if (ans == -1) printf("orz\n");
    else printf("%d\n", ans);
    return 0;
}