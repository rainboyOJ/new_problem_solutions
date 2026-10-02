/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 17:33
 * update_at: 2026-10-02 18:59
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// main.cpp：n <= 50 用暴力 DFS 打表查表，n > 50 用 n = 7k + r 的规律输出。

ll stick[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}; // 各数字消耗的木棍数
ll rcd[60];                                  // 当前拼到的数字序列
ll ans;                                      // 当前最优答案
ll ans_len;                                  // 当前最优答案的位数，用于剪枝

// 打表：dfs(pos, rest) 表示正在决定第 pos 位、还剩 rest 根木棍
void dfs(ll pos, ll rest) {
    if (rest == 1) {
        return; // 剩 1 根拼不出任何数字
    }
    if (rest == 0) {
        // 拼完一整条路径，把序列转成数字，取最小
        ll num = 0;
        for (ll i = 1; i < pos; i++) num = num * 10 + rcd[i];
        if (ans == -1 || ans > num) {
            ans_len = pos - 1;
            ans = num;
        }
        return;
    }

    // 剪枝：已确定的位数超过当前最优解的位数，后面只会更大
    if (ans_len != -1 && pos > ans_len) return;

    ll start = 0;
    if (pos == 1) start = 1; // 首位不能为 0

    for (ll i = 9; i >= start; i--) { // 倒序枚举，尽快把 ans_len 压小
        if (rest < stick[i]) continue;
        rcd[pos] = i;
        dfs(pos + 1, rest - stick[i]);
    }
}

// 连续输出 c 个字符 ch
void print_repeat(char ch, ll c) {
    for (ll i = 1; i <= c; i++)
        cout << ch;
}

// 规律：n = 7k + r 时答案完全由 r 决定
void print_pattern(ll n) {
    ll k = n / 7; // n = 7k + r
    ll r = n % 7;

    // 每位都放 8 用满 7 根，再把「多用的」分摊到高位：
    // 1 省 5 根，7 省 4 根，4 省 3 根，2/3/5 省 2 根，0/6/9 省 1 根，8 省 0 根。
    if (r == 0) {
        // 7k：恰好 k 位，每位都要用满 7 根，只能全是 8
        print_repeat('8', k);
    } else if (r == 1) {
        // 7k+1：k+1 位共省 6 根 = 1 省 5 + 0 省 1，其余全 8
        cout << "10";
        print_repeat('8', k - 1);
    } else if (r == 2) {
        // 7k+2：k+1 位共省 5 根 = 1 省 5，其余全 8
        cout << '1';
        print_repeat('8', k);
    } else if (r == 3) {
        if (k == 0) {
            cout << '7'; // n = 3：一位省 4 根
        } else if (k == 1) {
            cout << "22"; // n = 10：两位各省 2 根
        } else {
            // 7k+3, k >= 2：共省 4 根 = 2 省 2 + 0 省 1 + 0 省 1
            cout << "200";
            print_repeat('8', k - 2);
        }
    } else if (r == 4) {
        if (k == 0) {
            cout << '4'; // n = 4：一位省 3 根
        } else {
            // 7k+4：共省 3 根 = 2 省 2 + 0 省 1，其余全 8
            cout << "20";
            print_repeat('8', k - 1);
        }
    } else if (r == 5) {
        // 7k+5：共省 2 根 = 2 省 2，其余全 8
        cout << '2';
        print_repeat('8', k);
    } else {
        // 7k+6：共省 1 根 = 6 省 1（0 不能放首位），其余全 8
        cout << '6';
        print_repeat('8', k);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;

        if (n == 1) { // 一位数字最少要 2 根，无解
            cout << -1 << '\n';
            continue;
        }

        if (n <= 50) { // 小数据：暴力 DFS 现场打表
            ans = -1;
            ans_len = -1;
            dfs(1, n);
            cout << ans << '\n';
        } else { // 大数据：按规律直接输出
            print_pattern(n);
            cout << '\n';
        }
    }

    return 0;
}
