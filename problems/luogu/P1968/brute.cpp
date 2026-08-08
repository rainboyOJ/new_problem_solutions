// brute.cpp：小数据暴力枚举，用来帮助理解题意并辅助对拍。
// 时间复杂度 O(2^N)，只适合 N <= 10。

#include <bits/stdc++.h>
using namespace std;

int n;
double rate[105]; // rate[i] 表示第 i 天的汇率：100 美元 = rate[i] 马克

// 枚举所有兑换方案。
// day：当前在第几天（1-indexed）
// money：当前持有的金额
// has_dollar：true 表示当前持有美元，false 表示持有马克
double dfs(int day, double money, bool has_dollar) {
    if (day > n) {
        // 最后一天结束，如果还持有马克则按最后一天的汇率换回美元
        if (has_dollar) return money;
        else return money * 100.0 / rate[n];
    }
    double r = rate[day];
    // 不兑换，继续持有当前货币
    double best = dfs(day + 1, money, has_dollar);
    // 兑换全部资金
    if (has_dollar) {
        // 美元 -> 马克
        best = max(best, dfs(day + 1, money * r / 100.0, false));
    } else {
        // 马克 -> 美元
        best = max(best, dfs(day + 1, money * 100.0 / r, true));
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> rate[i];
    }

    double ans = dfs(1, 100.0, true);
    cout << fixed << setprecision(2) << ans << "\n";
    return 0;
}
