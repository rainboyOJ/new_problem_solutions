/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:53
 * update_at: 2026-10-06 10:53
 */
#include <cstdio>
using namespace std;

typedef long long ll;

int n;
int chosen[20]; // chosen[i] = 1 表示整数 i 已被选中

// 递归枚举第 u 个数选或不选
void dfs(int u) {
    if (u > n) {
        // 叶子：按升序输出已选中的数
        bool first = true;
        for (int i = 1; i <= n; ++i) {
            if (chosen[i]) {
                if (!first) printf(" ");
                printf("%d", i);
                first = false;
            }
        }
        printf("\n");
        return;
    }
    // 不选 u
    chosen[u] = 0;
    dfs(u + 1);
    // 选 u
    chosen[u] = 1;
    dfs(u + 1);
}

int main() {
    scanf("%d", &n);
    dfs(1);
    return 0;
}
