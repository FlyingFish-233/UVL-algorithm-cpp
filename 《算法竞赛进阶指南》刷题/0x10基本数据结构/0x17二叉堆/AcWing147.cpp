# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, k, a[NR];

struct Node
{
	int prev, next, val;
};

int head, tail;
Node node[NR];

void init()
{
	head = 0, tail = n + 1;
	node[head].next = tail;
	node[tail].prev = head;
}

void ins(int p, int x, int val)
{
	node[x].val = val;
	node[x].next = node[p].next;
	node[x].prev = p;
	node[node[p].next].prev = x;
	node[p].next = x;
}

void del(int x)
{
	node[node[x].next].prev = node[x].prev;
	node[node[x].prev].next = node[x].next;
}

int len, heap[NR];
int point[NR];

void up(int x)
{
	for (int dad = x >> 1, son = x; dad > 0; dad >>= 1, son >>= 1) {
		if (node[heap[dad]].val <= node[heap[son]].val) return;
		swap(heap[dad], heap[son]);
		swap(point[heap[dad]], point[heap[son]]);
	}
}

void push(int x)
{
	heap[++len] = x;
	point[x] = len;
	up(len);
}

void down(int x)
{
	for (int dad = x, son = x << 1; son <= len; dad = son, son <<= 1) {
		if (son + 1 <= len && node[heap[son]].val > node[heap[son + 1]].val) son++;
		if (node[heap[dad]].val <= node[heap[son]].val) return;
		swap(heap[dad], heap[son]);
		swap(point[heap[dad]], point[heap[son]]);
	}
}

void remove(int x)
{
	int tmp = point[x];
	swap(heap[tmp], heap[len--]);
	point[heap[tmp]] = tmp;
	up(tmp), down(tmp);
}

int main()
{
	scanf("%d%d", &n, &k);
	init();
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 2; i <= n; i++)
		ins(node[tail].prev, i, a[i] - a[i - 1]), push(i);
	int ans = 0;
	while (k--) {
		int x = heap[1];
		ans += node[x].val;
		if (node[x].prev == head || node[x].next == tail) { 
			remove(x), del(x);
			if (node[x].prev != head) remove(node[x].prev), del(node[x].prev);
			if (node[x].next != tail) remove(node[x].next), del(node[x].next);
			continue;
		}
		remove(x);
		node[x].val = node[node[x].prev].val + node[node[x].next].val - node[x].val;
		push(x);
		remove(node[x].prev), del(node[x].prev);
		remove(node[x].next), del(node[x].next);
	}
	printf("%d\n", ans);
	return 0;
}