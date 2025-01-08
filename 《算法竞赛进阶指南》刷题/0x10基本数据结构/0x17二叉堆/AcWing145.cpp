# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <queue>

using namespace std;

const int NR = 1e4 + 10;

int n, ans, d_max;
vector<int> a[NR];
int len, heap[NR];

void up(int x)
{
	for (int dad = x >> 1, son = x; dad > 0 && heap[dad] < heap[son]; dad >>= 1, son >>= 1)
		swap(heap[dad], heap[son]);
}

void down(int x)
{
	for (int dad = x, son = x << 1; son <= len; dad = son, son <<= 1) {
		if (son + 1 <= len && heap[son] < heap[son + 1]) son++;
		if (heap[dad] < heap[son]) swap(heap[dad], heap[son]);
		else break;
	}
}

void push(int x)
{
	heap[++len] = x;
	up(len);
}

void pop()
{
	swap(heap[1], heap[len--]);
	down(1);
}

int main()
{
	while (scanf("%d", &n) != EOF) {
		memset(a, 0, sizeof(a));
		ans = d_max = len = 0;
		for (int i = 1; i <= n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[y].push_back(x);
			d_max = max(d_max, y);
		}
		for (int i = 1e4; i >= 1; i--) {
			for (int j = 0; j < (int) a[i].size(); j++)
				push(a[i][j]);
			if (len > 0) ans += heap[1], pop();
		}
		printf("%d\n", ans);
	}
	return 0;
}