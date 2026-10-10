#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 100005;

int q0_arr[MAXN];

bool compare_desc(int a, int b) {
    return a > b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q, u, v, t;
    if (!(cin >> n >> m >> q >> u >> v >> t)) return 0;

    for (int i = 0; i < n; ++i) {
        cin >> q0_arr[i];
    }
    sort(q0_arr, q0_arr + n, compare_desc);

    int head0 = 0, tail0 = n;
    queue<int> q1, q2;

    long long offset = 0;
    bool first1 = true;

    for (int i = 1; i <= m; ++i) {
        long long max_val = -3000000000LL;
        int which = -1;

        if (head0 < tail0 && q0_arr[head0] > max_val) {
            max_val = q0_arr[head0];
            which = 0;
        }
        if (!q1.empty() && q1.front() > max_val) {
            max_val = q1.front();
            which = 1;
        }
        if (!q2.empty() && q2.front() > max_val) {
            max_val = q2.front();
            which = 2;
        }

        if (which == 0) head0++;
        else if (which == 1) q1.pop();
        else if (which == 2) q2.pop();

        long long L = max_val + offset;

        if (i % t == 0) {
            if (!first1) cout << " ";
            cout << L;
            first1 = false;
        }

        long long L1 = L * u / v;
        long long L2 = L - L1;

        q1.push((int)(L1 - offset - q));
        q2.push((int)(L2 - offset - q));

        offset += q;
    }
    cout << "\n";

    int count = 0;
    bool first2 = true;

    while (head0 < tail0 || !q1.empty() || !q2.empty()) {
        long long max_val = -3000000000LL;
        int which = -1;

        if (head0 < tail0 && q0_arr[head0] > max_val) {
            max_val = q0_arr[head0];
            which = 0;
        }
        if (!q1.empty() && q1.front() > max_val) {
            max_val = q1.front();
            which = 1;
        }
        if (!q2.empty() && q2.front() > max_val) {
            max_val = q2.front();
            which = 2;
        }

        if (which == 0) head0++;
        else if (which == 1) q1.pop();
        else if (which == 2) q2.pop();

        count++;
        if (count % t == 0) {
            if (!first2) cout << " ";
            cout << (max_val + offset);
            first2 = false;
        }
    }
    cout << "\n";

    return 0;
}