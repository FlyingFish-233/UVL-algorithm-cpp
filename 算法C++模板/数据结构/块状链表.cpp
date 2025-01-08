// P4008 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 8e3 + 10, SZ = 2e3;

struct Node
{
    int next, sz;
    char c[SZ + 10];
};

int cursor;
Node node[NR];

int tot, pool[NR];
int new_id() { return pool[++tot]; }
void del(int x) { pool[tot--] = x; }

void init()
{
    for (int i = 1; i < NR; i++)
        pool[i] = i;
    node[0].sz = 0, node[0].next = -1;
}

int newNode(int len, char c[])
{
    int x = new_id();
    memcpy(node[x].c, c, len);
    node[x].next = -1, node[x].sz = len;
    return x;
}

void add(int x, int y)
{
    node[y].next = node[x].next;
    node[x].next = y;
}

// 将块x分为前p个字符, 和后sz-p个字符
void split(int x, int p)
{
    add(x, newNode(node[x].sz - p, node[x].c + p));
    node[x].sz = p;
}

void maintain(int x)
{
    while (true) {
        int y = node[x].next;
        if (y == -1 || node[x].sz + node[y].sz > SZ) return;
        memcpy(node[x].c + node[x].sz, node[y].c, node[y].sz);
        node[x].next = node[y].next;
        node[x].sz += node[y].sz, del(y);
    }
}

int getpos(int &p)
{
    int x = 0;
    while (p > node[x].sz)
        p -= node[x].sz, x = node[x].next;
    return x;
}

void insert(int p, int len, char c[])
{
    int x = getpos(p); split(x, p);
    int now = 0, y = x;
    while (now + SZ < len) {
        add(y, newNode(SZ, c + now));
        now += SZ, y = node[y].next;
    }
    add(y, newNode(len - now, c + now));
    maintain(x), maintain(y);
}

void erase(int p, int len)
{
    int x = getpos(p); split(x, p);
    int y = node[x].next;
    while (len > node[y].sz)
        len -= node[y].sz, y = node[y].next;
    split(y, len);
    for (int i = node[x].next; i != node[y].next; i = node[i].next)
        node[x].next = node[i].next, del(i);
    maintain(x);
}

char str[3 * (1 << 20) + 10];

void getstr(int p, int len)
{
    int x = getpos(p), now = min(len, node[x].sz - p);
    memcpy(str, node[x].c + p, now);
    int y = node[x].next;
    while (now + node[y].sz < len) {
        memcpy(str + now, node[y].c, node[y].sz);
        now += node[y].sz, y = node[y].next;
    }
    memcpy(str + now, node[y].c, len - now);
    str[len] = '\0';
}

int main()
{
    int T;
    scanf("%d", &T);
    init();
    while (T--) {
        char op[10]; int x;
        scanf("%s", op);
        if (op[0] == 'M') scanf("%d", &x), cursor = x;
        if (op[0] == 'I') {
            scanf("%d", &x);
            for (int i = 0; i < x; i++) {
                str[i] = getchar();
                if (str[i] < 32 || str[i] > 126) i--;
            }
            insert(cursor, x, str);
        }
        if (op[0] == 'D') scanf("%d", &x), erase(cursor, x);
        if (op[0] == 'G') scanf("%d", &x), getstr(cursor, x), printf("%s\n", str);
        if (op[0] == 'P') cursor--;
        if (op[0] == 'N') cursor++;
    }
    return 0;
}