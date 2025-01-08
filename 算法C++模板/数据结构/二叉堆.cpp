# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <queue>

using namespace std;

const int NR = 1e6 + 10;

int len, heap[NR];

void up(int x)
{
	for (int dad = x >> 1, son = x; dad > 0 && heap[dad] > heap[son]; dad >>= 1, son >>= 1)
		swap(heap[dad], heap[son]);
}

void down(int x)
{
	for (int dad = x, son = x << 1; son <= len; dad = son, son <<= 1) {
		if (son + 1 <= len && heap[son] > heap[son + 1]) son++;
		if (heap[dad] > heap[son]) swap(heap[dad], heap[son]);
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
	int T;
	scanf("%d", &T);
	while (T--) {
		int op, x;
		scanf("%d", &op);
		if (op == 1) scanf("%d", &x), push(x);
		if (op == 2) printf("%d\n", heap[1]);
		if (op == 3) pop();
	}
	return 0;
}