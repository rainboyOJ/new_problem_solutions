/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 09:21
 * update_at: 2026-07-19 09:29
 */
#include <bits/stdc++.h>
using namespace std;

const int MAX_LENGTH = 5000;
const long long MOD = 1000000007;

int n;
int max_length;
long long count_length[MAX_LENGTH + 1]; // count_length[x] 表示长度 x 的木棒数量

long long choose_two(long long x) {
    return x * (x - 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int length;
        cin >> length;
        count_length[length]++;
        if (max_length < length) max_length = length;
    }

    long long answer = 0;

    // side 是三角形边长，需要两根长度为 side 的整边木棒。
    for (int side = 2; side <= max_length; side++) {
        if (count_length[side] < 2) continue;

        long long pair_choices = 0;

        // left < right，避免把同一对短棒按顺序重复计算。
        for (int left = 1; left * 2 < side; left++) {
            int right = side - left;
            pair_choices += count_length[left] * count_length[right];
        }

        // side 为偶数时，补上 left == right == side / 2 的情况。
        if (side % 2 == 0) {
            pair_choices += choose_two(count_length[side / 2]);
        }

        long long same_side_choices = choose_two(count_length[side]);
        answer += (same_side_choices % MOD) * (pair_choices % MOD) % MOD;
        answer %= MOD;
    }

    cout << answer << '\n';
    return 0;
}
