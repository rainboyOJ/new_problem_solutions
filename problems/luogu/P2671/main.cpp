#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int MAXM = 100000 + 5;
const int MOD = 10007;

int n, m;
int number_val[MAXN];
int color_val[MAXN];

int cnt[MAXM][2];         // 某种颜色、某种奇偶性已经出现了多少个位置
int sum_pos[MAXM][2];     // 这些位置编号之和
int sum_num[MAXM][2];     // 这些位置上的数字之和
int sum_pos_num[MAXM][2]; // 这些位置的 pos * number 之和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> number_val[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> color_val[i];
    }

    int answer = 0;

    for (int i = 1; i <= n; i++) {
        int c = color_val[i];
        int p = i & 1; // 因为 y 是中点，所以 x 和 z 必须同奇偶。

        int pos_mod = i % MOD;
        int num_mod = number_val[i] % MOD;

        // 对于当前点 i，把它当成右端点 z。
        // 之前同颜色、同奇偶的每个位置 x，都会和它形成一个合法三元组。
        //
        // 单个配对贡献为：
        // (x + i) * (number[x] + number[i])
        //
        // 展开后是：
        // x * number[x] + i * number[x] + x * number[i] + i * number[i]
        //
        // 对所有历史位置一起求和，就得到下面四项。
        int add = 0;
        add = (add + sum_pos_num[c][p]) % MOD;
        add = (add + pos_mod * sum_num[c][p]) % MOD;
        add = (add + num_mod * sum_pos[c][p]) % MOD;
        add = (add + 1LL * cnt[c][p] * pos_mod % MOD * num_mod) % MOD;

        answer += add;
        answer %= MOD;

        cnt[c][p]++;
        if (cnt[c][p] >= MOD) cnt[c][p] -= MOD;
        sum_pos[c][p] += pos_mod;
        sum_pos[c][p] %= MOD;
        sum_num[c][p] += num_mod;
        sum_num[c][p] %= MOD;
        sum_pos_num[c][p] += pos_mod * num_mod;
        sum_pos_num[c][p] %= MOD;
    }

    cout << answer % MOD << '\n';
    return 0;
}
