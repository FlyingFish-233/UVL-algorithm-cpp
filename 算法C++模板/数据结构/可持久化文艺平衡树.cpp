// P5055 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;
const int INF = 0x3f3f3f3f;

struct Node
{
	int ls, rs, val, rnd, sz;
	bool flag; long long sum;
};

int root[NR], tot;
Node tree[NR << 7];

int newNode(int val)
{
	tree[++tot].val = val;
	tree[tot].sum = val;
	tree[tot].rnd = rand();
	tree[tot].sz = 1;
	return tot;
}

void pushUp(int rt)
{
	tree[rt].sz = tree[tree[rt].ls].sz + 1 + tree[tree[rt].rs].sz;
	tree[rt].sum = tree[tree[rt].ls].sum + tree[rt].val + tree[tree[rt].rs].sum;
}

// pushDown中也需要复制节点
void pushDown(int rt)
{
	if (!tree[rt].flag) return;
	if (tree[rt].ls) tree[++tot] = tree[tree[rt].ls], tree[rt].ls = tot;
	if (tree[rt].rs) tree[++tot] = tree[tree[rt].rs], tree[rt].rs = tot;
	tree[tree[rt].ls].flag ^= 1;
	tree[tree[rt].rs].flag ^= 1;
    swap(tree[rt].ls, tree[rt].rs);
	tree[rt].flag = 0;
}

int merge(int x, int y)
{
    if (x == 0 || y == 0) return x + y;
    int rt = ++tot;
    if (tree[x].rnd > tree[y].rnd) {
    	tree[rt] = tree[x], pushDown(rt);
    	tree[rt].rs = merge(tree[rt].rs, y);
    }
    else {
    	tree[rt] = tree[y], pushDown(rt);
    	tree[rt].ls = merge(x, tree[rt].ls);
    }
    pushUp(rt);
    return rt;
}

void split_rank(int rt, int &x, int &y, int k)
{
    if (rt == 0) { x = y = 0; return; }
    pushDown(rt);
    int tmp = tree[tree[rt].ls].sz + 1;
    if (k < tmp) tree[y = ++tot] = tree[rt], split_rank(tree[y].ls, x, tree[y].ls, k), pushUp(y);
    else tree[x = ++tot] = tree[rt], split_rank(tree[x].rs, tree[x].rs, y, k - tmp), pushUp(x);
}

int main()
{
	int T; long long lastans = 0;
	scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        int v, op, a, b, c;
        long long x, y;
        scanf("%d%d%lld", &v, &op, &x), x ^= lastans;
        if (op != 2) scanf("%lld", &y), y ^= lastans;
        root[i] = root[v];
        if (op == 1) {
        	split_rank(root[i], a, b, x);
        	root[i] = merge(merge(a, newNode(y)), b);
        }
        if (op == 2) {
        	split_rank(root[i], a, b, x - 1);
        	split_rank(b, b, c, 1);
        	root[i] = merge(a, c);
        }
        if (op == 3) {
        	split_rank(root[i], a, c, y);
        	split_rank(a, a, b, x - 1);
        	tree[b].flag ^= 1;
        	root[i] = merge(merge(a, b), c);
        }
        if (op == 4) {
        	split_rank(root[i], a, c, y);
        	split_rank(a, a, b, x - 1);
        	printf("%lld\n", lastans = tree[b].sum);
        	root[i] = merge(merge(a, b), c);
        }
    }
	return 0;
}