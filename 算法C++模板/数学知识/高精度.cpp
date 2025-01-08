// P1932 (100 pts)
# include <cstdio>
# include <cstring>
# include <algorithm>
# include <cmath>

using namespace std;

struct Bigint
{
    static const int M = 1e5 + 10;
    int num[M], len;

    Bigint() {
    	memset(num, 0, sizeof(num)), len = 1;
	}

    Bigint (int x) {
        memset(num, 0, sizeof(num)), len = 0;
        while (x) num[++len] = x % 10, x /= 10;
        if (len == 0) len++;
    }

    void read() {
    	char str[M];
        scanf("%s", str);
        len = strlen(str);
        for (int i = 1; i <= len; i++)
            num[i] = str[len - i] - '0';
    }

    void print() {
        for (int i = len; i >= 1; i--)
            printf("%d", num[i]);
        puts("");
    }

    bool operator < (const Bigint &cmp) const {
        if (len != cmp.len) return len < cmp.len;
        for (int i = len; i >= 1; i--)
            if (num[i] != cmp.num[i]) return num[i] < cmp.num[i];
        return false;
    }

    bool operator > (const Bigint &cmp) const { return cmp < *this; }
	bool operator <= (const Bigint &cmp) const { return !(cmp < *this); }
    bool operator >= (const Bigint &cmp) const { return !(*this < cmp); }
	bool operator != (const Bigint &cmp) const { return cmp < *this || *this < cmp; }
	bool operator == (const Bigint &cmp) const { return !(cmp < *this || *this < cmp); }

    Bigint operator + (const Bigint &A) const {
        Bigint S; S.len = max(len, A.len);
        for (int i = 1; i <= S.len; i++) {
            S.num[i] += num[i] + A.num[i];
            if (S.num[i] >= 10) S.num[i] -= 10, S.num[i + 1]++;
        }
        while (S.num[S.len + 1]) S.len++;
        return S;
    }

    Bigint operator - (const Bigint &A) const {
        Bigint S; S.len = max(len, A.len);
        for (int i = 1; i <= S.len; i++) {
            S.num[i] += num[i] - A.num[i];
            if (S.num[i] < 0) S.num[i] += 10, S.num[i + 1]--;
        }
        while (S.num[S.len] == 0 && S.len > 1) S.len--;
        return S;
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
        long long now = 0;
        for (int i = S.len; i >= 1; i--) {
            now = now * 10 + S.num[i];
            S.num[i] = now / x;
            now %= x;
        }
        while (S.num[S.len] == 0 && S.len > 1) S.len--;
        return S;
    }

    Bigint operator * (const Bigint &A) const {
        if ((A.len == 1 && A.num[1] == 0) || (len == 1 && num[1] == 0)) return Bigint();
        Bigint S; S.len = A.len + len - 1;
        for (int i = 1; i <= len; i++)
            for (int j = 1; j <= A.len; j++) {
                S.num[i + j - 1] += num[i] * A.num[j];
                S.num[i + j] += S.num[i + j - 1] / 10;
                S.num[i + j - 1] %= 10;
            }
        while(S.num[S.len + 1]) S.len++;
        return S;
    }

    Bigint operator / (const Bigint &A) const {
        if ((A.len == 1 && A.num[1] == 0) || (len == 1 && num[1] == 0)) return Bigint();
        Bigint now = *this, S; S.len = now.len - A.len + 1;
        for (int i = S.len; i >= 1; i--)
            while (true) {
                bool flag = true;
                for (int j = max(A.len, now.len - i + 1); j >= 1; j--) {
                    if (now.num[i + j - 1] > A.num[j]) { flag = true; break; }
                    if (now.num[i + j - 1] < A.num[j]) { flag = false; break; }
                }
                if (!flag) break;
                for (int j = 1; j <= A.len; j++) {
                    now.num[i + j - 1] -= A.num[j];
                    if (now.num[i + j - 1] < 0) now.num[i + j - 1] += 10, now.num[i + j]--;
                }
                while (now.num[now.len] == 0 && now.len > 1) now.len--;
                S.num[i]++;
            }
        while (S.num[S.len] == 0 && S.len > 1) S.len--;
        S.len = max(S.len, 1);
        return S;
    }

    Bigint operator % (const Bigint &A) const {
        return (*this) - (*this) / A * A;
    }
};

int main()
{
    Bigint A, B;
    A.read(), B.read();
    (A + B).print();
    if (A >= B) (A - B).print();
    else printf("-"), (B - A).print();
    (A * B).print();
    (A / B).print();
    (A % B).print();
	return 0;
}
