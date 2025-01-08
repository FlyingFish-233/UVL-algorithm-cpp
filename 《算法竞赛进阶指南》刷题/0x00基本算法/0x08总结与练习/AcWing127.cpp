# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10, MR = 100 + 10;

struct Array
{
	int x, y;

	bool operator < (const Array &cmp) const {
		if (x != cmp.x) return x > cmp.x;
		return y > cmp.y;
	}
};

int n, m;
Array a[NR], b[NR];
int box[MR];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &b[i].x, &b[i].y);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	int ans = 0;
	long long sum = 0;
	for (int i = 1, j = 0; i <= m; i++) {
		while (j < n && a[j + 1].x >= b[i].x) j++, box[a[j].y]++;
		for (int k = b[i].y; k <= 100; k++)
			if (box[k]) {
				box[k]--, ans++;
				sum += 500 * b[i].x + 2 * b[i].y;
				break;
			}
	}
	printf("%d %lld\n", ans, sum);
	return 0;
}