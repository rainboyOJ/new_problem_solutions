/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:32
 * update_at: 2026-10-05 05:32
 */

#include <cstdio>

typedef long long ll;

ll n;            // 盘子数目
char src, dst, aux; // 三个杆子的编号：src 源杆，dst 目标杆，aux 辅助杆

// 把 1~num 号盘从 from 杆借助 mid 杆移到 to 杆（mid 为辅助杆）
void hanoi(ll num, char from, char mid, char to) {
    if (num == 0) return;      // 没有盘子可移，递归结束
    hanoi(num - 1, from, to, mid);   // 先把上面 num-1 个盘从 from 借助 to 移到 mid
    printf("%c->%lld->%c\n", from, num, to); // 再把最大的 num 号盘直接移到 to
    hanoi(num - 1, mid, from, to);   // 最后把 num-1 个盘从 mid 借助 from 移到 to
}

int main() {
    scanf("%lld %c %c %c", &n, &src, &dst, &aux);
    hanoi(n, src, aux, dst);
    return 0;
}
