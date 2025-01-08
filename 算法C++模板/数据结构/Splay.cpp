// P3369 (100 pts)
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
};

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

void rotate(int x)
{
    int y = tree[x].fa, z = tree[y].fa, k = which(x);
    tree[z].ch[which(y)] = x, tree[x].fa = z;
    tree[y].ch[k] = tree[x].ch[k ^ 1], tree[tree[x].ch[k ^ 1]].fa = y;
    tree[x].ch[k ^ 1] = y, tree[y].fa = x;
    pushUp(y), pushUp(x);
}

// 将x旋转为goal的儿子, 如果goal=0就将x旋转到根
void splay(int x, int goal)
{
    while (tree[x].fa != goal) {
        int y = tree[x].fa, z = tree[y].fa;
        if (z != goal) (which(x) == which(y)) ? rotate(y) : rotate(x);
        rotate(x);
        // 如果which(x)==which(y), 那么先旋转y, 再旋转x (把x的两棵子树都转到较上层)
        // 如果which(x)!=which(y), 那么旋转两次x (若先转y, 则x只能向上一层)
    }
    if (goal == 0) root = x;
}

// 把权值为x的点旋转到根（若没有权值为x的点, 则会将x的前驱或者后继旋转到根）
void find(int x)
{
    if (root == 0) return;
    int rt = root;
    while (tree[rt].ch[tree[rt].val < x] && x != tree[rt].val)
        rt = tree[rt].ch[tree[rt].val < x];
    splay(rt, 0);
}

int getPrev(int x)
{
    find(x);
    int rt = root;
    if (tree[rt].val < x) return rt;
    rt = tree[rt].ch[0];
    while (tree[rt].ch[1]) rt = tree[rt].ch[1];
    return rt;
}

int getNext(int x)
{
    find(x);
    int rt = root;
    if (tree[rt].val > x) return rt;
    rt = tree[rt].ch[1];
    while (tree[rt].ch[0]) rt = tree[rt].ch[0];
    return rt;
}

int getRank(int x)
{
    find(x);
    return tree[tree[root].ch[0]].sz + 1;
}

int kth(int k)
{
    int rt = root;
    while (rt) {
        if (k <= tree[tree[rt].ch[0]].sz) rt = tree[rt].ch[0];
        else if (k <= tree[tree[rt].ch[0]].sz + tree[rt].num) break;
        else k -= tree[tree[rt].ch[0]].sz + tree[rt].num, rt = tree[rt].ch[1];
    }
    return rt;
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

void remove(int x)
{
    int pre = getPrev(x), nxt = getNext(x);
    splay(pre, 0), splay(nxt, pre);
    int rt = tree[nxt].ch[0];
    if (tree[rt].num > 1) tree[rt].num--, splay(rt, 0);
    else tree[nxt].ch[0] = 0;
}

int main()
{
    int T;
    scanf("%d", &T);
    insert(-INF), insert(INF);
    while (T--) {
        int opt, x;
        scanf("%d%d", &opt, &x);
        switch (opt) {
            case 1: insert(x); break;
            case 2: remove(x); break;
            case 3: printf("%d\n", getRank(x) - 1); break;
            case 4: printf("%d\n", tree[kth(x + 1)].val); break;
            case 5: printf("%d\n", tree[getPrev(x)].val); break;
            case 6: printf("%d\n", tree[getNext(x)].val); break;
        }
    }
    return 0;
}