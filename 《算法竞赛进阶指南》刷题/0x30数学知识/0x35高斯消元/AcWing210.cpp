# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef unsigned long long LL;

const int NR = 1e4 + 10;

int n, m;
LL mat[NR];

int Gause()
{
	for (int i = 1; i <= n; i++) {
		int row = i;
		for (int j = i + 1; j <= n; j++)
			if (mat[j] > mat[row]) row = j;
		if (mat[row] == 0) return i - 1;
		swap(mat[i], mat[row]);
		for (int k = 63; k >= 0; k--) 
			if (mat[i] >> k & 1) {
				for (int j = 1; j <= n; j++)
					if (i != j && mat[j] >> k & 1) mat[j] ^= mat[i];
				break;
			}
	}
	return n;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int cnt = 1; cnt <= T; cnt++) {
		printf("Case #%d:\n", cnt);
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			cin >> mat[i];
		int dim = Gause(), Q;
		scanf("%d", &Q);
		while (Q--) {
			LL k, ans = 0;
			cin >> k;
			if (dim < n) k--;
			if (k >= 1ull << dim) { cout << -1 << endl; continue; }
			for (int i = 0; i <= dim - 1; i++)
				if (k >> i & 1) ans ^= mat[dim - i];
			cout << ans << endl;
		}
	}
	return 0;
}