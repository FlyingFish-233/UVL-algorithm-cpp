# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>

using namespace std;

const int NR = 210, MR = 1e4 + 10;

int n, m;
int u[MR], v[MR], id[NR];

bool check(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 || x1 == y2 || y1 == x2 || y1 == y2) return false;
    if (x1 > y1) swap(x1, y1);
    return (x1 < x2 && x2 < y1) ^ (x1 < y2 && y2 < y1);
}

int fa[MR << 1];

int find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    fa[find(x)] = find(y);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++)
            scanf("%d%d", &u[i], &v[i]);
        for (int i = 1, x; i <= n; i++)
            scanf("%d", &x), id[x] = i;
        if (m > 3 * n + 6) { printf("NO\n"); continue; }
        for (int i = 1; i <= 2 * m; i++) fa[i] = i;
        for (int i = 1; i <= m; i++)
            for (int j = i + 1; j <= m; j++)
                if (check(id[u[i]], id[v[i]], id[u[j]], id[v[j]]))
                    merge(i, j + m), merge(i + m, j);
        bool flag = true;
        for (int i = 1; i <= m; i++)
            if (find(i) == find(i + m)) { flag = false; break; }
        if (flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}