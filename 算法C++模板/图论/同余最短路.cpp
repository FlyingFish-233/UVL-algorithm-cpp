// P3403 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

struct Edge
{
    int to, next, w;
};

long long H; int X, Y, Z;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

long long dis[NR];
queue<int> q;
bool already[NR];

void spfa(int s)
{
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 1;
    q.push(s), already[s] = true;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        already[x] = false;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] <= dis[x] + g[i].w) continue;
            dis[y] = dis[x] + g[i].w;
            if (!already[y]) q.push(y), already[y] = true;
        }
    }
}

// 有多少个k满足, 存在a,b,c使1 + a*X + b*Y + c*Z = k
int main()
{
    scanf("%lld", &H);
    scanf("%d%d%d", &X, &Y, &Z);
    if (X == 1 || Y == 1 || Z == 1) return printf("%lld\n", H), 0;
    for (int i = 0; i < X; i++)
        addEdge(i, (i + Y) % X, Y), addEdge(i, (i + Z) % X, Z);
    spfa(1);
    long long ans = 0;
    for (int i = 0; i < X; i++)
        if (dis[i] <= H) ans += (H - dis[i]) / X + 1; // dis[i]为1 + b*Y + c*Z可表示出的模X余i的最小数
    printf("%lld\n", ans);
    return 0;
}