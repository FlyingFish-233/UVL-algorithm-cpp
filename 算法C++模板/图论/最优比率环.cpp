// AcWing361 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e4 + 10;
const double eps = 1e-4;

struct Edge
{
    int to, next; double w;
};

int n, m;
int a[NR], b[NR], w[NR], v[NR];
int gsz, fte[NR];
Edge g[NR];

void addEdge(int x, int y, double w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

queue<int> q;
double dis[NR];
bool already[NR];
int len[NR];

bool spfa(int s)
{
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) dis[i] = 1e9;
    memset(len, 0, sizeof(len)), dis[s] = 0;
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
            if (!already[y]) q.push(y), already[y] = true;
        }
    }
    return true;
}

bool check(double mid)
{
    memset(fte, 0, sizeof(fte)), gsz = 0;
    for (int i = 1; i <= m; i++)
        addEdge(a[i], b[i], mid * w[i] - v[b[i]]);
    return spfa(1);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &a[i], &b[i], &w[i]);
    double l = 0, r = 2000, ans = 0;
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (check(mid)) ans = r = mid;
        else l = mid;
    }
    printf("%.2f\n", ans);
    return 0;
}