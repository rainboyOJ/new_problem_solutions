/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:13
 * update_at: 2026-10-06 11:13
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 9 + 5;

ll n;                  // 题目给出的 n，排列长度
ll path[MAXN];         // path[pos] 表示第 pos 个位置填的数字
bool used[MAXN];       // used[i] 表示数字 i 是否已经被选用

// dfs(pos)：这一层在为第 pos 个位置选择一个未使用的数字
void dfs(ll pos) {
    if (pos == n) { // 前 n 个位置全部填满，输出当前排列
        for (ll i = 0; i < n; i++) printf("%lld ", path[i]);
        printf("\n");
        return;
    }
    // 从小到大尝试每个数字，保证输出按字典序
    for (ll i = 1; i <= n; i++) {
        if (used[i]) continue;
        used[i] = true;
        path[pos] = i;
        dfs(pos + 1);
        used[i] = false; // 回溯恢复现场
    }
}

int main() {
    scanf("%lld", &n);
    dfs(0);
    return 0;
}
