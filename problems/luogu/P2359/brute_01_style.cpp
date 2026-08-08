// brute_01_style.cpp：选择序列风格暴力，按位决定当前数字填什么。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MOD = 1000000009;

int n;
int digit[MAXN];
int answer;

bool is_prime(int x) {
    if (x < 2) {
        return false;
    }
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

bool check() {
    if (digit[1] == 0) return false;
    for (int i = 3; i <= n; i++) {
        int val = digit[i - 2] * 100 + digit[i - 1] * 10 + digit[i];
        if (val < 100 || !is_prime(val)) return false;
    }
    return true;
}

void dfs_build(int pos) {
    if (pos == n + 1) {
        if (check()) {
            answer++;
            if (answer >= MOD) {
                answer -= MOD;
            }
        }
        return;
    }

    // 第 pos 位可以填 0..9；完整生成后再统一检查。
    for (int d = 0; d <= 9; d++) {
        digit[pos] = d;
        dfs_build(pos + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    if (n < 3) {
        cout << 0 << '\n';
        return 0;
    }

    answer = 0;
    dfs_build(1);

    cout << answer << '\n';
    return 0;
}
