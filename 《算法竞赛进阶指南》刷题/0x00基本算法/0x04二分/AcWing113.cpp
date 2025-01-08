// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution {
public:
    vector<int> specialSort(int N) {
        vector <int> a;
        for (int i = 1; i <= N; i++)
        	a.push_back(i);
        for (int i = 1; i <= N - 1; i++) {
        	int l = 0, r = i - 1, ans = i, tmp = a[i];
        	while (l <= r) {
        		int mid = (l + r) >> 1;
        		if (compare(tmp, a[mid])) r = mid - 1, ans = mid;
        		else l = mid + 1;
        	}
        	for (int j = i - 1; j >= ans; j--)
        		a[j + 1] = a[j];
        	a[ans] = tmp;
        }
        return a;
    }
};