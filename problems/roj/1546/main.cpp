/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:41
 * update_at: 2026-10-06 00:41
 */
#include <cstdio>

const int MAXN = 2000005;
const int MAXK = 10005;

int col[MAXN];     // col[i] 表示第 i 家客栈的色调
int covered[MAXK]; // covered[c]：阈值 g 左侧（位置 <= g）色调为 c 的客栈数，即可作合法左端点的数量

int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);

    int g = 0;    // g：目前为止最靠右的便宜咖啡店位置（消费 <= p），没有则为 0
    int last = 0; // last：已经计入 covered 的最右位置，随 g 单调推进
    long long ans = 0;

    for (int j = 1; j <= n; j++) {
        int b;
        scanf("%d %d", &col[j], &b);

        if (b <= p) g = j;              // 出现便宜咖啡店，阈值推进到当前位置
        int upto = (g < j) ? g : j - 1; // 只能把位置在 j 之前的客栈计入 covered
        while (last < upto) {
            last++;
            covered[col[last]]++;
        }

        // 固定右端点 j：合法的左端点恰为位置 <= g 的同色客栈
        ans += covered[col[j]];
    }

    printf("%lld\n", ans);
    return 0;
}
