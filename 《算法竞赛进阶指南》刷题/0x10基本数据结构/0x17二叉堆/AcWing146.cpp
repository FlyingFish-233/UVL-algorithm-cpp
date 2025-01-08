# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e3 + 10, MR = 2e6 + 10;

struct Node
{
	int val, x, y;
};

int n, m;
int a[NR], b[NR], save[NR];

int len;
Node heap[MR];

void up(int x)
{
	for (int dad = x >> 1, son = x; dad > 0 && heap[dad].val > heap[son].val; dad >>= 1, son >>= 1)
		swap(heap[dad], heap[son]);
}

void push(int x, int y)
{
	heap[++len] = (Node) {a[x] + b[y], x, y};
	up(len);
}

void down(int x)
{
	for (int dad = x, son = x << 1; son <= len; dad = son, son <<= 1) {
		if (son + 1 <= len && heap[son].val > heap[son + 1].val) son++;
		if (heap[dad].val > heap[son].val) swap(heap[dad], heap[son]);
		else break;
	}
}

void pop()
{
	swap(heap[1], heap[len--]);
	down(1);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &m, &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		for (int i = 2; i <= m; i++) {
			len = 0;
			for (int j = 1; j <= n; j++)
				scanf("%d", &b[j]);
			sort(b + 1, b + n + 1);
			push(1, 1);
			for (int j = 1; j <= n; j++) {
				save[j] = heap[1].val;
				push(heap[1].x, heap[1].y + 1);
				if (heap[1].y == 1) push(heap[1].x + 1, heap[1].y);
				pop();
			}
			memcpy(a, save, sizeof(save));
		}
		for (int i = 1; i <= n; i++)
			printf("%d ", a[i]);
		puts("");
	}
	return 0;
}