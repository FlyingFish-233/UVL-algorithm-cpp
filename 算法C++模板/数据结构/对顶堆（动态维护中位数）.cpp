// AcWing106 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

priority_queue <int, vector<int>, less<int> > q1;
priority_queue <int, vector<int>, greater<int> > q2;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int id, n;
		scanf("%d %d", &id, &n);
		printf("%d %d\n", id, n / 2 + 1);
		for (int i = 1, x; i <= n; i++) {
			scanf("%d", &x);
			if (!q1.empty() && x <= q1.top()) q1.push(x);
			else q2.push(x);
			while ((int) q1.size() > i / 2) q2.push(q1.top()), q1.pop();
			while ((int) q1.size() < i / 2) q1.push(q2.top()), q2.pop();
			if (i & 1) printf("%d ", q2.top());
			if (i % 20 == 0) puts("");
		}
		if (n % 20 != 0) puts("");
		while (!q1.empty()) q1.pop();
		while (!q2.empty()) q2.pop();
	}
	return 0;
}