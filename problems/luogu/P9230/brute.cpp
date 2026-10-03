/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-03 11:23
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// A 题：直接枚举 1 ~ 100000000 的每个数，数位求和后比较前后两半，不做任何数学优化。
// B 题：把答题过程看成一次搜索，状态是（已答题数, 当前分数），
//       每层在这一题上做“答对 / 答错”的选择，遇到 70 分就把“此刻停止答题”计入答案。
// 它与 main.cpp 的状态定义完全不同（main 用的是“末尾连续答对数”），
// 因此是一份独立的校验实现；规模只够用来对拍和理解，不适合当作正解。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int ALL_Q = 30;            // B 题总题数
const int MAX_SCORE = 90;        // 分数只能是 10 的倍数，且 100 分时立即停止
const int WANT_SCORE = 70;       // 最终实际获得的 70 分
const int A_LIMIT = 100000000;   // A 题题面上界

int digit[16];                   // digit[1..len]：当前枚举到的数的各位数字

// A 题暴力：把 x 拆位，位数必须是偶数，且前后两半的数位和相等。
bool is_lucky(int x) {
    int len = 0;
    int y = x;
    while (y > 0) {
        len++;
        digit[len] = y % 10;
        y /= 10;
    }
    if (len % 2 != 0) {
        return false;
    }
    int half = len / 2;
    int front = 0;
    int back = 0;
    for (int i = len; i > half; i--) { // digit[len]..digit[half+1] 是高位那一半
        front += digit[i];
    }
    for (int i = half; i >= 1; i--) {  // digit[half]..digit[1] 是低位那一半
        back += digit[i];
    }
    return front == back;
}

ll solve_a_brute() {
    ll cnt = 0;
    for (int x = 1; x <= A_LIMIT; x++) {
        if (is_lucky(x)) {
            cnt++;
        }
    }
    return cnt;
}

ll memo[ALL_Q + 1][MAX_SCORE + 1];  // 记忆化：同一个（已答题数, 当前分数）只算一次
bool visited[ALL_Q + 1][MAX_SCORE + 1];

// 当前已经答了 t 题、手上分数是 score，返回还能产生多少种“以 70 分结束”的答题情况。
// 到达某个状态时分数一定小于 100，否则早就在 100 分处停止、不会继续答题。
ll dfs_answer(int t, int score) {
    if (visited[t][score]) {
        return memo[t][score];
    }
    visited[t][score] = true;

    ll res = 0;
    if (score == WANT_SCORE) {
        res += 1;                       // 此刻正好 70 分，小蓝可以选择在这里结束答题
    }
    if (t < ALL_Q) {
        res += dfs_answer(t + 1, 0);    // 这一题答错：分数直接归零
        if (score + 10 <= MAX_SCORE) {  // 这一题答对：拿到 100 分就必须停止，不能再往后展开
            res += dfs_answer(t + 1, score + 10);
        }
    }
    memo[t][score] = res;
    return res;
}

ll solve_b_brute() {
    memset(visited, 0, sizeof(visited));
    memset(memo, 0, sizeof(memo));
    return dfs_answer(0, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char pid;
    if (!(cin >> pid)) {
        return 0;
    }
    if (pid == 'A') {
        cout << solve_a_brute() << "\n";
    } else {
        cout << solve_b_brute() << "\n";
    }
    return 0;
}
