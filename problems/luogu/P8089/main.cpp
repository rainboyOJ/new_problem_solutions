#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXD = 1000005;

int T;
int dep_arr[15];
string s_arr[15];
int max_dep;
long long A[MAXD];

string minus_one_binary(string s) {
    int n = (int) s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '1') {
            s[i] = '0';
            for (int j = i + 1; j < n; j++) {
                s[j] = '1';
            }
            return s;
        }
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    max_dep = 0;
    for (int i = 1; i <= T; i++) {
        cin >> dep_arr[i];
        cin >> s_arr[i];
        if (dep_arr[i] > max_dep) {
            max_dep = dep_arr[i];
        }
    }

    // A[i] = 满 i 层完全二叉树的方案数 + 1。
    // A[0] = 1 对应空树。
    A[0] = 1;
    for (int i = 1; i <= max_dep; i++) {
        A[i] = (A[i - 1] * A[i - 1] + 1) % MOD;
    }

    for (int tc = 1; tc <= T; tc++) {
        int dep = dep_arr[tc];
        string s = s_arr[tc];

        if ((int) s.size() < dep) {
            s = string(dep - (int) s.size(), '0') + s;
        }

        if (dep == 1) {
            cout << 1 << '\n';
            continue;
        }

        // c 表示最后一层节点数，r = c - 1。
        // 对 dep 位二进制做减一后，最高位一定是 0，后面的 dep-1 位
        // 正好描述“最后一个叶子”在底层从左到右的 0-based 位置。
        s = minus_one_binary(s);

        long long val = 1; // 高度为 1 的单点树，只有选根这一种方案。
        int cur_h = 1;

        // 从低位往高位回推，相当于不断把当前子树向上接一层父亲。
        for (int i = dep - 1; i >= 1; i--) {
            if (s[i] == '0') {
                val = A[cur_h - 1] * (val + 1) % MOD;
            } else {
                val = A[cur_h] * (val + 1) % MOD;
            }
            cur_h++;
        }

        cout << val % MOD << '\n';
    }

    return 0;
}
