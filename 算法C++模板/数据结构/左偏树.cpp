// P3377 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

struct Node
{
    int ls, rs, d, val, id;
};

int n, m;
Node h[NR];
int root[NR];
bool flag[NR];

int merge(int x, int y)
{
    if (x == 0 || y == 0) return x + y;
    if (h[x].val > h[y].val || (h[x].val == h[y].val && h[x].id > h[y].id)) swap(x, y);
    h[x].rs = merge(h[x].rs, y);
    if (h[h[x].ls].d < h[h[x].rs].d) swap(h[x].ls, h[x].rs);
    h[x].d = h[h[x].rs].d + 1;
    return x;
}

int find(int x)
{
    if (root[x] == x) return x;
    return root[x] = find(root[x]);
}

int main()
{
    scanf("%d%d", &n, &m);
    h[0].d = -1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i].val), root[i] = h[i].id = i;
    while (m--) {
        int op, x, y;
        scanf("%d%d", &op, &x);
        if (op == 1) {
            scanf("%d", &y);
            if (flag[x] || flag[y]) continue;
            x = find(x), y = find(y);
            if (x != y) root[x] = root[y] = merge(x, y);
        }
        if (op == 2) {
            if (flag[x]) { printf("-1\n"); continue; }
            x = find(x);
            printf("%d\n", h[x].val);
            flag[x] = true;
            // 这里必须更新root[x], 虽然x已被删除, 但有可能有root[y]=x, 需要让root[y]也更新
            root[h[x].ls] = root[h[x].rs] = root[x] = merge(h[x].ls, h[x].rs);
            h[x].ls = h[x].rs = h[x].d = 0;
        }
    }
    return 0;
}