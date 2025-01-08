# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <queue>

using namespace std;

const int NR = 3e4 + 10;

int n, m;
int a[NR], cnt[NR], ans[NR];
priority_queue<int, vector<int>, less<int> > q1;
priority_queue<int, vector<int>, greater<int> > q2;

void change(int k)
{
	while ((int) q1.size() < k) q1.push(q2.top()), q2.pop();
	while ((int) q1.size() > k) q2.push(q1.top()), q1.pop();
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1, x; i <= m; i++)
		scanf("%d", &x), cnt[x]++;
	for (int i = 1, k = 1; i <= n; i++) {
		if (!q1.empty() && a[i] <= q1.top()) q1.push(a[i]);
		else q2.push(a[i]);
		change(k);
		while (cnt[i]--) ans[k] = q1.top(), change(++k);
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}