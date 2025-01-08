# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <map>

using namespace std;

const int NR = 1e5 + 10;

struct Edge
{
    int to, next, w;
};

int n, m;
map<string, int> mp;

int gsz, fte[NR];
Edge g[NR];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

int value(char c)
{
    if (c == 'S') return 1000;
    if (c == 'G') return 500;
    if (c == 'D') return 300;
    if (c == 'T') return 200;
    return 150;
}

double dis[NR];
bool vis[NR], flag;

bool spfa(int x, double mid)
{
    vis[x] = true;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (dis[y] <= dis[x] + mid - g[i].w) continue;
        dis[y] = dis[x] + mid - g[i].w;
        if (vis[y] || !spfa(y, mid)) return false;
    }
    vis[x] = false;
    return true;
}

bool check(double mid)
{
    for (int i = 1; i <= n; i++)
        dis[i] = 0, vis[i] = false;
    for (int i = 1; i <= n; i++)
        if (!spfa(i, mid)) return false;
    return true;
}

int main()
{
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        string s, s1, s2 = ""; int w = 0;
        cin >> s;
        bool first_time = true; 
        for (int i = 0; i < (int) s.size(); i++) {
            if (s[i] == '-') {
                if (first_time) first_time = false, s1 = s2;
                w += value(s2[0]), s2 = "";
            }
            else s2 += s[i];
        }
        w += value(s2[0]);
        if (mp.count(s1) == 0) mp[s1] = ++n;
        if (mp.count(s2) == 0) mp[s2] = ++n;
        addEdge(mp[s1], mp[s2], w);
    }
    if (check(0)) return printf("-1\n"), 0;
    double l = 0, r = 2e4, ans;
    while (r - l > 0.01) {
        double mid = (l + r) / 2;
        if (check(mid)) ans = r = mid;
        else l = mid;
    }
    printf("%.0f\n", ans);
    return 0;
}