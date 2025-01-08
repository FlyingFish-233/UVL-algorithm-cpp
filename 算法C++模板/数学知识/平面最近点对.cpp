// P1429 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;
const double angle = 1;

struct Node
{
	double x, y;
};

int n;
Node a[NR], b[NR];
double ans = 1e18;

bool cmp_x(Node p, Node q)
{
	if (p.x != q.x) return p.x < q.x;
	return p.y < q.y;
}

bool cmp_y(Node p, Node q)
{
	if (p.y != q.y) return p.y < q.y;
	return p.x < q.x;
}

double dis(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void dfs(int l, int r)
{
	if (l == r) return;
	int mid = (l + r) >> 1;
	dfs(l, mid), dfs(mid + 1, r);
	int cnt = 0;
	for (int i = l; i <= r; i++) {
		if (a[i].x > a[mid].x + ans) break;
		if (a[i].x >= a[mid].x - ans) b[++cnt] = a[i];
	}
	sort(b + 1, b + cnt + 1, cmp_y);
	for (int i = 1; i <= cnt; i++)
		for (int j = i + 1; j <= cnt; j++) {
			if (b[j].y > b[i].y + ans) break;
			ans = min(ans, dis(b[i].x, b[i].y, b[j].x, b[j].y));
		}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		a[i].x = x * cos(angle) + y * sin(angle);
		a[i].y = y * cos(angle) - x * sin(angle);
	}
	sort(a + 1, a + n + 1, cmp_x);
	dfs(1, n);
	printf("%.4f\n", ans);
	return 0;
}