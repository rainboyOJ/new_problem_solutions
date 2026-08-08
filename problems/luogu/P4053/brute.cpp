// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 22;

struct Building {
    long long need_time;
    long long deadline;
};

int n;
Building buildings[MAXN];

bool cmp_building(const Building &a, const Building &b) {
    if (a.deadline != b.deadline) {
        return a.deadline < b.deadline;
    }
    return a.need_time < b.need_time;
}

bool check_subset(int mask) {
    vector<Building> chosen;
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            chosen.push_back(buildings[i]);
        }
    }

    sort(chosen.begin(), chosen.end(), cmp_building);
    long long cur = 0;
    for (int i = 0; i < (int)chosen.size(); i++) {
        cur += chosen[i].need_time;
        if (cur > chosen[i].deadline) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> buildings[i].need_time >> buildings[i].deadline;
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (check_subset(mask)) {
            ans = max(ans, __builtin_popcount((unsigned)mask));
        }
    }

    cout << ans << '\n';
    return 0;
}
