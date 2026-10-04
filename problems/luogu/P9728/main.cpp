/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 13:15
 *
 * P9728 [EC Final 2022] Dining Professors
 * 正解：每个位置放一道不辣菜，对总满意度的增益 = (1-b[i-1])+(1-b[i])+(1-b[i+1]);
 *       辣菜放到任何位置都不贡献，因此把 n-a 道不辣菜放到增益最大的 n-a 个位置。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int maxn = 1e5 + 5;

int n;   // 教授人数 = 位置数
int a;   // 辣菜数量
int b[maxn]; // b[i]=1:教授 i 能吃辣; b[i]=0:教授 i 不能吃辣
int c[maxn]; // c[p]:在位置 p 放一道不辣菜带来的满意度增益

void read_data() {
    cin >> n >> a;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    read_data();

    // 能吃辣的教授：无论摆什么菜都是 3 道菜可吃，先把这部分作为底数
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if (b[i] == 1) {
            ans += 3;
        }
    }

    // 对不能吃辣的教授，只有不辣菜才算满意
    // 位置 p 摆在教授 p-1、p、p+1 面前，所以一道不辣菜影响这三位教授
    for (int p = 0; p < n; ++p) {
        int l = (p - 1 + n) % n; // 左边教授
        int r = (p + 1) % n;     // 右边教授
        c[p] = (1 - b[l]) + (1 - b[p]) + (1 - b[r]);
    }

    // 一共要选 n-a 个位置放不辣菜，贪心选增益最大的那些
    sort(c, c + n, greater<int>());
    for (int k = 0; k < n - a; ++k) {
        ans += c[k];
    }

    cout << ans << "\n";
    return 0;
}
