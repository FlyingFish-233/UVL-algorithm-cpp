// AcWing289 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2e6 + 10;

struct Node
{
	int id, val;
};

int n;
int a[NR];
deque<Node> q;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), a[i + n] = a[i];
	int ans = 0;
	for (int i = 1; i <= (n << 1); i++) {
		while (!q.empty() && q.back().id < i - n / 2) q.pop_back();
		if (!q.empty()) ans = max(ans, a[i] + i + q.back().val);
		while (!q.empty() && q.front().val <= a[i] - i) q.pop_front();
		q.push_front((Node) {i, a[i] - i});
	}
	printf("%d\n", ans);
	return 0;
}