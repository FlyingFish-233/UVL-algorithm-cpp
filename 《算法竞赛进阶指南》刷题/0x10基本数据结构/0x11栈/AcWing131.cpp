# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>

using namespace std;

const int NR = 1e5 + 10;

int n, a[NR];
stack< pair<int, int> > s;
long long ans;

int main()
{
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		while (!s.empty()) s.pop();
		ans = a[n + 1] = 0;
		for (int i = 1; i <= n + 1; i++) {
			int sum = 0;
			while (!s.empty() && s.top().first >= a[i]) {
				sum += s.top().second;
				ans = max(ans, 1ll * sum * s.top().first);
				s.pop();
			}
			s.push(make_pair(a[i], sum + 1));
		}
		printf("%lld\n", ans);
	}
	return 0;
}