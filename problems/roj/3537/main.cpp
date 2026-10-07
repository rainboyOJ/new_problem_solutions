/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:26
 * update_at: 2026-10-06 13:27
 */

#include <cstdio>

typedef long long ll;

const int MAX_LENGTH = 10000; // 马路长度上限

char removed[MAX_LENGTH + 1]; // removed[i] 表示整数点 i 上的树已被移走（只有 0/1，用 char 控制内存）

int main() {
    ll length, region_count;
    scanf("%lld %lld", &length, &region_count);

    for (int region = 1; region <= region_count; region++) {
        ll start, end;
        scanf("%lld %lld", &start, &end);
        // 端点顺序不保证，先规范化成 [left_end, right_end]
        ll left_end = start;
        ll right_end = end;
        if (left_end > right_end) {
            left_end = end;
            right_end = start;
        }
        // 区间内的每个整数点（含两端端点）打删除标记，重复标记是幂等的
        for (ll point = left_end; point <= right_end; point++) {
            removed[point] = 1;
        }
    }

    ll remain = 0; // 一次都没被覆盖的树
    for (ll point = 0; point <= length; point++) {
        if (removed[point] == 0) {
            remain++;
        }
    }
    printf("%lld\n", remain);
    return 0;
}
