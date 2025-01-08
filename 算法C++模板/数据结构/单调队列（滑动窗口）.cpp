# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int n, k;
int a[NR];
int l, r, q[NR];

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	l = 1, r = 0;
	for (int i = 1; i <= n; i++) {
		while (l <= r && q[l] <= i - k) l++;
		while (l <= r && a[q[r]] >= a[i]) r--;
		q[++r] = i;
		if (i >= k) printf("%d ", a[q[l]]);
	}
	puts("");
	
	l = 1, r = 0;
	for (int i = 1; i <= n; i++) {
		while (l <= r && q[l] <= i - k) l++;
		while (l <= r && a[q[r]] <= a[i]) r--;
		q[++r] = i;
		if (i >= k) printf("%d ", a[q[l]]);
	}
	puts("");
	return 0;
}