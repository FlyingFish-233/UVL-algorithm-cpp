# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int f[20];

int main()
{
	memset(f, 0x3f, sizeof(f));
	f[1] = 1;
	for (int i = 2; i <= 12; i++)
		for (int j = 1; j <= i - 1; j++)
			f[i] = min(f[i], 2 * f[j] + (1 << (i - j)) - 1);
	for (int i = 1; i <= 12; i++)
		printf("%d\n", f[i]);
	return 0;
}