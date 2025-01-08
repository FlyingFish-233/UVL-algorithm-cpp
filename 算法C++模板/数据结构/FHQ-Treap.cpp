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
	int ls, rs, val, rnd, sz;
};

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

int merge(int x, int y)
{
	if (x == 0 || y == 0) return x + y;
	int rt = 0;
	if (tree[x].rnd > tree[y].rnd) tree[rt = x].rs = merge(tree[x].rs, y);
	else tree[rt = y].ls = merge(x, tree[y].ls);
	pushUp(rt);
	return rt;
}

// 树 -> 排名小于等于k的树 & 排名大于k的树
void split_rank(int rt, int &x, int &y, int k)
{
	if (rt == 0) { x = y = 0; return; }
	int tmp = tree[tree[rt].ls].sz + 1;
	if (k < tmp) split_rank(tree[y = rt].ls, x, tree[rt].ls, k);
	else split_rank(tree[x = rt].rs, tree[rt].rs, y, k - tmp);
	pushUp(rt);
}

// 树 -> 权值小于k的树 & 权值大于等于k的树
void split_val(int rt, int &x, int &y, int k)
{
	if (rt == 0) { x = y = 0; return; }
	if (k <= tree[rt].val) split_val(tree[y = rt].ls, x, tree[rt].ls, k);
	else split_val(tree[x = rt].rs, tree[rt].rs, y, k);
	pushUp(rt);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int opt, x, a, b, c;
		scanf("%d%d", &opt, &x);
		switch (opt) {
			case 1:
				split_val(root, a, b, x);
				root = merge(merge(a, newNode(x)), b);
				break;
			case 2:
				split_val(root, a, b, x);
				split_rank(b, b, c, 1);
				root = merge(a, c);
				break;
			case 3:
				split_val(root, a, b, x);
				printf("%d\n", tree[a].sz + 1);
				root = merge(a, b);
				break;
			case 4:
				split_rank(root, a, b, x - 1);
				split_rank(b, b, c, 1);
				printf("%d\n", tree[b].val);
				root = merge(merge(a, b), c);
				break;
			case 5:
				split_val(root, a, c, x);
				split_rank(a, a, b, tree[a].sz - 1);
				printf("%d\n", tree[b].val);
				root = merge(merge(a, b), c);
				break;
			case 6:
				split_val(root, a, b, x + 1);
				split_rank(b, b, c, 1);
				printf("%d\n", tree[b].val);
				root = merge(merge(a, b), c);
				break;
		}
	}
	return 0;
}