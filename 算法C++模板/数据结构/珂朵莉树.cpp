// CF896C (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <set>
# include <vector>

# define LL long long
# define IT set<Node>::iterator

using namespace std;

const int INF = 0x3f3f3f3f;

struct Node
{
    int l, r;
    mutable LL v;
    Node(int l, int r, LL v) : l(l), r(r), v(v) {}
    bool operator < (const Node &cmp) const { return l < cmp.l; }
};

set<Node> tree;

// 把一个区间[l,r]分裂为[l,pos-1]和[pos,r], 并返回[pos,r]对应的指针
IT split(int pos)
{
    IT it = tree.lower_bound(Node(pos, 0, 0));
    if (it != tree.end() && it->l == pos) return it;
    it--;
    int l = it->l, r = it->r; LL v = it->v;
    tree.erase(it);
    tree.insert(Node(l, pos - 1, v));
    return tree.insert(Node(pos, r, v)).first; // set的insert()返回pair<iterator, bool>
}

void assign(int l, int r, LL v)
{
    IT it1 = split(l), it2 = split(r + 1);
    tree.erase(it1, it2);
    tree.insert(Node(l, r, v));
}

void add(int l, int r, LL v)
{
    IT it2 = split(r + 1);
    for (IT it = split(l); it != it2; it++)
        it->v += v;
}

LL kth(int l, int r, int k)
{
    IT it2 = split(r + 1);
    vector< pair<LL, int> > v;
    for (IT it = split(l); it != it2; it++)
        v.push_back(make_pair(it->v, it->r - it->l + 1));
    sort(v.begin(), v.end());
    for (int i = 0; i < (int) v.size(); i++) {
        k -= v[i].second;
        if (k <= 0) return v[i].first;
    }
    return 0;
}

LL qpow(LL a, int b, int p)
{
    LL sum = 1; a %= p;
    for (int i = b; i; i >>= 1, a = a * a % p)
        if (i & 1) sum = sum * a % p;
    return sum;
}

LL getsum(int l, int r, int x, int p)
{
    IT it2 = split(r + 1);
    LL sum = 0;
    for (IT it = split(l); it != it2; it++)
        sum = (sum + 1ll * qpow(it->v, x, p) * (it->r - it->l + 1)) % p;
    return sum;
}

int n, m, seed, vmax;

int rnd()
{
    int ret = seed;
    seed = (7ll * seed + 13) % 1000000007;
    return ret;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &seed, &vmax);
    for (int i = 1; i <= n; i++)
        tree.insert(Node(i, i, rnd() % vmax + 1));
    while (m--) {
        int op = rnd() % 4 + 1, l = rnd() % n + 1, r = rnd() % n + 1, x = 0, y = 0;
        if (l > r) swap(l, r);
        if (op == 3) x = rnd() % (r - l + 1) + 1;
        else x = rnd() % vmax + 1;
        if (op == 4) y = rnd() % vmax + 1;

        if (op == 1) add(l, r, x);
        if (op == 2) assign(l, r, x);
        if (op == 3) printf("%lld\n", kth(l, r, x));
        if (op == 4) printf("%lld\n", getsum(l, r, x, y));
    }
    return 0;
}