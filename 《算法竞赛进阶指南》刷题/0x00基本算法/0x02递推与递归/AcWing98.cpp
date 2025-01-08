# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <utility>

using namespace std;

pair <long long, long long> solve(int n, long long id)
{
	if (n == 0) return make_pair(1, 1);
	long long sz = 1ll << (2 * n - 2), len = 1ll << (n - 1);
	pair <long long, long long> tmp = solve(n - 1, id % sz);
	long long x = tmp.first, y = tmp.second;
	if (id / sz == 0) return make_pair(y, x);
	if (id / sz == 1) return make_pair(x, y + len);
	if (id / sz == 2) return make_pair(x + len, y + len);
	if (id / sz == 3) return make_pair(2 * len - y + 1, len - x + 1);
	return make_pair(0, 0);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		long long a, b;
		scanf("%d%lld%lld", &n, &a, &b);
		pair <long long, long long> p1 = solve(n, a - 1), p2 = solve(n, b - 1);
		long long d1 = p1.first - p2.first, d2 = p1.second - p2.second;
		printf("%.0f\n", 10 * sqrt(d1 * d1 + d2 * d2));
	}
	return 0;
}