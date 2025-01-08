# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 5e5 + 10;

int n;
int a[NR], b[NR];

long long mergeSort(int l, int r)
{
	if (l == r) return 0;
	int mid = (l + r) >> 1, t1 = l, t2 = mid + 1;
	long long ans = mergeSort(l, mid) + mergeSort(mid + 1, r);
	for (int i = l; i <= r; i++)
		if (t2 > r || (t1 <= mid && a[t1] <= a[t2])) b[i] = a[t1++];
		else b[i] = a[t2++], ans += mid - t1 + 1;
	for (int i = l; i <= r; i++)
		a[i] = b[i];
	return ans;
}

int main()
{
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		printf("%lld\n", mergeSort(1, n));
	}
	return 0;
}