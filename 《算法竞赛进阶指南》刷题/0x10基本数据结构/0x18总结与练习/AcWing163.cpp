# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2e5 + 10;

struct Node
{
	int next, prev, val;
};

int n, m, cnt;
int a[NR], b[NR];

int tot, head, tail;
Node node[NR];

struct Point
{
	int x;
	bool operator < (const Point &cmp) const { return node[x].val > node[cmp.x].val; }
};

priority_queue<Point> q;
bool used[NR];

void init()
{
	head = ++tot, tail = ++tot;
	node[head].next = tail;
	node[tail].prev = head;
}

void ins(int p, int val)
{
	int x = ++tot;
	node[x].val = val;
	q.push((Point) {x});
	node[x].prev = p;
	node[x].next = node[p].next;
	node[node[p].next].prev = x;
	node[p].next = x;
}

void del(int x)
{
	used[x] = true;
	node[node[x].prev].next = node[x].next;
	node[node[x].next].prev = node[x].prev;
}

int main()
{
	int len;
	scanf("%d%d", &len, &m);
	for (int i = 1, x; i <= len; i++) {
		scanf("%d", &x);
		if (x) a[++n] = x;
	}
	for (int i = 1; i <= n; i++) {
		if (a[i] * a[i - 1] > 0) b[cnt] += a[i];
		else b[++cnt] = a[i];
	}
	int sum = 0, num = 0;
	init();
	for (int i = 1; i <= cnt; i++) {
		if (b[i] > 0) sum += b[i], num++;
		if (b[i] < 0 && i == 1) continue;
		if (b[i] < 0 && i == cnt) continue;
		ins(node[tail].prev, abs(b[i]));
	}
	if (num <= m) {
		printf("%d\n", sum);
		return 0;
	}
	m = num - m;
	int ans = 0;
	while (m--) {
		while (used[q.top().x]) q.pop();
		int x = q.top().x;
		q.pop();
		ans += node[x].val;
		if (node[x].prev == head || node[x].next == tail) {
			if (node[x].prev != head) del(node[x].prev);
			if (node[x].next != tail) del(node[x].next);
			del(x);
			continue;
		}
		int val = node[node[x].prev].val + node[node[x].next].val - node[x].val;
		del(node[x].prev), del(node[x].next);
		ins(x, val), del(x);
	}
	printf("%d\n", sum - ans);
	return 0;
}