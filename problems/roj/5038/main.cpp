/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:46
 * update_at: 2026-10-08 22:46
 */
#include <iostream>

using namespace std;

typedef long long ll;

ll n; // 房间数，题面给出 2 <= n <= 1000

// 第 k 扇门被"相反处理"的次数 = k 的正约数个数 d(k)（第 1 个服务员开门等价于对每扇门翻转一次），
// d(k) 为奇数 <=> k 是完全平方数。故答案就是不超过 n 的全部完全平方数，由小到大输出。
void solve() {
    bool first = true;                // 是否尚未输出任何元素，用来控制分隔符
    for (ll i = 1; i * i <= n; i++) { // 枚举 1^2, 2^2, ... 直到不超过 n，天然升序
        if (!first) cout << " ";      // 元素之间恰一个空格，行首行末都不留空格
        cout << i * i;
        first = false;
    }
    cout << "\n"; // 题面要求一行，末尾补单个换行
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0; // 无输入时直接退出

    solve();

    return 0;
}
