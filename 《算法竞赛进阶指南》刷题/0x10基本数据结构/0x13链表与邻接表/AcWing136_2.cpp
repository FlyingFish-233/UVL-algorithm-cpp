# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <set>
# include <climits>

using namespace std;

int n;
set< pair<int, int> > s;

int main()
{
	scanf("%d", &n);
	s.insert({INT_MIN, 0});
	s.insert({INT_MAX, 0});
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		if (i > 1) {
			auto it = s.upper_bound({x, 0}); // set<Node>::iterator
			auto jt = it; jt--;
			long long t1 = (long long) x - (jt -> first);
			long long t2 = (long long) (it -> first) - x;
			if (t1 <= t2) printf("%lld %d\n", t1, jt -> second);
			else printf("%lld %d\n", t2, it -> second);
		}
		s.insert({x, i});
	}
	return 0;
}