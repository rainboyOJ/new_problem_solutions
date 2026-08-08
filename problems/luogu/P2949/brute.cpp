// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 22;

struct Job {
    int deadline;
    long long profit;
};

int n;
Job jobs[MAXN];

bool check_subset(int mask) {
    vector<int> deadlines;
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            deadlines.push_back(jobs[i].deadline);
        }
    }

    sort(deadlines.begin(), deadlines.end());
    for (int i = 0; i < (int)deadlines.size(); i++) {
        int finish_time = i + 1;
        if (finish_time > deadlines[i]) {
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
        cin >> jobs[i].deadline >> jobs[i].profit;
    }

    long long ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!check_subset(mask)) {
            continue;
        }
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += jobs[i].profit;
            }
        }
        ans = max(ans, sum);
    }

    cout << ans << '\n';
    return 0;
}
