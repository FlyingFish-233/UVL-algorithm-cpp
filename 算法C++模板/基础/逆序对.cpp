// P1908 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 500010;

int n;
int a[NR], b[NR];
long long ans;

void mergeSort(int l, int r)
{
	if (l >= r) return;
	int mid = (l + r) / 2;
	mergeSort(l, mid), mergeSort(mid + 1, r);
	int t1 = l, t2 = mid + 1;
	for (int i = l; i <= r; i++){
		if (t2 > r || (t1 <= mid && a[t1] <= a[t2])) b[i] = a[t1++];
		else b[i] = a[t2++], ans += mid - t1 + 1;
	}
	for (int i = l; i <= r; i++)
		a[i] = b[i];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	mergeSort(1, n);
	printf("%lld\n", ans);
	return 0;
}
