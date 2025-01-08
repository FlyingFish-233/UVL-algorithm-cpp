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
	int ls, rs, val, rnd, sz;
	bool flag;
};

int n, m;
int root, tot;
Node tree[NR];

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

void pushDown(int rt)
{
	if (!tree[rt].flag) return;
	tree[tree[rt].ls].flag ^= 1;
	tree[tree[rt].rs].flag ^= 1;
    swap(tree[rt].ls, tree[rt].rs);
	tree[rt].flag = 0;
}

int merge(int x, int y)
{
	if (x == 0 || y == 0) return x + y;
	int rt = 0;
	if (tree[x].rnd > tree[y].rnd) pushDown(x), tree[rt = x].rs = merge(tree[x].rs, y);
	else pushDown(y), tree[rt = y].ls = merge(x, tree[y].ls);
	pushUp(rt);
	return rt;
}

void split_rank(int rt, int &x, int &y, int k)
{
	if (rt == 0) { x = y = 0; return; }
	pushDown(rt);
	int tmp = tree[tree[rt].ls].sz + 1;
	if (k < tmp) split_rank(tree[y = rt].ls, x, tree[rt].ls, k);
	else split_rank(tree[x = rt].rs, tree[rt].rs, y, k - tmp);
	pushUp(rt);
}

void split_val(int rt, int &x, int &y, int k)
{
	if (rt == 0) { x = y = 0; return; }
	pushDown(rt);
	if (k <= tree[rt].val) split_val(tree[y = rt].ls, x, tree[rt].ls, k);
	else split_val(tree[x = rt].rs, tree[rt].rs, y, k);
	pushUp(rt);
}

void write(int rt)
{
    pushDown(rt);
    if (tree[rt].ls) write(tree[rt].ls);
    printf("%d ", tree[rt].val);
    if (tree[rt].rs) write(tree[rt].rs);
}

int main()
{
	scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        root = merge(root, newNode(i));
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        int a, b, c;
        split_rank(root, a, c, r);
        split_rank(a, a, b, l - 1);
        tree[b].flag ^= 1;
        root = merge(merge(a, b), c);
    }
    write(root), puts("");
	return 0;
}