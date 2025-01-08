# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <deque>

using namespace std;

const int NR = 3e5 + 10;

struct Node
{
	int id, val;
};

int n, m;
int a[NR], s[NR];
deque<Node> q;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
	int ans = -2e9;
	q.push_front((Node) {0, 0});
	for (int i = 1; i <= n; i++) {
		while (!q.empty() && q.back().id < i - m) q.pop_back();
		ans = max(ans, s[i] - q.back().val);
		while (!q.empty() && q.front().val >= s[i]) q.pop_front();
		q.push_front((Node) {i, s[i]});
	}
	printf("%d\n", ans);
	return 0;
}