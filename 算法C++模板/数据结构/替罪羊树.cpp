// P3369 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const double alpha = 0.7;

struct Node
{
	int l, r, val, sz, sz2;
	bool flag;
	// flag = true表示该节点存在, flag = false表示该节点已被删去
	// sz表示不算已删去节点时树的大小, sz2表示树的实际大小(包括已删去节点)
};

int root, tot;
Node tree[NR];

void pushUp(int rt)
{
	tree[rt].sz = tree[tree[rt].l].sz + 1 + tree[tree[rt].r].sz;
	tree[rt].sz2 = tree[tree[rt].l].sz2 + 1 + tree[tree[rt].r].sz2;
}

int newNode(int val)
{
	tree[++tot].val = val;
	tree[tot].sz = tree[tot].sz2 = 1;
	tree[tot].flag = true;
	return tot;
}

int getRank(int rt, int val)
{
	if (rt == 0) return 1;
	if (val <= tree[rt].val) return getRank(tree[rt].l, val);
	return getRank(tree[rt].r, val) + tree[tree[rt].l].sz + tree[rt].flag;
}

int getVal(int rt, int rank)
{
	if (rt == 0) return -INF;
	if (rank <= tree[tree[rt].l].sz) return getVal(tree[rt].l, rank);
	if (tree[rt].flag && rank == tree[tree[rt].l].sz + 1) return tree[rt].val;
	return getVal(tree[rt].r, rank - tree[tree[rt].l].sz - tree[rt].flag);
}

bool check(int rt)
{
	return (double) max(tree[tree[rt].l].sz2, tree[tree[rt].r].sz2) > alpha * tree[rt].sz2;
}

int save[NR];

void getArray(int rt)
{
	if (rt == 0) return;
	getArray(tree[rt].l);
	if (tree[rt].flag) save[++save[0]] = rt;
	getArray(tree[rt].r);
}

int build(int l, int r)
{
	if (l > r) return 0;
	int mid = (l + r) >> 1, rt = save[mid];
	tree[rt].l = build(l, mid - 1);
	tree[rt].r = build(mid + 1, r);
	pushUp(rt);
	return rt;
}

void reBuild(int &rt)
{
	save[0] = 0, getArray(rt);
	rt = build(1, save[0]);
}

void insert(int &rt, int val)
{
	if (rt == 0) { rt = newNode(val); return; }
	tree[rt].sz++, tree[rt].sz2++;
	if (val < tree[rt].val) insert(tree[rt].l, val);
	else insert(tree[rt].r, val);
	if (check(rt)) reBuild(rt);
}

void remove(int rt, int k)
{
    if (rt == 0) return;
    tree[rt].sz--;
    if (tree[rt].flag && k == tree[tree[rt].l].sz + 1) { tree[rt].flag = false; return; }
    if (k <= tree[tree[rt].l].sz + tree[rt].flag) remove(tree[rt].l, k);
    else remove(tree[rt].r, k - tree[tree[rt].l].sz - tree[rt].flag);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int opt, x;
		scanf("%d%d", &opt, &x);
		switch (opt) {
			case 1: insert(root, x); break;
			case 2: remove(root, getRank(root, x)); break;
			case 3: printf("%d\n", getRank(root, x)); break;
			case 4: printf("%d\n", getVal(root, x)); break;
			case 5: printf("%d\n", getVal(root, getRank(root, x) - 1)); break;
			case 6: printf("%d\n", getVal(root, getRank(root, x + 1))); break;
		}
	}
	return 0;
}
