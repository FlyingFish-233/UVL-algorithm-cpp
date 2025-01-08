# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <queue>

using namespace std;

struct Node
{
	int pos, len, stt, tim;
};

int n, ans, cnt;
vector<Node> pro;
queue<Node> q;

bool work_in(Node cur)
{
	for (int i = 1; i < (int) pro.size(); i++)
		if (pro[i].pos - pro[i - 1].pos - pro[i - 1].len >= cur.len) {
			cur.pos = pro[i - 1].pos + pro[i - 1].len;
			pro.insert(pro.begin() + i, cur);
			return true;
		}
	return false;
}

void work_out()
{
	for (int i = 0; i < (int) pro.size(); i++)
		if (pro[i].stt + pro[i].tim == ans) pro.erase(pro.begin() + i--);
	while (!q.empty()) {
		Node node = q.front();
		if (work_in((Node) {0, node.len, ans, node.tim})) q.pop();
		else break;
	}
	ans = 2e9;
	for (int i = 0; i < (int) pro.size(); i++)
		ans = min(ans, pro[i].stt + pro[i].tim);
}
int main()
{
	scanf("%d", &n);
	pro.push_back((Node) {-1, 1, 0, (int) 2e9});
	pro.push_back((Node) {n, 1, 0, (int) 2e9});
	while (true) {
		int t, m, p;
		scanf("%d%d%d", &t, &m, &p);
		if (t == 0 && m == 0 && p == 0) break;
		Node cur = (Node) {0, m, t, p};
		while (cur.stt >= ans) work_out();
		if (!work_in(cur)) q.push(cur), cnt++;
		else ans = min(ans, cur.stt + cur.tim);
	}
	while (!q.empty()) work_out();
	for (int i = 1; i < (int) pro.size() - 1; i++)
		ans = max(ans, pro[i].stt + pro[i].tim);
	printf("%d\n%d\n", ans, cnt);
	return 0;
}