# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef long long LL;

const int NR = 2e5 + 10;

struct Node
{
	int ls, rs, sz, rnd;
	LL min, val, tag; bool flag;
};

int n, m;
int tot, root;
Node tree[NR];

int newNode(LL val)
{
	int rt = ++tot;
	tree[rt].sz = 1;
	tree[rt].rnd = rand();
	tree[rt].min = tree[rt].val = val;
	return rt;
}

void pushDown(int rt)
{
	if (tree[rt].flag) {
		swap(tree[rt].ls, tree[rt].rs);
		tree[tree[rt].ls].flag ^= 1;
		tree[tree[rt].rs].flag ^= 1;
		tree[rt].flag = false;
	}
	if (tree[rt].tag == 0) return;
	tree[tree[rt].ls].min += tree[rt].tag;
	tree[tree[rt].ls].val += tree[rt].tag;
	tree[tree[rt].ls].tag += tree[rt].tag;
	tree[tree[rt].rs].min += tree[rt].tag;
	tree[tree[rt].rs].val += tree[rt].tag;
	tree[tree[rt].rs].tag += tree[rt].tag;
	tree[rt].tag = 0;
}

void pushUp(int rt)
{
	tree[rt].sz = tree[tree[rt].ls].sz + 1 + tree[tree[rt].rs].sz;
	tree[rt].min = min(tree[rt].val, min(tree[tree[rt].ls].min, tree[tree[rt].rs].min));
}

int merge(int x, int y)
{
	if (x == 0 || y == 0) return x + y;
	int rt = 0;
	if (tree[x].rnd > tree[y].rnd) pushDown(rt = x), tree[rt].rs = merge(tree[x].rs, y);
	else pushDown(rt = y), tree[rt].ls = merge(x, tree[y].ls);
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

int main()
{
	scanf("%d", &n);
	tree[0].min = tree[0].val = 1e18;
	for (int i = 1, x; i <= n; i++)
		scanf("%d", &x), root = merge(root, newNode(x));
	scanf("%d", &m);
	while (m--) {
		char str[10]; int x, y, k, a, b, c, d;
		scanf("%s", str);
		if (str[0] == 'A') {
			scanf("%d%d%d", &x, &y, &k);
			split_rank(root, a, c, y);
			split_rank(a, a, b, x - 1);
			tree[b].min += k, tree[b].val += k, tree[b].tag += k;
			root = merge(merge(a, b), c);
		}
		if (str[0] == 'R' && str[3] == 'E') {
			scanf("%d%d", &x, &y);
			split_rank(root, a, c, y);
			split_rank(a, a, b, x - 1);
			tree[b].flag ^= 1;
			root = merge(merge(a, b), c);
		}
		if (str[0] == 'R' && str[3] == 'O') {
			scanf("%d%d%d", &x, &y, &k);
			split_rank(root, c, d, y);
			split_rank(c, b, c, y - k % (y - x + 1));
			split_rank(b, a, b, x - 1);
			root = merge(merge(a, c), merge(b, d));
		}
		if (str[0] == 'I') {
			scanf("%d%d", &x, &k);
			split_rank(root, a, b, x);
			root = merge(merge(a, newNode(k)), b);
		}
		if (str[0] == 'D') {
			scanf("%d", &x);
			split_rank(root, a, b, x - 1);
			split_rank(b, b, c, 1);
			root = merge(a, c);
		}
		if (str[0] == 'M') {
			scanf("%d%d", &x, &y);
			split_rank(root, a, c, y);
			split_rank(a, a, b, x - 1);
			printf("%lld\n", tree[b].min);
			root = merge(merge(a, b), c);
		}
	}
	return 0;
}