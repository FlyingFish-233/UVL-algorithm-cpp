# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

struct Array
{
    int len, num;
    bool operator < (const Array &cmp) const {
        if (num != cmp.num) return num > cmp.num;
        return len > cmp.len;
    }
};

int n;
int a[NR];
priority_queue<Array> q;

bool check(int k)
{
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && a[i] > q.top().num + 1) {
            if (q.top().len < k) return false;
            q.pop();
        }
        if (q.empty()) { q.push((Array) {1, a[i]}); continue; }
        int x = q.top().num, l = q.top().len;
        if (a[i] == x) q.push((Array) {1, a[i]});
        if (a[i] == x + 1) q.pop(), q.push((Array) {l + 1, a[i]});
    }
    while (!q.empty()) {
        if (q.top().len < k) return false;
        q.pop();
    }
    return true;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    int l = 1, r = n, ans = 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}