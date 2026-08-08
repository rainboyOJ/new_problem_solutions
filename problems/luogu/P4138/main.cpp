#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const long long NEG_INF = -(1LL << 60);

int n;
int zero_cnt, opt_cnt;
int zero_value[MAXN];     // A=0 且 B>0 的挂饰喜悦值
int opt_cap[MAXN];        // 负收益可选挂饰增加的额外挂钩数 A-1
long long opt_joy[MAXN];  // 对应的喜悦值
long long prefix[MAXN];   // zero_value 排序后的前缀和
long long dp[MAXN], ndp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    long long base_joy = 0; // 一定选择的挂饰总喜悦值
    int base_cap = 0;       // 一定选择的挂饰总额外挂钩数

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;

        if (a == 0) {
            // 没有挂钩的挂饰只能当叶子或唯一根。
            // 如果喜悦值不为正，就没有任何保留价值。
            if (b > 0) {
                zero_value[++zero_cnt] = b;
            }
            continue;
        }

        if (b >= 0) {
            // A>=1 且收益非负：一定值得选。
            // 它作为非根节点时，净增加 A-1 个可用挂钩。
            base_joy += b;
            base_cap += a - 1;
            continue;
        }

        if (a >= 2) {
            // 这类挂饰会亏分，但能增加额外挂钩，
            // 可能值得为了接更多正收益叶子而选择。
            opt_cap[++opt_cnt] = a - 1;
            opt_joy[opt_cnt] = b;
        }
        // a==1 且 b<0：不增加挂钩，还会降低答案，一定不选。
    }

    sort(zero_value + 1, zero_value + zero_cnt + 1, greater<int>());
    for (int i = 1; i <= zero_cnt; i++) {
        prefix[i] = prefix[i - 1] + zero_value[i];
    }

    int limit = zero_cnt;
    for (int i = 0; i <= limit; i++) {
        dp[i] = NEG_INF;
    }
    dp[0] = 0;

    // 对负收益但能增加挂钩的挂饰做 0/1 背包。
    for (int i = 1; i <= opt_cnt; i++) {
        for (int j = 0; j <= limit; j++) {
            ndp[j] = dp[j];
        }

        int w = opt_cap[i];
        if (w > limit) {
            w = limit;
        }

        for (int j = 0; j <= limit; j++) {
            if (dp[j] == NEG_INF) {
                continue;
            }
            int nj = j + w;
            if (nj > limit) {
                nj = limit;
            }
            ndp[nj] = max(ndp[nj], dp[j] + opt_joy[i]);
        }

        for (int j = 0; j <= limit; j++) {
            dp[j] = ndp[j];
        }
    }

    long long answer = 0;

    for (int extra = 0; extra <= limit; extra++) {
        if (dp[extra] == NEG_INF) {
            continue;
        }

        // 如果当前总额外挂钩数是 base_cap + extra，
        // 那么最多还能接 base_cap + extra + 1 个 A=0 的正收益挂饰。
        int can_take = base_cap + extra + 1;
        if (can_take > zero_cnt) {
            can_take = zero_cnt;
        }

        long long cur = base_joy + dp[extra] + prefix[can_take];
        answer = max(answer, cur);
    }

    cout << answer << '\n';
    return 0;
}
