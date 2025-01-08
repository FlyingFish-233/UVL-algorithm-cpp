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
	Node() { prev = next = 0, val = 2e9; }
};

int n;
Array a[NR];

int head, tail;
Node node[NR];

int ans1[NR], ans2[NR];

void init()
{
	head = 0, tail = n + 1;
	node[head].next = tail;
	node[tail].prev = head;
}

void ins(int p, int x, int val)
{
	node[x].val = val;
	node[x].prev = p;
	node[x].next = node[p].next;
	node[node[p].next].prev = x;
	node[p].next = x;
}

void del(int p)
{
	node[node[p].next].prev = node[p].prev;
	node[node[p].prev].next = node[p].next;
	node[p] = Node();
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i].x), a[i].id = i;
	sort(a + 1, a + n + 1);
	init();
	for (int i = 1; i <= n; i++)
		ins(node[tail].prev, a[i].id, a[i].x);
	for (int i = n; i >= 2; i--) {
		int x = abs(node[node[i].prev].val - node[i].val);
		int y = abs(node[node[i].next].val - node[i].val);
		if (x <= y) ans1[i] = x, ans2[i] = node[i].prev;
		else ans1[i] = y, ans2[i] = node[i].next;
		del(i);
	}
	for (int i = 2; i <= n; i++)
		printf("%d %d\n", ans1[i], ans2[i]);
	return 0;
}