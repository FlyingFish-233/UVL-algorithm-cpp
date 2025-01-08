# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

struct Array
{
	int x, id;
	bool operator < (const Array &cmp) const { return x < cmp.x; }
};

struct Node
{
	int prev, next, val;
	bool flag;
};

int n;
Array a[NR];
int ans[NR];

int head, tail;
Node node[NR];

void init()
{
	memset(node, 0, sizeof(node));
	head = 0, tail = n + 1;
	node[head].next = tail;
	node[tail].prev = head;
}

void ins(int p, int x, int val, bool flag)
{
	node[x] = (Node) {p, node[p].next, val, flag};
	node[node[p].next].prev = x;
	node[p].next = x;
}

void del(int p)
{
	node[node[p].next].prev = node[p].prev;
	node[node[p].prev].next = node[p].next;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int id;
		scanf("%d %d", &id, &n);
		printf("%d %d\n", id, n / 2 + 1);
		init();
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i].x), a[i].id = i;
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++)
			ins(node[tail].prev, a[i].id, a[i].x, i <= n / 2 + 1);
		int mid = a[n / 2 + 1].id;
		for (int i = n; i >= 1; i--) {
			ans[i] = node[mid].val;
			if (i == mid) {
				int save = mid;
				if (i & 1) mid = node[mid].next, node[mid].flag = true;
				else mid = node[mid].prev;
				del(save);
				continue;
			}
			bool flag = node[i].flag;
			del(i);
			if ((i & 1) && flag) mid = node[mid].next, node[mid].flag = true;
			if (!(i & 1) && !flag) node[mid].flag = false, mid = node[mid].prev;
		}
		for (int i = 1; i <= n; i++) {
			if (i & 1) printf("%d ", ans[i]);
			if (i % 20 == 0) puts("");
		}
		if (n % 20 != 0) puts("");
	}
	return 0;
}