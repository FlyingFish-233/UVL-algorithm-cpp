# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 30, MR = 100;

struct Edge
{
    int to, next, w;
};

int n;
int r[NR], c[NR];
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
    memset(dis, -0x3f, sizeof(dis)), dis[s] = 0;
    memset(len, 0, sizeof(len));
    memset(already, false, sizeof(already));
    while (!q.empty()) q.pop();
    q.push(s), already[s] = true;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        already[x] = false;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] >= dis[x] + g[i].w) continue;
            dis[y] = dis[x] + g[i].w, len[y] = len[x] + 1;
            if (len[y] >= 25) return false;
            if (!already[y]) q.push(y), already[y] = true;
        }
    }
    return true;
}

bool check(int s_24)
{
    memset(fte, 0, sizeof(fte)), gsz = 0;
    for (int i = 1; i <= 24; i++) {
        addEdge(i - 1, i, 0), addEdge(i, i - 1, -c[i]);
        if (i >= 8) addEdge(i - 8, i, r[i]);
        else addEdge(i + 16, i, r[i] - s_24);
    }
    addEdge(0, 24, s_24), addEdge(24, 0, -s_24);
    return spfa(0);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= 24; i++)
            scanf("%d", &r[i]);
        scanf("%d", &n);
        for (int i = 1, t; i <= n; i++)
            scanf("%d", &t), c[t + 1]++;
        bool find_answer = false;
        for (int i = 0; i <= n; i++)
            if (check(i)) {
                printf("%d\n", i), find_answer = true;
                break;
            }
        if (!find_answer) printf("No Solution\n");
    }
    return 0;
}