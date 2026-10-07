/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:46
 * update_at: 2026-10-05 10:46
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXLEN = 12;

// memo[pos][last + 1]：从第 pos 位起在不受上限约束时能填出的方案数，
// 第二维用 last + 1 把小标，使 last = -1（还处于前导零阶段）正好落在下标 0；-1 表示未计算。
ll memo[MAXLEN][11];
int digit[MAXLEN]; // digit[i] 表示上限 n 从高到低第 i 位的数字
int len;           // 上限 n 的十进制位数

// 数位 DP（记忆化搜索）：从高位往低位逐位填数。
// pos：当前要填的位下标；last：上一位填的数字，-1 表示还没填过有效数字（仍在前导零阶段）；
// is_limit：前面已填的位是否都紧贴上限；is_num：是否已经填过有效数字。
// 返回从 pos 位起能得到的合法方案数，pos == len 时只有 is_num 为真才算一个正整数。
ll dfs(int pos, int last, bool is_limit, bool is_num) {
    if (pos == len) {
        return is_num ? 1 : 0;
    }

    // 只有不受上限约束的状态能复用；此时 last 与 is_num 的取值一一对应。
    if (!is_limit && memo[pos][last + 1] != -1) {
        return memo[pos][last + 1];
    }

    int up = is_limit ? digit[pos] : 9;
    ll res = 0;
    if (!is_num) {
        // 还处于前导零阶段：这一位可以继续空着，仍是前导零。
        res += dfs(pos + 1, -1, false, false);
        // 也可以在这一位填首个非零数字，作为这个数的最高位。
        for (int d = 1; d <= up; d++) {
            res += dfs(pos + 1, d, is_limit && d == up, true);
        }
    } else {
        // 已经有前缀数字：当前位必须与上一位相差至少 2。
        for (int d = 0; d <= up; d++) {
            if (abs(d - last) >= 2) {
                res += dfs(pos + 1, d, is_limit && d == up, true);
            }
        }
    }

    if (!is_limit) {
        memo[pos][last + 1] = res;
    }
    return res;
}

// 统计 [1, n] 内 Windy 数的个数。
ll count_windy(ll n) {
    if (n <= 0) {
        return 0;
    }

    ll tmp[MAXLEN]; // 先按低位到高位拆位，再翻转成高位到低位
    int l = 0;
    while (n > 0) {
        tmp[l] = n % 10;
        n /= 10;
        l++;
    }
    len = l;
    for (int i = 0; i < len; i++) {
        digit[i] = tmp[len - 1 - i];
    }

    // 只清理本次实际会用到的位置，last + 1 的取值范围是 0..10。
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <= 10; j++) {
            memo[i][j] = -1;
        }
    }

    return dfs(0, -1, true, false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll A, B;
    cin >> A >> B;

    // 区间计数可减：ans(A, B) = count(B) - count(A - 1)。
    cout << count_windy(B) - count_windy(A - 1) << endl;

    return 0;
}
