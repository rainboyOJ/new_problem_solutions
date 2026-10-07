/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:31
 * update_at: 2026-10-06 12:31
 */
/* roj 3513 [NOIP2002-普及] 选数 */
/* 递增下标 DFS 枚举所有选 k 个数的组合，求和并判断是否为素数。 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 25;

int n, k;
ll a[MAXN]; // 输入数组，单个 xi ≤ 5e6
ll ans;     // 和为素数的组合个数，最多 C(20,10) < 2e5 但用 ll 更省心

// 判断 x 是否为素数：只需试除到 sqrt(x)，x ≤ 1e8 故循环次数很小
bool is_prime(ll x) {
    if (x < 2) return false;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

// dfs(dep, last, sum)：正在选第 dep 个数（从 1 开始），
// 上一个选中的下标是 last，当前已选数字的和是 sum
void dfs(int dep, int last, ll sum) {
    if (dep == k + 1) {
        // 已经选满 k 个数，判断和是否为素数
        if (is_prime(sum)) ans++;
        return;
    }

    // 下标递增保证组合不重不漏：第 dep 个数只能从 last+1 往后选。
    // 上界剪枝：之后还要选 k - dep 个数，下标 i 最多到 n - (k - dep)
    for (int i = last + 1; i <= n - (k - dep); i++) {
        dfs(dep + 1, i, sum + a[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    dfs(1, 0, 0); // 正在选第 1 个数，上一个下标是 0，当前和为 0
    cout << ans << "\n";
    return 0;
}
