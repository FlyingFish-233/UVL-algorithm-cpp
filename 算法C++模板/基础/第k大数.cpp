// AcWing104 (100 pts) 
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n;
int a[NR];

int kth(int l, int r, int k)
{
	if (l == r) return a[l];
    int i = l, t1 = l, t2 = r, key = a[(l + r) >> 1];
    while (i <= t2) {
    	if (a[i] < key) swap(a[i++], a[t1++]);
    	else if (a[i] > key) swap(a[i], a[t2--]);
    	else i++;
    }
    if (k <= t1 - l) return kth(l, t1 - 1, k);
    if (k >= t2 - l + 2) return kth(t2 + 1, r, k - (t2 - l + 1));
    return key;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int x = kth(1, n, n / 2 + 1), sum = 0;
	for (int i = 1; i <= n; i++)
		sum += abs(a[i] - x);
	printf("%d\n", sum);
	return 0;
}
