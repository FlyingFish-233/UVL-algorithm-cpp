// P5787 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 2e5 + 10;

int n, m, k;
int u[NR], v[NR];
vector<int> tree[NR << 2];

void modify(int rt, int l, int r, int l0, int r0, int x)
{
    if (l0 <= l && r <= r0) { tree[rt].push_back(x); return; }
    if (l0 <= mid) modify(ls, l, mid, l0, r0, x);
    if (mid < r0) modify(rs, mid + 1, r, l0, r0, x);
}

int fa[NR], sz[NR];
int top, st[NR][2];

int find(int x)
{
    if (fa[x] == x) return x;
    return find(fa[x]);
}

void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y) return;
    if (sz[x] > sz[y]) swap(x, y);
    fa[x] = y, sz[y] += sz[x];
    st[++top][0] = x, st[top][1] = y;
}

void cancel()
{
    fa[st[top][0]] = st[top][0];
    sz[st[top][1]] -= sz[st[top][0]];
    top--;
}

void solve(int rt, int l, int r)
{
    bool flag = true; int save = top;
    for (int i = 0; i < (int) tree[rt].size(); i++) {
        int x = u[tree[rt][i]], y = v[tree[rt][i]];
        if (find(x) == find(y)) {
            for (int j = l; j <= r; j++)
                printf("No\n");
            flag = false;
            break;
        }
        merge(x, y + n), merge(x + n, y);
    }
    if (flag) {
        if (l == r) printf("Yes\n");
        else solve(ls, l, mid), solve(rs, mid + 1, r);
    }
    while (top != save) cancel();
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, l, r; i <= m; i++)
        scanf("%d%d%d%d", &u[i], &v[i], &l, &r), modify(1, 1, k, l + 1, r, i);
    for (int i = 1; i <= 2 * n; i++)
        fa[i] = i, sz[i] = 1;
    solve(1, 1, k);
    return 0;
}