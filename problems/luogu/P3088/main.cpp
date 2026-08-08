#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

struct Cow {
    int x, h;
};

int n, d;
Cow cow[MAXN];
int left_max_h[MAXN];
int right_max_h[MAXN];

bool cmp_by_x(const Cow &a, const Cow &b) {
    return a.x < b.x;
}

void calc_left_max() {
    deque<int> q;

    for (int i = 1; i <= n; i++) {
        // 删除左侧距离超过 D 的牛，它们已经不在窗口里了。
        while (!q.empty() && cow[i].x - cow[q.front()].x > d) {
            q.pop_front();
        }

        if (q.empty()) {
            left_max_h[i] = 0;
        }
        else {
            left_max_h[i] = cow[q.front()].h;
        }

        // 把当前牛加入单调队列，维护窗口内高度最大值。
        while (!q.empty() && cow[q.back()].h <= cow[i].h) {
            q.pop_back();
        }
        q.push_back(i);
    }
}

void calc_right_max() {
    deque<int> q;

    for (int i = n; i >= 1; i--) {
        // 删除右侧距离超过 D 的牛。
        while (!q.empty() && cow[q.front()].x - cow[i].x > d) {
            q.pop_front();
        }

        if (q.empty()) {
            right_max_h[i] = 0;
        }
        else {
            right_max_h[i] = cow[q.front()].h;
        }

        while (!q.empty() && cow[q.back()].h <= cow[i].h) {
            q.pop_back();
        }
        q.push_back(i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 1; i <= n; i++) {
        cin >> cow[i].x >> cow[i].h;
    }

    sort(cow + 1, cow + n + 1, cmp_by_x);

    calc_left_max();
    calc_right_max();

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // 一头牛拥挤，当且仅当左右两边都存在一头高度至少是它两倍的牛。
        if ((long long)left_max_h[i] >= 2LL * cow[i].h &&
            (long long)right_max_h[i] >= 2LL * cow[i].h) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
