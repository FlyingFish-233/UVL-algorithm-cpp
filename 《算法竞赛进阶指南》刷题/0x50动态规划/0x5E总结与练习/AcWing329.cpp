# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define mid ((l + r) >> 1)
# define ls (rt << 1)
# define rs (rt << 1 | 1)

using namespace std;

const int NR = 3e4 + 10;
const int D = 1e5 + 1, MR = 2e5 + 10;

int n, S;
int l[NR], r[NR];
int f[NR][2];

int id[MR << 2], tag[MR << 2];

void pushDown(int rt)
{
    if (tag[rt] == 0) return;
    id[ls] = tag[ls] = tag[rt];
    id[rs] = tag[rs] = tag[rt];
    tag[rt] = 0;
}

void modify(int rt, int l, int r, int l0, int r0, int x)
{
    if (l0 <= l && r <= r0) { id[rt] = tag[rt] = x; return; }
    pushDown(rt);
    if (l0 <= mid) modify(ls, l, mid, l0, r0, x);
    if (mid < r0) modify(rs, mid + 1, r, l0, r0, x);
}

int query(int rt, int l, int r, int x)
{
    if (l == r) return id[rt];
    pushDown(rt);
    if (x <= mid) return query(ls, l, mid, x);
    return query(rs, mid + 1, r, x);
}

int main()
{
    scanf("%d%d", &n, &S), S += D;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &l[i], &r[i]), l[i] += D, r[i] += D;
    memset(f, 0x3f, sizeof(f));
    l[0] = r[0] = D, f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        int j = query(1, 1, D << 1, l[i]);
        f[i][0] = min(f[j][0] + abs(l[i] - l[j]), f[j][1] + abs(l[i] - r[j]));
        j = query(1, 1, D << 1, r[i]);
        f[i][1] = min(f[j][0] + abs(r[i] - l[j]), f[j][1] + abs(r[i] - r[j]));
        modify(1, 1, D << 1, l[i], r[i], i);
    }
    printf("%d\n", min(f[n][0] + abs(S - l[n]), f[n][1] + abs(S - r[n])));
    return 0;
}