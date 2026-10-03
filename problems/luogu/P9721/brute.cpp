/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:30
 */
// brute.cpp：暴力对拍解。
//
// 思路（把每个位置和其余所有位置都比一遍）：
//   1. 先按定义求出所有 inv(l,r)，也就是交互器对所有可能询问的回答；
//   2. 再用同一个恒等式
//        [p_l > p_r] = inv(l,r) ^ inv(l+1,r) ^ inv(l,r-1) ^ inv(l+1,r-1)
//      得到每一对位置的大小关系；
//   3. p_i 就是比它大的元素个数 bigger[i]，故 p_i = n - bigger[i]。
//
// 正确但很慢：一共要处理 Θ(n^2) 对位置，换算成真实的询问次数也是 Θ(n^2)，
// 在 n=2000 时达到 10^6 级别，远超题目的 4*10^4 次上限。
// 本地对拍时输入是 “n + 隐藏排列”，排列只用来扮演交互器。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;

int n;
static unsigned char invtab[maxn][maxn]; // invtab[l][r] = p_l..p_r 内逆序对个数的奇偶性
static int perm_in[maxn];
int bigger[maxn];                        // bigger[i] = 比 p_i 大的元素个数

// 按定义算出所有区间的逆序对奇偶性：固定 r，l 递减，cnt 维护 [l, r-1] 中比 p_r 大的个数。
void build_inv_table() {
    for (int r = 1; r <= n; r++) {
        int cnt = 0;
        for (int l = r - 1; l >= 1; l--) {
            if (perm_in[l] > perm_in[r]) {
                cnt++;
            }
            invtab[l][r] = (unsigned char)(invtab[l][r - 1] ^ (cnt & 1));
        }
    }
}

void solve() {
    // 一次“询问”：直接查预先算好的表。
    for (int l = 1; l <= n; l++) {
        for (int r = l + 1; r <= n; r++) {
            // 用恒等式还原大小关系，inv 中越界的部分按 0 处理。
            int cmp = invtab[l][r] ^ invtab[l + 1][r] ^ invtab[l][r - 1] ^ invtab[l + 1][r - 1];
            if (cmp) {
                bigger[r]++; // p_l > p_r
            } else {
                bigger[l]++; // p_r > p_l
            }
        }
    }

    cout << "!";
    for (int i = 1; i <= n; i++) {
        cout << " " << n - bigger[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> perm_in[i];
    }
    build_inv_table();
    solve();

    return 0;
}
