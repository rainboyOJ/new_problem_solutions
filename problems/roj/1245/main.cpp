/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:55
 * update_at: 2026-10-05 06:55
 */

#include <cstdio>
#include <set>
#include <algorithm>
typedef long long ll;

const int MAXN = 100005;

ll a[MAXN]; // a[i]：第 i 个输入的数
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    // 值域是整个 int 范围，不能开桶；用 set 去重并自动保持升序
    std::set<ll> s(a + 1, a + n + 1);

    // 输出 set 里从小到大的每个数，相邻之间一个空格
    bool first = true;
    for (std::set<ll>::iterator it = s.begin(); it != s.end(); it++) {
        if (!first) printf(" ");
        printf("%lld", *it);
        first = false;
    }
    printf("\n");
    return 0;
}
