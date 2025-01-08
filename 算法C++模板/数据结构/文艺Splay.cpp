// P3391 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;
const int INF = 0x3f3f3f3f;

struct Node
{
    int ch[2], val, fa, num, sz;
    bool flag;
};

int n, m;
int root, tot;
Node tree[NR];

int newNode(int val)
{
    tree[++tot].val = val;
    tree[tot].num = tree[tot].sz = 1;
    return tot;
}

bool which(int x)
{
    return tree[tree[x].fa].ch[1] == x;
}

void pushUp(int rt)
{
    tree[rt].sz = tree[tree[rt].ch[0]].sz + tree[rt].num + tree[tree[rt].ch[1]].sz;
}

void pushDown(int rt)
{
    if (!tree[rt].flag) return;
    tree[tree[rt].ch[0]].flag ^= 1;
    tree[tree[rt].ch[1]].flag ^= 1;
    swap(tree[rt].ch[0], tree[rt].ch[1]);
    tree[rt].flag = 0;
}

void rotate(int x)
{
    int y = tree[x].fa, z = tree[y].fa, k = which(x);
    tree[z].ch[which(y)] = x, tree[x].fa = z;
    tree[y].ch[k] = tree[x].ch[k ^ 1], tree[tree[x].ch[k ^ 1]].fa = y;
    tree[x].ch[k ^ 1] = y, tree[y].fa = x;
    pushUp(y), pushUp(x);
}

void splay(int x, int goal)
{
    while (tree[x].fa != goal) {
        int y = tree[x].fa, z = tree[y].fa;
        if (z != goal) (which(x) ^ which(y)) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if (goal == 0) root = x;
}

void insert(int x)
{
    int rt = root, fa = 0;
    while (rt && tree[rt].val != x)
        fa = rt, rt = tree[rt].ch[tree[rt].val < x];
    if (rt) tree[rt].num++;
    else {
        rt = newNode(x);
        if (fa) tree[rt].fa = fa, tree[fa].ch[tree[fa].val < x] = rt;
    }
    splay(rt, 0);
}

int kth(int k)
{
    int rt = root;
    while (rt) {
        pushDown(rt);
        if (k <= tree[tree[rt].ch[0]].sz) rt = tree[rt].ch[0];
        else if (k <= tree[tree[rt].ch[0]].sz + tree[rt].num) break;
        else k -= tree[tree[rt].ch[0]].sz + tree[rt].num, rt = tree[rt].ch[1];
    }
    return rt;
}

void write(int rt)
{
    pushDown(rt);
    if (tree[rt].ch[0]) write(tree[rt].ch[0]);
    if (tree[rt].val >= 1 && tree[rt].val <= n) printf("%d ", tree[rt].val);
    if (tree[rt].ch[1]) write(tree[rt].ch[1]);
}

int main()
{
    scanf("%d%d", &n, &m);
    insert(-INF), insert(INF);
    for (int i = 1; i <= n; i++) insert(i);
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l = kth(l-1 + 1), r = kth(r+1 + 1);
        splay(l, 0), splay(r, l);
        tree[tree[r].ch[0]].flag ^= 1;
    }
    write(root), puts("");
    return 0;
}