// P3385 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e4 + 10, MR = 5e5 + 10;

struct Edge
{
    int to, next, w;
};

int n, m;
int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

queue<int> q;
int dis[NR], len[NR];
bool already[NR];

bool spfa(int s)
{
    while (!q.empty()) q.pop();
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    memset(len, 0, sizeof(len));
    memset(already, false, sizeof(already));

    q.push(s), already[s] = true;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        already[x] = false;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] <= dis[x] + g[i].w) continue;
            dis[y] = dis[x] + g[i].w, len[y] = len[x] + 1;
            if (len[y] >= n) return false;
            if (!already[y]) {
                // if (++cnt[y] >= n) return false; 另一种判负环的方式
                q.push(y), already[y] = true;
            }
        }
    }
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(fte, 0, sizeof(fte)), gsz = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1, x, y, w; i <= m; i++) {
            scanf("%d%d%d", &x, &y, &w);
            addEdge(x, y, w);
            if (w >= 0) addEdge(y, x, w);
        }
        if (!spfa(1)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}