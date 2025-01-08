# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

int n;
priority_queue<int, vector<int>, greater<int> > q;

int main()
{
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++)
		scanf("%d", &x), q.push(x);
	int ans = 0;
	while (q.size() > 1) {
		int x = q.top(); q.pop();
		int y = q.top(); q.pop();
		ans += x + y;
		q.push(x + y);
	}
	printf("%d\n", ans);
	return 0;
}