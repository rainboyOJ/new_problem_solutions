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

// dfs_build(pos)：正在决定第 pos 位填哪个数字。
void dfs_build(int pos) {
    if (pos == n + 1) {
        answer++;
        if (answer >= MOD) {
            answer -= MOD;
        }
        return;
    }

    int left = 0;
    if (pos == 1) {
        left = 1; // 第一位不能为 0。
    }

    for (int d = left; d <= 9; d++) {
        digit[pos] = d;

        if (pos >= 3) {
            int val = digit[pos - 2] * 100 + digit[pos - 1] * 10 + digit[pos];
            if (val < 100 || !is_prime(val)) {
                continue;
            }
        }

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
