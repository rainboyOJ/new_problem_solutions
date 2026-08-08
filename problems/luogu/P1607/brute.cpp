#include <bits/stdc++.h>
using namespace std;

const int MAXK = 50000 + 5;
const int MAXN = 20000 + 5;

struct Order {
    int s, e, m;
};

int req_cnt, stop_cnt, cap;
Order ord[MAXK];
int used[MAXN];
long long suffix_sum[MAXK];
long long best_ans;

int calc_limit(int idx) {
    int limit = ord[idx].m;
    for (int i = ord[idx].s; i < ord[idx].e; i++) {
        limit = min(limit, cap - used[i]);
    }
    return limit;
}

void add_interval(int idx, int val) {
    for (int i = ord[idx].s; i < ord[idx].e; i++) {
        used[i] += val;
    }
}

void dfs(int idx, long long cur) {
    if (idx > req_cnt) {
        best_ans = max(best_ans, cur);
        return;
    }

    // 一个简单上界：后面的所有请求都全部接上。
    if (cur + suffix_sum[idx] <= best_ans) {
        return;
    }

    int limit = calc_limit(idx);
    for (int take = limit; take >= 0; take--) {
        add_interval(idx, take);
        dfs(idx + 1, cur + take);
        add_interval(idx, -take);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个只用于小数据验证的精确暴力。
    // 对每个请求枚举“到底接多少头牛”，然后搜索全局最优。
    cin >> req_cnt >> stop_cnt >> cap;
    for (int i = 1; i <= req_cnt; i++) {
        cin >> ord[i].s >> ord[i].e >> ord[i].m;
    }

    suffix_sum[req_cnt + 1] = 0;
    for (int i = req_cnt; i >= 1; i--) {
        suffix_sum[i] = suffix_sum[i + 1] + ord[i].m;
    }

    dfs(1, 0);
    cout << best_ans << '\n';
    return 0;
}
