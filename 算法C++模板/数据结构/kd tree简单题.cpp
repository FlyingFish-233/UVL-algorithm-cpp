// P4148 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2e5 + 10;
const double alpha = 0.7;

struct Node
{
    int x, y, v;
};

int n;
Node p[NR];

int root, ls[NR], rs[NR], d[NR];

bool cmp_x(int n1, int n2) { return p[n1].x < p[n2].x; }
bool cmp_y(int n1, int n2) { return p[n1].y < p[n2].y; }

int siz[NR], sum[NR];
int L[NR], R[NR], D[NR], U[NR];

void maintain(int o)
{
    siz[o] = siz[ls[o]] + 1 + siz[rs[o]];
    sum[o] = sum[ls[o]] + p[o].v + sum[rs[o]];
    L[o] = R[o] = p[o].x, D[o] = U[o] = p[o].y;
    if (ls[o] != 0) {
        L[o] = min(L[o], L[ls[o]]), R[o] = max(R[o], R[ls[o]]);
        D[o] = min(D[o], D[ls[o]]), U[o] = max(U[o], U[ls[o]]);
    }
    if (rs[o] != 0) {
        L[o] = min(L[o], L[rs[o]]), R[o] = max(R[o], R[rs[o]]);
        D[o] = min(D[o], D[rs[o]]), U[o] = max(U[o], U[rs[o]]);
    }
}

int t[NR];

void getArray(int o)
{
    if (o == 0) return;
    getArray(ls[o]);
    t[++t[0]] = o;
    getArray(rs[o]);
}

int build(int l, int r)
{
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    double avx = 0, avy = 0, vax = 0, vay = 0;
    for (int i = l; i <= r; i++)
        avx += p[t[i]].x, avy += p[t[i]].y;
    avx /= r - l + 1, avy /= r - l + 1;
    for (int i = l; i <= r; i++)
        vax += (p[t[i]].x - avx) * (p[t[i]].x - avx), vay += (p[t[i]].y - avy) * (p[t[i]].y - avy);
    if (vax >= vay) d[t[mid]] = 1, nth_element(t + l, t + mid, t + r + 1, cmp_x);
    else d[t[mid]] = 2, nth_element(t + l, t + mid, t + r + 1, cmp_y);
    ls[t[mid]] = build(l, mid - 1), rs[t[mid]] = build(mid + 1, r);
    maintain(t[mid]);
    return t[mid];
}

void rebuild(int &o)
{
    t[0] = 0, getArray(o);
    o = build(1, t[0]);
}

bool check(int o)
{
    return (double) max(siz[ls[o]], siz[rs[o]]) > alpha * siz[o];
}

void insert(int &o, int z)
{
    if (o == 0) {
        maintain(o = z);
        return;
    }
    if (d[o] == 1) {
        if (p[z].x <= p[o].x) insert(ls[o], z);
        else insert(rs[o], z);
    }
    else {
        if (p[z].y <= p[o].y) insert(ls[o], z);
        else insert(rs[o], z);
    }
    maintain(o);
    if (check(o)) rebuild(o);
}

int query(int o, int x1, int y1, int x2, int y2)
{
    if (o == 0 || x1 > R[o] || x2 < L[o] || y1 > U[o] || y2 < D[o]) return 0;
    if (x1 <= L[o] && R[o] <= x2 && y1 <= D[o] && U[o] <= y2) return sum[o];
    return query(ls[o], x1, y1, x2, y2) + query(rs[o], x1, y1, x2, y2)
         + ((x1 <= p[o].x && p[o].x <= x2 && y1 <= p[o].y && p[o].y <= y2) ? p[o].v : 0);
}

int main()
{
    int op, lastans = 0;
    scanf("%*d");
    while (scanf("%d", &op) && op != 3) {
        if (op == 1) {
            n++, scanf("%d%d%d", &p[n].x, &p[n].y, &p[n].v);
            p[n].x ^= lastans, p[n].y ^= lastans, p[n].v ^= lastans;
            insert(root, n);
        }
        if (op == 2) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1 ^= lastans, y1 ^= lastans, x2 ^= lastans, y2 ^= lastans;
            printf("%d\n", lastans = query(root, x1, y1, x2, y2));
        }
    }
    return 0;
}