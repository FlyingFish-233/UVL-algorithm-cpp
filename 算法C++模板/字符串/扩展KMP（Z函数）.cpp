// P5410 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>

using namespace std;

const int NR = 4e7 + 10;

int len1, len2;
string s1, s2;
int z[NR];

void getZ(string s)
{
    int len = s.size();
    for (int i = 1, l = 0; i <= len; i++) {
        if (i <= l + z[l] - 1) z[i] = min(z[i - l], l + z[l] - i);
        while (i + z[i] < len && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] > l + z[l]) l = i;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> s1 >> s2;
    len1 = s1.size(), len2 = s2.size();
    getZ(s2 + '$' + s1);
    long long ans1 = len2 + 1, ans2 = 0;
    for (int i = 1; i < len2; i++)
        ans1 ^= 1ll * (i + 1) * (z[i] + 1);
    for (int i = 0; i < len1; i++)
        ans2 ^= 1ll * (i + 1) * (z[i + len2 + 1] + 1);
    printf("%lld\n%lld\n", ans1, ans2);
    return 0;
}