// brute.cpp：小数据暴力解，使用 01 序列枚举每个好友打或不打。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;              // 好友数量
int x;              // 药水数量
int lose_exp[MAXN]; // 失败时获得的经验
int win_exp[MAXN];  // 胜利时获得的经验
int need[MAXN];     // 打过至少需要的药水数量
int choose_friend[MAXN]; // choose_friend[i] = 0/1，表示不打/打第 i 个好友
long long best_answer;   // 最大经验值

// 检查当前选择方案的总药水消耗是否不超过 x
bool check() {
    int total_need = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_friend[i] == 1) total_need += need[i];
    }
    return total_need <= x;
}

// 计算当前选择方案的总经验
long long calc_answer() {
    long long total = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_friend[i] == 1)
            total += win_exp[i];
        else
            total += lose_exp[i];
    }
    return total;
}

// 01 序列递归枚举
void dfs(int dep) {
    if (dep == n + 1) {
        if (check()) {
            long long cur = calc_answer();
            if (best_answer < cur) best_answer = cur;
        }
        return;
    }

    // 第 dep 个好友：0 不打，1 打
    for (int i = 0; i <= 1; i++) {
        choose_friend[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> lose_exp[i] >> win_exp[i] >> need[i];
    }

    best_answer = 0;
    dfs(1);

    cout << 5LL * best_answer << '\n';
    return 0;
}
