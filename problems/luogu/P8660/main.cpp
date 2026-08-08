#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int TARGET = 20000; // 把所有坐标乘 2，这样 0.5 也能变成整数处理。

int n;
int a[MAXN], b[MAXN];

struct Interval {
    int need_left; // 当前覆盖前缀至少要到这里，区间才能接上。
    int dead;      // 当前覆盖前缀一旦达到这里或更右，这个区间就接不上了。
    int len;       // 区间本身的长度。
};

Interval seg[MAXN];

bool cmp_interval(const Interval &x, const Interval &y) {
    if (x.need_left != y.need_left) {
        return x.need_left < y.need_left;
    }
    if (x.dead != y.dead) {
        return x.dead < y.dead;
    }
    return x.len < y.len;
}

// 检查当最大位移不超过 lim2/2 时，是否能覆盖整个 [0, 10000]。
bool check(int lim2) {
    for (int i = 1; i <= n; i++) {
        seg[i].need_left = a[i] - lim2;
        seg[i].dead = b[i] + lim2;
        seg[i].len = b[i] - a[i];
    }

    sort(seg + 1, seg + n + 1, cmp_interval);

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    int covered = 0; // 当前已经连续覆盖到了 [0, covered]。
    int idx = 1;

    while (covered < TARGET) {
        while (idx <= n && seg[idx].need_left <= covered) {
            pq.push(make_pair(seg[idx].dead, seg[idx].len));
            idx++;
        }

        // 已经过期的区间，不可能再接住当前前缀，直接丢掉。
        while (!pq.empty() && pq.top().first <= covered) {
            pq.pop();
        }

        if (pq.empty()) {
            return false;
        }

        int dead = pq.top().first;
        int len = pq.top().second;
        pq.pop();

        covered = min(covered + len, dead);
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        a[i] *= 2;
        b[i] *= 2;
    }

    int left = 0;
    int right = TARGET;
    while (left < right) {
        int mid = (left + right) >> 1;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if ((left & 1) == 0) {
        cout << left / 2 << '\n';
    } else {
        cout << left / 2 << ".5\n";
    }

    return 0;
}
