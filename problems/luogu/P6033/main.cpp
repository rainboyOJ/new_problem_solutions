/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:52
 * update_at: 2026-11-11 00:52
 */
#include <cstdio>
#include <iostream>

using namespace std;

const int MAXA = 100005;
const int MAXN = 10000005;

int bucket[MAXA];
long long q2[MAXN];

// 高效快读，针对 10^7 大规模输入
inline int read_int() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x;
}

int main() {
    int n = read_int();
    if (n <= 0) return 0;

    for (int i = 0; i < n; ++i) {
        int val = read_int();
        bucket[val]++;
    }

    int cur_val = 1;
    int h2 = 0, t2 = -1;

    // 从原桶序列和新队列 q2 中提取全局最小值的辅助 lambda/函数
    auto get_min = [&]() -> long long {
        // 找到桶中下一个有剩余权值的数值
        while (cur_val < MAXA && bucket[cur_val] == 0) {
            cur_val++;
        }

        bool has_bucket = (cur_val < MAXA);
        bool has_q2 = (h2 <= t2);

        if (has_bucket && has_q2) {
            if (cur_val <= q2[h2]) {
                bucket[cur_val]--;
                return cur_val;
            } else {
                return q2[h2++];
            }
        } else if (has_bucket) {
            bucket[cur_val]--;
            return cur_val;
        } else {
            return q2[h2++];
        }
    };

    long long total_cost = 0;

    // 共进行 n - 1 次合并
    for (int i = 1; i < n; ++i) {
        long long u = get_min();
        long long v = get_min();
        long long sum = u + v;
        total_cost += sum;
        q2[++t2] = sum;
    }

    cout << total_cost << "\n";

    return 0;
}
