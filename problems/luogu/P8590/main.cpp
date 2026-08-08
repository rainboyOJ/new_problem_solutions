#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 998244353;

int n;
i64 k;
i64 a;

i64 norm(i64 x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

i64 mod_mul(i64 a, i64 b) {
    return (i64)((__int128)a * b % MOD);
}

i64 sum_1_to_x(i64 x) {
    if (x <= 0) return 0;
    return mod_mul(mod_mul(norm(x), norm(x + 1)), (MOD + 1) / 2);
}

i64 sum_square_1_to_x(i64 x) {
    if (x <= 0) return 0;
    i64 part1 = mod_mul(norm(x), norm(x + 1));
    i64 part2 = norm(2 * x + 1);
    return mod_mul(mod_mul(part1, part2), 166374059); // 6 在模 MOD 下的逆元
}

i64 range_sum(i64 l, i64 r) {
    if (l > r) return 0;
    return norm(sum_1_to_x(r) - sum_1_to_x(l - 1));
}

i64 range_sum_square(i64 l, i64 r) {
    if (l > r) return 0;
    return norm(sum_square_1_to_x(r) - sum_square_1_to_x(l - 1));
}

i64 contribution_of_one_number(i64 value, i64 limit_k) {
    // 对固定 a_i，只有当 m >= max(2, -2*a_i) 时，
    // 把它从“加 1”改成“加 m”才会带来正收益。
    i64 left = 2;
    if (value < 0) {
        i64 need = -2 * value;
        if (need > left) left = need;
    }

    if (left > limit_k) return 0;

    i64 cnt = limit_k - left + 1;
    i64 sum_m = range_sum(left, limit_k);
    i64 sum_m2 = range_sum_square(left, limit_k);

    // 单个 m 的增量：
    // (a_i + m)^2 - (a_i + 1)^2
    // = (m - 1)(2a_i + m + 1)
    // = m^2 + 2a_i * m - (2a_i + 1)
    i64 term1 = sum_m2;
    i64 term2 = mod_mul(norm(2 * value), sum_m);
    i64 term3 = mod_mul(norm(2 * value + 1), norm(cnt));
    return norm(term1 + term2 - term3);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    i64 base_sum = 0;   // sum (a_i + 1)^2
    i64 extra_sum = 0;  // 对所有 m>=2 的“把某个位置改成加 m”带来的额外收益总和

    for (int i = 1; i <= n; i++) {
        cin >> a;

        i64 x = norm(a + 1);
        base_sum += mod_mul(x, x);
        base_sum %= MOD;

        extra_sum += contribution_of_one_number(a, k);
        extra_sum %= MOD;
    }

    // 每个 q_m 至少都包含一份 sum(a_i + 1)^2。
    i64 answer = mod_mul(norm(k), base_sum);
    answer += extra_sum;
    answer %= MOD;

    cout << answer << '\n';
    return 0;
}
