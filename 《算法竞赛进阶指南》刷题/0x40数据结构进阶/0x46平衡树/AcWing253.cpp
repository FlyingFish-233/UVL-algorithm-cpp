# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;
const int INF = 0x3f3f3f3f;

struct Node
{
	int l, r, val, rnd, num, sz;
};

int root, tot;
Node tree[NR];

int newNode(int val)
{
	tree[++tot].val = val;
	tree[tot].rnd = rand();
	tree[tot].num = tree[tot].sz = 1;
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

int getRank(int rt, int val)
{
	if (rt == 0) return 1;
	if (val == tree[rt].val) return tree[tree[rt].l].sz + 1;
	if (val < tree[rt].val) return getRank(tree[rt].l, val);
	return getRank(tree[rt].r, val) + tree[tree[rt].l].sz + tree[rt].num;
}

int getVal(int rt, int rank)
{
	if (rt == 0) return -INF;
	if (rank <= tree[tree[rt].l].sz) return getVal(tree[rt].l, rank);
	if (rank <= tree[tree[rt].l].sz + tree[rt].num) return tree[rt].val;
	return getVal(tree[rt].r, rank - tree[tree[rt].l].sz - tree[rt].num);
}

int getPrev(int val)
{
	int ans = -INF;
	for (int rt = root; rt; rt = (val < tree[rt].val) ? tree[rt].l : tree[rt].r) {
		if (val == tree[rt].val) {
			if (tree[rt].l == 0) break;
			rt = tree[rt].l;
			while (tree[rt].r != 0) rt = tree[rt].r;
			ans = tree[rt].val;
			break;
		}
		if (tree[rt].val < val && tree[rt].val > ans)
			ans = tree[rt].val;
	}
	return ans;
}

int getNext(int val)
{
	int ans = INF;
	for (int rt = root; rt; rt = (val < tree[rt].val) ? tree[rt].l : tree[rt].r) {
		if (val == tree[rt].val) {
			if (tree[rt].r == 0) break;
			rt = tree[rt].r;
			while (tree[rt].l != 0) rt = tree[rt].l;
			ans = tree[rt].val;
			break;
		}
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
	if (val == tree[rt].val) { tree[rt].num++, pushUp(rt); return; }
	if (val < tree[rt].val) {
		insert(tree[rt].l, val);
		if (tree[rt].rnd < tree[tree[rt].l].rnd) zig(rt);
	}
	else {
		insert(tree[rt].r, val);
		if (tree[rt].rnd < tree[tree[rt].r].rnd) zag(rt);
	}
	pushUp(rt);
}

void remove(int &rt, int val)
{
	if (rt == 0) return;
	if (val == tree[rt].val) {
		if (tree[rt].num > 1) { tree[rt].num--, pushUp(rt); return; }
		if (tree[rt].l == 0 && tree[rt].r == 0) { rt = 0; return; }
		if (tree[rt].r == 0 || tree[tree[rt].l].rnd > tree[tree[rt].r].rnd)
			zig(rt), remove(tree[rt].r, val);
		else zag(rt), remove(tree[rt].l, val);
		pushUp(rt);
		return;
	}
	if (val < tree[rt].val) remove(tree[rt].l, val);
	else remove(tree[rt].r, val);
	pushUp(rt);
}

int main()
{
	init();
	int T;
	scanf("%d", &T);
	while (T--) {
		int opt, x;
		scanf("%d%d", &opt, &x);
		switch (opt) {
			case 1: insert(root, x); break;
			case 2: remove(root, x); break;
			case 3: printf("%d\n", getRank(root, x) - 1); break;
			case 4: printf("%d\n", getVal(root, x + 1)); break;
			case 5: printf("%d\n", getPrev(x)); break;
			case 6: printf("%d\n", getNext(x)); break;
		}
	}
	return 0;
}