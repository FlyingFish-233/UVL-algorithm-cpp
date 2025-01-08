# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e6 + 10;

int n, len;
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

long long read()
{
	len = 0;
	for (int i = 1, x; i <= n * n; i++) {
		scanf("%d", &x);
		if (x != 0) a[++len] = x;
	}
	if (len == 0) return 0;
	return mergeSort(1, len);
}

int main()
{
	while (scanf("%d", &n) != EOF)
		if (read() % 2 == read() % 2) printf("TAK\n");
		else printf("NIE\n");
	return 0;
}