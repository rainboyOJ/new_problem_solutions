/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:59
 * update_at: 2026-10-08 06:59
 *
 * 1994《音乐会》：n 条闭区间演奏记录（5 种乐器）+ m 次单点询问，
 * 每种乐器一个差分数组，区间加 1 后前缀和还原，单点询问 O(1) 拼出 PVCDB。
 * 时间折成秒：t = 3600*hh + 60*mm + ss，由 0<=hh<=9 知 t 最大 35999。
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXT = 36000;     // 秒 0..35999，差分还要用 t = 36000 这一格
const int MAXN = 20005;

int diff[5][MAXT + 5];      // 每种乐器的差分数组，下标 0..36000
int state[5][MAXT + 5];     // 前缀和还原后：该秒该乐器是否在演奏（>0 即演奏）
const char* name = "PVCDB"; // 输出优先级顺序

/**
 * hh:mm:ss 折成绝对秒。
 */
int to_sec(int hh, int mm, int ss) {
    return hh * 3600 + mm * 60 + ss;
}

/**
 * 读入一个 hh:mm:ss 时间串并折成秒，冒号交给 scanf 吞掉。
 */
int read_time() {
    int hh, mm, ss;
    scanf("%d:%d:%d", &hh, &mm, &ss);
    return to_sec(hh, mm, ss);
}

/**
 * 乐器字母映射成 0..4 的下标，顺序与 name 一致。
 */
int to_id(char c) {
    for (int i = 0; i < 5; ++i) {
        if (name[i] == c) return i;
    }
    return -1;
}

int main() {
    ll n = 0, m = 0;
    scanf("%lld", &n);

    char op[8];
    for (ll i = 0; i < n; ++i) {
        int l = read_time();
        int r = read_time();
        scanf("%s", op);
        int id = to_id(op[0]);
        if (id < 0) continue;
        // 闭区间 [l, r]：l 处 +1，r+1 处 -1；r 最大 35999，故差分开到 36000。
        diff[id][l] += 1;
        diff[id][r + 1] -= 1;
    }

    // 对每种乐器求前缀和，得到每个秒时刻的覆盖层数
    for (int id = 0; id < 5; ++id) {
        int cur = 0;
        for (int t = 0; t <= MAXT; ++t) {
            cur += diff[id][t];
            state[id][t] = cur;
        }
    }

    scanf("%lld", &m);
    for (ll i = 0; i < m; ++i) {
        int t = read_time();
        int cnt = 0;                        // 本时刻演奏中的乐器数
        for (int id = 0; id < 5; ++id) {
            if (state[id][t] > 0) {
                putchar(name[id]);
                ++cnt;
            }
        }
        if (cnt == 0) printf("None");        // 一个乐器都没有
        putchar('\n');
    }
    return 0;
}
