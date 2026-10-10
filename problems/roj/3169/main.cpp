/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 平分大理石：多重背包可行性，位图整体左移或
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

int cnt[6];                        // cnt[v]：价值 v+1 的宝石块数
vector<unsigned long long> reach;  // reach 的第 s 位 = 1 表示价值 s 可达

// 往可达集合里再加一块价值 bits 的宝石（整体左移 bits 位）
void add_piece(int bits, int limit) {
    int words = limit / 64 + 1;
    int ws = bits / 64, bs = bits % 64;
    for (int i = words - 1; i >= 0; i--) {
        unsigned long long x = reach[i];
        if (!x) {
            continue;
        }
        int lo = i + ws;
        if (lo < words) {
            reach[lo] |= x << bs;
        }
        if (bs && lo + 1 < words) {
            reach[lo + 1] |= x >> (64 - bs);
        }
    }
}

int main() {
    int printed = 0;
    while (true) {
        bool eof = false;
        for (int i = 0; i < 6; i++) {
            if (scanf("%d", &cnt[i]) != 1) {
                eof = true;
                break;
            }
        }
        if (eof) {
            break;
        }
        bool all_zero = true;
        for (int i = 0; i < 6; i++) {
            if (cnt[i]) {
                all_zero = false;
            }
        }
        if (all_zero) {
            break; // 全 0 行是结束标志
        }

        ll total = 0;
        for (int v = 0; v < 6; v++) {
            total += (ll)(v + 1) * cnt[v];
        }
        bool can = false;
        if (total % 2 == 0) { // 总价值为奇数，无法平分
            int half = (int)(total / 2);
            reach.assign(half / 64 + 1, 0);
            reach[0] = 1;
            for (int v = 0; v < 6; v++) {
                for (int t = 0; t < cnt[v]; t++) {
                    add_piece(v + 1, half);
                }
            }
            can = (reach[half >> 6] >> (half & 63)) & 1;
        }
        printf("%s\n", can ? "Can" : "Can't");
        printed++;
    }
    if (printed == 0) {
        printf("\n"); // 复刻 py 的 print('\n'.join([])) 行为
    }
    return 0;
}
