/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 17:33
 * update_at: 2026-10-02 21:52
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// main.cpp：n <= 50 直接查打表数组 tables[]，n > 50 用 n = 7k + r 的规律输出。
// tables[] 由 brute-dfs-clip.cpp（DFS 暴力打表）生成，见题解「打表」部分。

// tables[i]：恰好用 i 根木棍拼出的最小正整数（i = 0 不用，n = 1 无解记为 -1）
// 由 brute-dfs-clip.cpp 的 DFS 暴力打表得到，范围 n = 1..50
ll tables[] = {
    -1,      // n = 0（不用）
    -1,      // n = 1：无解
    1, 7, 4, 2, 6, 8, 10, 18, 22, 20,
    28, 68, 88, 108, 188, 200, 208, 288, 688, 888,
    1088, 1888, 2008, 2088, 2888, 6888, 8888, 10888, 18888, 20088,
    20888, 28888, 68888, 88888, 108888, 188888, 200888, 208888, 288888, 688888,
    888888, 1088888, 1888888, 2008888, 2088888, 2888888, 6888888, 8888888, 10888888,
}; // tables[50] = 10888888

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

        if (n <= 50) { // 小数据：直接查打表数组
            cout << tables[n] << '\n';
        } else { // 大数据：按规律直接输出
            print_pattern(n);
            cout << '\n';
        }
    }

    return 0;
}
