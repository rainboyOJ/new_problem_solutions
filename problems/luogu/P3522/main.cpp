#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int INF = 0x3f3f3f3f;

int n;
int x_arr[MAXN], y_arr[MAXN];
int all_y[MAXN];
int bit_min_pos[MAXN];
int bad_pos[MAXN];

// 树状数组维护前缀最小值。
void update(int idx, int val, int size) {
    while (idx <= size) {
        bit_min_pos[idx] = min(bit_min_pos[idx], val);
        idx += idx & -idx;
    }
}

int query(int idx) {
    int res = INF;
    while (idx > 0) {
        res = min(res, bit_min_pos[idx]);
        idx -= idx & -idx;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x_arr[i] >> y_arr[i];
        all_y[i] = y_arr[i];
    }

    sort(all_y + 1, all_y + n + 1);
    int m = (int)(unique(all_y + 1, all_y + n + 1) - (all_y + 1));

    for (int i = 1; i <= m; i++) {
        bit_min_pos[i] = INF;
    }

    // bad_pos[i] 表示最靠左的一个 j>i，使得 y_j < x_i。
    // 一旦这样的 j 落进区间 [l,r]，那么第 i 天与第 j 天就无法同时属于同一个不下降区间。
    for (int i = n; i >= 1; i--) {
        int pos_x = (int)(lower_bound(all_y + 1, all_y + m + 1, x_arr[i]) - all_y);
        if (pos_x > 1) {
            bad_pos[i] = query(pos_x - 1);
        }
        else {
            bad_pos[i] = INF;
        }

        int pos_y = (int)(lower_bound(all_y + 1, all_y + m + 1, y_arr[i]) - all_y);
        update(pos_y, i, m);
    }

    deque<int> q;
    int ans = 1;
    int l = 1;

    for (int r = 1; r <= n; r++) {
        // 队列维护当前窗口内 bad_pos 的最小值。
        while (!q.empty() && bad_pos[q.back()] >= bad_pos[r]) {
            q.pop_back();
        }
        q.push_back(r);

        while (!q.empty() && q.front() < l) {
            q.pop_front();
        }

        // 如果窗口里有人的 bad_pos 已经落进了当前 r，
        // 说明窗口内已经出现冲突，只能把左端点右移。
        while (!q.empty() && bad_pos[q.front()] <= r) {
            l = q.front() + 1;
            q.pop_front();
            while (!q.empty() && q.front() < l) {
                q.pop_front();
            }
        }

        ans = max(ans, r - l + 1);
    }

    cout << ans << '\n';
    return 0;
}
