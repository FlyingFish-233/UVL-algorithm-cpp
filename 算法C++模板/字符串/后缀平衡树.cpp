// P6164 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 8e5 + 10;
const double INF = 1e18;
const double alpha = 0.7;

int n, mask;
char str[NR], c[NR];

void decode(char* s, int len, int mask)
{
	for (int i = 0; i < len; ++i)
		mask = (mask * 131 + i) % len, swap(s[i], s[mask]);
}

struct Node
{
	int l, r, sz;
	double tag;
};

int root;
Node tree[NR];

void pushUp(int rt)
{
	if (rt == 0) return; // 必须要特判rt=0的情况！
	tree[rt].sz = tree[tree[rt].l].sz + 1 + tree[tree[rt].r].sz;
}

void initNode(int rt, double lv, double rv)
{
	tree[rt].sz = 1;
	tree[rt].tag = (lv + rv) / 2;
	tree[rt].l = tree[rt].r = 0;
}

// 这里维护的是str反串的后缀,结点x表示str[1~x]
bool cmp(int x, int y)
{
	if (str[x] != str[y]) return str[x] < str[y];
	return tree[x - 1].tag < tree[y - 1].tag;
}

bool check(int rt)
{
	return (double) max(tree[tree[rt].l].sz, tree[tree[rt].r].sz) > alpha * tree[rt].sz;
}

int save[NR];

void getArray(int rt)
{
	if (rt == 0) return;
	getArray(tree[rt].l);
	save[++save[0]] = rt;
	getArray(tree[rt].r);
}

int build(int l, int r, double lv, double rv)
{
    if (l > r) return 0;
    int mid = (l + r) >> 1, rt = save[mid];
    double mv = tree[rt].tag = (lv + rv) / 2;
    tree[rt].l = build(l, mid - 1, lv, mv);
    tree[rt].r = build(mid + 1, r, mv, rv);
    pushUp(rt);
    return rt;
}

void reBuild(int &rt, double lv, double rv)
{
    save[0] = 0, getArray(rt);
    rt = build(1, save[0], lv, rv);
}

void insert(int &rt, int p, double lv, double rv)
{
	if (rt == 0) { initNode(rt = p, lv, rv); return; }
	if (cmp(p, rt)) insert(tree[rt].l, p, lv, tree[rt].tag);
	else insert(tree[rt].r, p, tree[rt].tag, rv);
    pushUp(rt);
	if (check(rt)) reBuild(rt, lv, rv);
}

void remove(int &rt, int p, double lv, double rv)
{
    if (rt == 0) return;
    if (rt == p) {
    	if (tree[rt].l == 0 || tree[rt].r == 0)
    		rt = tree[rt].l + tree[rt].r;
    	else {
    		int nrt = tree[rt].l, fa = rt;
    		for ( ; tree[nrt].r; nrt = tree[nrt].r)
    			tree[fa = nrt].sz--;
    		if (fa == rt) tree[nrt].r = tree[rt].r;
    		else tree[nrt].l = tree[rt].l, tree[nrt].r = tree[rt].r, tree[fa].r = 0;
    		tree[nrt].tag = tree[rt].tag;
    		rt = nrt;
    	}
    }
    else {
    	if (cmp(p, rt)) remove(tree[rt].l, p, lv, tree[rt].tag);
    	else remove(tree[rt].r, p, tree[rt].tag, rv);
    }
    pushUp(rt);
	if (check(rt)) reBuild(rt, lv, rv);
}

bool str_cmp(char* s, int len, int p) {
  	for (int i = 1; i <= len; i++, p--) {
    	if (str[p] > s[i]) return true;
    	if (str[p] < s[i]) return false;
  	}
  	return false;
}

int getRank(int rt, char *s, int len)
{
	if (rt == 0) return 0;
	if (str_cmp(s, len, rt)) return getRank(tree[rt].l, s, len);
	return tree[tree[rt].l].sz + 1 + getRank(tree[rt].r, s, len);
}

int main()
{
	int T;
	scanf("%d%s", &T, str + 1), n = strlen(str + 1);
	for (int i = 1; i <= n; i++)
		insert(root, i, 0, INF);
	int mask = 0;
	while (T--) {
		char op[10];
		scanf("%s", op);
		if (op[0] == 'A') {
			scanf("%s", c + 1);
			int len = strlen(c + 1);
			decode(c + 1, len, mask);
			for (int i = 1; i <= len; i++)
				str[++n] = c[i], insert(root, n, 0, INF);
		}
		if (op[0] == 'D') {
			int x;
			scanf("%d", &x);
			while (x--)
				remove(root, n--, 0, INF);
		}
		if (op[0] == 'Q') {
			scanf("%s", c + 1);
			int len = strlen(c + 1);
			decode(c + 1, len, mask);
			reverse(c + 1, c + len + 1);
			c[len + 1] = 'Z' + 1, c[len + 2] = 0;
			int ans = getRank(root, c, len + 1);
			c[len]--, ans -= getRank(root, c, len + 1);
			printf("%d\n", ans), mask ^= ans;
		}
	}
	return 0;
}
