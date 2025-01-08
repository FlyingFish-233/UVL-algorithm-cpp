// AcWing149 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

struct Node
{
	long long x, dep;

	bool operator < (const Node &cmp) const {
		if (x != cmp.x) return x > cmp.x;
		return dep > cmp.dep;
	}
};

int n, k;
priority_queue<Node> q;

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		long long x;
		scanf("%lld", &x);
		q.push((Node) {x, 0});
	}
	for (int i = 0; (n + i - 1) % (k - 1) > 0; i++)
		q.push((Node) {0, 0});
	long long ans = 0;
	while (q.size() > 1) {
		long long sum = 0, dep = 0;
		for (int i = 1; i <= k; i++)
			sum += q.top().x, dep = max(dep, q.top().dep), q.pop();
		ans += sum;
		q.push((Node) {sum, dep + 1});
	}
	printf("%lld\n", ans);
	printf("%lld\n", q.top().dep);
	return 0;
}