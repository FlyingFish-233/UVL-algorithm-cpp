# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 5e5 + 10;
const int INF = 0x3f3f3f3f;

struct Node
{
	int sum, lmax, rmax, dat;
	Node () { sum = 0, lmax = rmax = dat = -INF; }
	Node (int k) { sum = lmax = rmax = dat = k; }
};

int n, m;
int a[NR];
Node tree[NR << 2];

void pushup(Node &o, Node l, Node r)
{
	o.sum = l.sum + r.sum;
	o.lmax = max(l.lmax, l.sum + r.lmax);
	o.rmax = max(r.rmax, r.sum + l.rmax);
	o.dat = max(max(l.dat, r.dat), l.rmax + r.lmax);
}

void build(int rt, int l, int r)
{
	if (l == r) { tree[rt] = Node(a[l]); return; }
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(tree[rt], tree[ls], tree[rs]);
}

void modify(int rt, int l, int r, int x, int v)
{
	if (l == r) { tree[rt] = Node(v); return; }
	if (x <= mid) modify(ls, l, mid, x, v);
	else modify(rs, mid + 1, r, x, v);
	pushup(tree[rt], tree[ls], tree[rs]);
}

Node query(int rt, int l, int r, int l0, int r0)
{
	if (l0 <= l && r <= r0) return tree[rt];
	Node ans, l_ans, r_ans;
	if (l0 <= mid) l_ans = query(ls, l, mid, l0, r0);
	if (mid < r0) r_ans = query(rs, mid + 1, r, l0, r0);
	pushup(ans, l_ans, r_ans);
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	build(1, 1, n);
	while (m--) {
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) printf("%d\n", query(1, 1, n, min(x, y), max(x, y)).dat);
		if (op == 2) modify(1, 1, n, x, y);
	}
	return 0;
}