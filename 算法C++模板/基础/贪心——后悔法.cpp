// P2949 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

struct Array
{
	int t, x;
	bool operator < (const Array cmp) const {
		return t < cmp.t;
	} 
};

int n;
Array a[NR];
priority_queue<int, vector<int>, greater<int> > q;

int main()
{
	scanf("%d", &n); 
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].t, &a[i].x);
	sort(a + 1, a + n + 1);
	long long ans = 0;
	// q维护的是当前1~i这i个时间上的i个工作的利润 
	for (int i = 1; i <= n; i++)
		if (a[i].t <= q.size()) {
			if (q.top() < a[i].x)
				ans += a[i].x - q.top(), q.pop(), q.push(a[i].x);
		}
		else {
			ans += a[i].x, q.push(a[i].x);
		}
	printf("%lld\n", ans);
	return 0;
}

