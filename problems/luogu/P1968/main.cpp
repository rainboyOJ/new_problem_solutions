#include <bits/stdc++.h>
using namespace std;

int n;
double rate[105]; // rate[i] 表示第 i 天的汇率：100 美元 = rate[i] 马克

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> rate[i];
    }

    // dollar：以美元结尾的最大美元价值
    // mark：以马克结尾的最大马克价值
    double dollar = 100.0;
    double mark = 0.0;

    for (int i = 1; i <= n; i++) {
        double r = rate[i];
        // 当天结束时持有美元：要么昨天就持有美元（不动），要么昨天持有马克并在今天兑换
        double new_dollar = max(dollar, mark * 100.0 / r);
        // 当天结束时持有马克：要么昨天就持有马克（不动），要么昨天持有美元并在今天兑换
        double new_mark = max(mark, dollar * r / 100.0);
        dollar = new_dollar;
        mark = new_mark;
    }

    cout << fixed << setprecision(2) << dollar << "\n";
    return 0;
}
