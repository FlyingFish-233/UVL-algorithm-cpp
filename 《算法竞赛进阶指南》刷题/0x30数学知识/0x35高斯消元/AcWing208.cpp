# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 100;

int n;
int mat[NR];

int Gause()
{
	for (int i = 1; i <= n; i++) {
		int row = i;
		for (int j = i + 1; j <= n; j++)
			if (mat[j] > mat[row]) row = j;
		if (mat[row] == 0) return 1 << (n - (i - 1));
		if (mat[row] == 1) return 0;
		swap(mat[i], mat[row]);
		for (int k = n; k >= 1; k--) 
			if (mat[i] >> k & 1) {
				for (int j = 1; j <= n; j++)
					if (i != j && mat[j] >> k & 1) mat[j] ^= mat[i];
				break;
			}
	}
	return 1;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			mat[i] = 1 << i;
		for (int i = 1, x; i <= n; i++)
			scanf("%d", &x), mat[i] ^= x;
		for (int i = 1, x; i <= n; i++)
			scanf("%d", &x), mat[i] ^= x;
		for (int x, y; scanf("%d%d", &x, &y) && !(x == 0 && y == 0); )
			mat[y] |= 1 << x;
		int ans = Gause();
		if (ans == 0) printf("Oh,it's impossible~!!\n");
		else printf("%d\n", ans);
	}
	return 0;
}