/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:00
 * update_at: 2026-10-05 12:00
 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1000005;

int n; // 车站数

ll cw[MAXN];  // 顺时针差额 cw[i] = p_i - d_i，下标 1..n
ll ccw[MAXN]; // 逆时针差额 b_i = p_i - d_{i-1}，倒序存放：ccw[n+1-i] = b_i
ll wrap_min[MAXN]; // wrap_min[i] = 差额序列前 i 项的前缀最小值
char ok_cw[MAXN];  // ok_cw[i] = 从第 i 站顺时针能否走通
char ok_ccw[MAXN]; // ok_ccw[k] = 倒序差额序列从下标 k 出发能否走通

// 环形差额序列 gain[1..n]：判断以每个位置为起点顺推一圈，累计值是否始终非负。
// 起点 i 的整圈前缀按环的衔接点拆成两段：
//   不绕回段 gain[i..n]，其前缀最小值 tail 从右往左滚动；
//   绕回段 gain[1..i-1]，其前缀最小值是 wrap_min[i-1]，前面还要先补余量 suffix。
void check_each_start(ll gain[], char ok[]) {
    ll run = 0;
    for (int i = 1; i <= n; i++) {
        run += gain[i];
        bool first = (i == 1);
        wrap_min[i] = first ? run : min(run, wrap_min[i - 1]);
    }

    ll tail = 0;   // 不绕回段的前缀最小值，初值 0 使首项算出 min(x, x+0) = x
    ll suffix = 0; // 绕回段要接着用的余量 gain[i..n] 之和
    for (int i = n; i >= 1; i--) {
        ll x = gain[i];
        tail = min(x, x + tail);
        suffix += x;
        ll wrap = (i == 1) ? 0 : wrap_min[i - 1];
        ok[i] = (min(tail, suffix + wrap) >= 0) ? 1 : 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    ll p_first = 0; // 第 1 站的存油，等读到最后一站的出边 d_n 后补 b_1
    ll prev_d = 0;  // 上一站的出边 d_{i-1}
    for (int i = 1; i <= n; i++) {
        ll p, d;
        cin >> p >> d;
        cw[i] = p - d;

        int k = n + 1 - i; // 第 i 站的逆时针差额放到倒序下标
        if (i == 1) {
            p_first = p; // b_1 = p_1 - d_n，d_n 要等最后一站读完
        } else {
            ccw[k] = p - prev_d; // 逆时针出边是上一站到本站的距离
        }
        prev_d = d;
    }
    ccw[n] = p_first - prev_d;

    check_each_start(cw, ok_cw);
    check_each_start(ccw, ok_ccw);

    for (int i = 1; i <= n; i++) {
        // 原第 i 站逆时针可行 = 倒序数组从下标 n+1-i 出发顺推一圈可行
        int k = n + 1 - i;
        if (ok_cw[i] || ok_ccw[k]) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
    }
    return 0;
}
