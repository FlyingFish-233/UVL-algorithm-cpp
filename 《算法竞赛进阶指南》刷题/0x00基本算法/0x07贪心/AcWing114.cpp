# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1010;

struct Bigint
{
	static const int Max = 5000;
	int len, num[Max];

	Bigint()
	{
		len = 1;
		memset(num, 0, sizeof(num));
	}

	bool operator < (const Bigint &cmp) const {
		if (len != cmp.len) return len < cmp.len;
		for (int i = len; i >= 1; i--)
			if (num[i] != cmp.num[i]) return num[i] < cmp.num[i];
		return false;
	}

	Bigint operator * (const int &x) const {
		Bigint S = *this;
		for (int i = 1; i <= S.len; i++)
			S.num[i] *= x;
		for (int i = 1; i <= S.len; i++) {
			S.num[i + 1] += S.num[i] / 10;
			S.num[i] %= 10;
			while (S.num[S.len + 1]) S.len++;
		}
		return S;
	}

	Bigint operator / (const int &x) const {
		Bigint S = *this;
		int now = 0;
		for (int i = S.len; i >= 1; i--) {
			now = now * 10 + S.num[i];
			S.num[i] = now / x;
			now %= x;
		}
		while (S.num[S.len] == 0 && S.len > 1) S.len--;
		return S;
	}

	void print()
	{
		for (int i = len; i >= 1; i--)
			printf("%d", num[i]);
		puts("");
	}
};

struct Array
{
	int l, r;

	bool operator < (const Array &cmp) const {
		return l * r < cmp.l * cmp.r;
	}
};

int n;
Array a[NR];
Bigint A, S;

int main()
{
	scanf("%d", &n);
	for (int i = 0; i <= n; i++)
		scanf("%d%d", &a[i].l, &a[i].r);
	sort(a + 1, a + n + 1);
	A.num[1] = 1;
	A = A * a[0].l;
	for (int i = 1; i <= n; i++) {
		S = max(S, A / a[i].r);
		A = A * a[i].l;
	}
	S.print();
	return 0;
}