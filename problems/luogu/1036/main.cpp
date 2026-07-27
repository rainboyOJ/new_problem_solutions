/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1036 [NOIP 2002 普及组] 选数 */
/* DFS 枚举选 k 个数的所有组合，求和并判断是否为素数。 */

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, k;
int a[MAXN];       // 输入数组
int choose[MAXN];  // choose[i] = 1 表示选了第 i 个数
int ans;

// 判断 x 是否为素数
bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

// dfs(dep, cnt) 表示处理到第 dep 个数，已经选了 cnt 个
void dfs(int dep, int cnt) {
    if (dep == n + 1) {
        if (cnt == k) {
            int sum = 0;
            for (int i = 1; i <= n; i++) {
                if (choose[i]) sum += a[i];
            }
            if (is_prime(sum)) ans++;
        }
        return;
    }

    // 剪枝：剩余的数全选也不够 k 个
    if (cnt + (n - dep + 1) < k) return;

    // 不选第 dep 个数
    choose[dep] = 0;
    dfs(dep + 1, cnt);

    // 选第 dep 个数
    choose[dep] = 1;
    dfs(dep + 1, cnt + 1);
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    dfs(1, 0); // 从第 1 个数开始，已选 0 个
    cout << ans << "\n";
    return 0;
}
