# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 4e4 + 10;
const int INF = 0x3f3f3f3f;

struct Node
{
	int l, r, val, rnd, num, sz;
};

int n;
int a[NR];

int tot, root;
Node tree[NR];

int newNode(int x)
{
	tree[++tot].val = x;
	tree[tot].rnd = rand();
	tree[tot].sz = tree[tot].num = 1;
	return tot;
}

void pushUp(int rt)
{
	tree[rt].sz = tree[tree[rt].l].sz + tree[rt].num + tree[tree[rt].r].sz;
}

void init()
{
	newNode(-INF), newNode(INF);
	tree[root = 1].r = 2;
	pushUp(root);
}

int getPrev(int val)
{
	int ans = -INF;
	for (int rt = root; rt; rt = (val < tree[rt].val) ? tree[rt].l : tree[rt].r) {
		if (tree[rt].val == val) ans = val;
		if (tree[rt].val < val && tree[rt].val > ans)
			ans = tree[rt].val;
	}
	return ans;
}

int getNext(int val)
{
	int ans = INF;
	for (int rt = root; rt; rt = (val < tree[rt].val) ? tree[rt].l : tree[rt].r) {
		if (tree[rt].val == val) ans = val;
		if (tree[rt].val > val && tree[rt].val < ans)
			ans = tree[rt].val;
	}
	return ans;
}

void zig(int &rt)
{
	int tmp = tree[rt].l;
	tree[rt].l = tree[tmp].r, tree[tmp].r = rt, rt = tmp;
	pushUp(tree[rt].r), pushUp(rt);
}

void zag(int &rt)
{
	int tmp = tree[rt].r;
	tree[rt].r = tree[tmp].l, tree[tmp].l = rt, rt = tmp;
	pushUp(tree[rt].l), pushUp(rt);
}

void insert(int &rt, int val)
{
	if (rt == 0) { rt = newNode(val); return; }
	if (val == tree[rt].val) { tree[rt].num++; return; }
	if (val < tree[rt].val) {
		insert(tree[rt].l, val);
		if (tree[tree[rt].l].rnd > tree[rt].rnd) zig(rt);
	}
	else {
		insert(tree[rt].r, val);
		if (tree[tree[rt].r].rnd > tree[rt].rnd) zag(rt);
	}
	pushUp(rt);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int ans = a[1]; init();
	for (int i = 1; i <= n; i++) {
		int x = getPrev(a[i]), y = getNext(a[i]);
		if (x != -INF || y != INF) ans += min(y - a[i], a[i] - x);
		insert(root, a[i]);
	}
	printf("%d\n", ans);
	return 0;
}