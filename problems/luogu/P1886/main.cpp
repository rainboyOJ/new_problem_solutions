#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000000 + 5;

int n, k;
int a[maxn];
deque<int> qmin, qmax;
vector<int> ans_min, ans_max;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        while (!qmin.empty() && qmin.front() <= i - k) {
            qmin.pop_front();
        }
        while (!qmin.empty() && a[qmin.back()] >= a[i]) {
            qmin.pop_back();
        }
        qmin.push_back(i);

        while (!qmax.empty() && qmax.front() <= i - k) {
            qmax.pop_front();
        }
        while (!qmax.empty() && a[qmax.back()] <= a[i]) {
            qmax.pop_back();
        }
        qmax.push_back(i);

        if (i >= k) {
            ans_min.push_back(a[qmin.front()]);
            ans_max.push_back(a[qmax.front()]);
        }
    }

    for (int i = 0; i < (int) ans_min.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << ans_min[i];
    }
    cout << '\n';

    for (int i = 0; i < (int) ans_max.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << ans_max[i];
    }
    cout << '\n';

    return 0;
}
