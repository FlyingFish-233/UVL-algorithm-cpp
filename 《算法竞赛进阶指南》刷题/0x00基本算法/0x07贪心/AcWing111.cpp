# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 5e4 + 10;

struct Array
{
	int l, r, x;

	bool operator < (const Array &A) const {
		return l < A.l;
	}
};

struct Node
{
	int r, id;

	bool operator < (const Node &A) const {
		return r > A.r;
	}
};

int n;
Array a[NR];
priority_queue<Node> q;
int num[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].l, &a[i].r), a[i].x = i;
	sort(a + 1, a + n + 1);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (!q.empty() && q.top().r < a[i].l) num[a[i].x] = q.top().id, q.pop();
		else num[a[i].x] = ++ans;
		q.push((Node) {a[i].r, num[a[i].x]});
	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++)
		printf("%d\n", num[i]);
	return 0;
}