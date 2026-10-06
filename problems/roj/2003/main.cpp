// main.cpp：把环接成两倍直线，枚举断点，两端各自查"同色连续段"表贪心收集。
/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:19
 * update_at: 2026-10-06 09:19
 */

#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 355;       // n <= 350，两倍串长 <= 700
const int MAX2 = 2 * MAXN;

int n;                      // 项链珠子数
string r;                   // 项链接成两倍后的直线串，下标 0 ~ 2n-1
int next_nonwhite[MAX2];    // next_nonwhite[i]：i 起向右第一颗非白珠位置，没有则为 -1
int prev_nonwhite[MAX2];    // prev_nonwhite[i]：i 起向左第一颗非白珠位置，没有则为 -1
int red_start[MAX2], red_end[MAX2];     // "可当红"（本色红或白）连续段的首/尾下标
int blue_start[MAX2], blue_end[MAX2];   // "可当蓝"（本色蓝或白）连续段的首/尾下标

// 对布尔数组 c 求极长连续段两端：start[i]/end[i] 是含 i 的段首/段尾，c[i]=0 时为 -1
void run_edge(bool c[], int start[], int ende[]) {
    for (int i = 0; i < 2 * n; i++) {
        if (!c[i])
            start[i] = -1;
        else if (i && c[i - 1])
            start[i] = start[i - 1];    // 与左邻同段，继承段首
        else
            start[i] = i;               // 新段从这里起头
    }
    for (int i = 2 * n - 1; i >= 0; i--) {
        if (!c[i])
            ende[i] = -1;
        else if (i + 1 < 2 * n && c[i + 1])
            ende[i] = ende[i + 1];      // 与右邻同段，继承段尾
        else
            ende[i] = i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> n >> s;
    r = s + s;                  // 项链是环：接成两倍当成直线扫，断点 k 对应起点 k

    // 顺 / 逆两个方向上第一颗非白珠的位置
    next_nonwhite[2 * n] = -1;
    for (int i = 2 * n - 1; i >= 0; i--)
        next_nonwhite[i] = (r[i] != 'w') ? i : next_nonwhite[i + 1];
    for (int i = 0; i < 2 * n; i++)
        // i == 0 时左边没有珠子，直接记 -1
        prev_nonwhite[i] = (r[i] != 'w') ? i : (i ? prev_nonwhite[i - 1] : -1);

    // 白珠两色都算，所以红、蓝各建一套连续段端点表
    bool as_red[MAX2], as_blue[MAX2];   // as_red[i]：第 i 颗可当红；as_blue 同理
    for (int i = 0; i < 2 * n; i++) {
        as_red[i] = (r[i] != 'b');
        as_blue[i] = (r[i] != 'r');
    }
    run_edge(as_red, red_start, red_end);
    run_edge(as_blue, blue_start, blue_end);

    int best = 0;
    for (int k = 0; k < n; k++) {
        // 顺时针：从 k 向右，第一颗非白珠锁定颜色，吃到该色段的末尾
        int first = (r[k] != 'w') ? k : next_nonwhite[k];
        int left;
        if (first == -1) {      // 整条项链全是白珠
            best = n;
            break;
        }
        if (r[first] == 'r')
            left = min(red_end[first] - k + 1, n);
        else
            left = min(blue_end[first] - k + 1, n);

        // 逆时针：从 k+n-1 向左收，颗数不超过 budget（与顺时针不重叠）
        int budget = n - left;
        int back = prev_nonwhite[k + n - 1];
        int right;
        if (back == -1)
            right = budget;     // 后半截全是白珠，budget 全收
        else {
            // 该珠锁定逆时针的颜色，吃到该色段的开头
            int seg_start = (r[back] == 'r') ? red_start[back] : blue_start[back];
            right = min(k + n - seg_start, budget);
        }
        best = max(best, left + right);
    }

    cout << best << endl;
    return 0;
}
