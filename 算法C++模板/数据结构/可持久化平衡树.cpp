// P3835 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e5 + 10;
const int INF = 2147483647;

struct Node
{
    int ls, rs, val, rnd, sz;
};

int root[NR], tot;
Node tree[NR << 6];

int newNode(int val)
{
    tree[++tot].val = val;
    tree[tot].rnd = rand();
    tree[tot].sz = 1;
    return tot;
}

void pushUp(int rt)
{
    tree[rt].sz = tree[tree[rt].ls].sz + 1 + tree[tree[rt].rs].sz;
}

int merge(int x, int y)
{
    if (x == 0 || y == 0) return x + y;
    int rt = ++tot;
    if (tree[x].rnd > tree[y].rnd) tree[rt] = tree[x], tree[rt].rs = merge(tree[rt].rs, y);
    else tree[rt] = tree[y], tree[rt].ls = merge(x, tree[rt].ls);
    pushUp(rt);
    return rt;
}

void split_rank(int rt, int &x, int &y, int k)
{
    if (rt == 0) { x = y = 0; return; }
    int tmp = tree[tree[rt].ls].sz + 1;
    if (k < tmp) tree[y = ++tot] = tree[rt], split_rank(tree[y].ls, x, tree[y].ls, k), pushUp(y);
    else tree[x = ++tot] = tree[rt], split_rank(tree[x].rs, tree[x].rs, y, k - tmp), pushUp(x);
}

void split_val(int rt, int &x, int &y, int k)
{
    if (rt == 0) { x = y = 0; return; }
    if (k <= tree[rt].val) tree[y = ++tot] = tree[rt], split_val(tree[y].ls, x, tree[y].ls, k), pushUp(y);
    else tree[x = ++tot] = tree[rt], split_val(tree[x].rs, tree[x].rs, y, k), pushUp(x);
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        int v, opt, x, a, b, c;
        scanf("%d%d%d", &v, &opt, &x);
        root[i] = root[v];
        switch (opt) {
            case 1:
                split_val(root[i], a, b, x);
                root[i] = merge(merge(a, newNode(x)), b);
                break;
            case 2:
                split_val(root[i], a, b, x);
                split_rank(b, b, c, 1);
                if (b != 0 && tree[b].val == x) root[i] = merge(a, c);
                else root[i] = merge(merge(a, b), c);
                break;
            case 3:
                split_val(root[i], a, b, x);
                printf("%d\n", tree[a].sz + 1);
                root[i] = merge(a, b);
                break;
            case 4:
                split_rank(root[i], a, b, x - 1);
                split_rank(b, b, c, 1);
                printf("%d\n", tree[b].val);
                root[i] = merge(merge(a, b), c);
                break;
            case 5:
                split_val(root[i], a, c, x);
                split_rank(a, a, b, tree[a].sz - 1);
                printf("%d\n", (b == 0) ? -INF : tree[b].val);
                root[i] = merge(merge(a, b), c);
                break;
            case 6:
                split_val(root[i], a, b, x + 1);
                split_rank(b, b, c, 1);
                printf("%d\n", (b == 0) ? INF : tree[b].val);
                root[i] = merge(merge(a, b), c);
                break;
        }
    }
    return 0;
}