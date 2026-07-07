#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。

const int INF = 1e9;

int m;
vector<int> pows;
vector<int> choose_count; // choose_count[i] 表示第 i 种四次方数取多少个
int answer = INF;

int calc_sum() {
    int sum = 0;
    for (int i = 0; i < (int)pows.size(); i++) {
        sum += choose_count[i] * pows[i];
    }
    return sum;
}

int calc_count() {
    int cnt = 0;
    for (int i = 0; i < (int)pows.size(); i++) {
        cnt += choose_count[i];
    }
    return cnt;
}

// 依次枚举每种四次方数要用多少个，叶子节点统一检查。
void dfs_choose(int dep) {
    if (dep == (int)pows.size()) {
        if (calc_sum() == m) {
            int value = calc_count();
            if (answer > value) answer = value;
        }
        return;
    }

    int w = pows[dep];
    int limit = m / w;
    for (int cnt = 0; cnt <= limit; cnt++) {
        choose_count[dep] = cnt;
        dfs_choose(dep + 1);
    }
}

void read_input() {
    cin >> m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    for (int i = 1; ; i++) {
        long long x = 1LL * i * i * i * i;
        if (x > m) {
            break;
        }
        pows.push_back((int)x);
    }

    choose_count.assign(pows.size(), 0);
    dfs_choose(0);
    cout << answer << '\n';

    return 0;
}
