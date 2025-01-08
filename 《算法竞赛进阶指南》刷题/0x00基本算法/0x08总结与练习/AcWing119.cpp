# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

struct Node
{
	int x, y;
	bool type;

	bool operator < (const Node &cmp) const {
		return x < cmp.x;
	}
};

int n;
Node a[NR], b[NR], c[NR];

bool cmp(Node n1, Node n2)
{
	return n1.y < n2.y;
}

double dist(Node n1, Node n2)
{
	return sqrt(1.0 * (n1.x - n2.x) * (n1.x - n2.x) + 1.0 * (n1.y - n2.y) * (n1.y - n2.y));
}

double solve(int l, int r)
{
	if (l == r) return 2e9;
	int mid = (l + r) >> 1;
	double ans = min(solve(l, mid), solve(mid + 1, r));
	int save = a[mid].x, bsz = 0, csz = 0;
	for (int i = l; i <= mid; i++)
		if (abs(a[i].x - save) <= ans) b[++bsz] = a[i];
	for (int i = mid + 1; i <= r; i++)
		if (abs(a[i].x - save) <= ans) c[++csz] = a[i];
	sort(b + 1, b + bsz + 1, cmp);
	sort(c + 1, c + csz + 1, cmp);
	for (int i = 1; i <= bsz; i++)
		for (int j = 1; j <= csz && c[j].y - b[i].y <= ans; j++)
			if (b[i].type ^ c[j].type) ans = min(ans, dist(b[i], c[j]));
	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &a[i].x, &a[i].y), a[i].type = false;
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &a[n + i].x, &a[n + i].y), a[i].type = true;
		n <<= 1;
		sort(a + 1, a + n + 1);
		printf("%.3f\n", solve(1, n));
	}
	return 0;
}