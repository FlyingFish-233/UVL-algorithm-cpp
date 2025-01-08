# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <deque>

using namespace std;

const int NR = 1e6 + 10;

int n, k;
int a[NR];
deque<int> q1, q2;
int ans1[NR], ans2[NR];

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		while (!q1.empty() && q1.back() <= i - k) q1.pop_back();
		while (!q1.empty() && a[q1.front()] >= a[i]) q1.pop_front();
		q1.push_front(i);
		ans1[i] = a[q1.back()];

		while (!q2.empty() && q2.back() <= i - k) q2.pop_back();
		while (!q2.empty() && a[q2.front()] <= a[i]) q2.pop_front();
		q2.push_front(i);
		ans2[i] = a[q2.back()];
	}
	for (int i = k; i <= n; i++)
		printf("%d ", ans1[i]);
	puts("");
	for (int i = k; i <= n; i++)
		printf("%d ", ans2[i]);
	puts("");
	return 0;
}