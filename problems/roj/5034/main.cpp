/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:40
 * update_at: 2026-10-08 22:40
 */
// roj 5034《【例4.18】分解质因数》：从小到大试除 + 循环后补打剩余商（必为素数）
//
// 题意：输入正整数 n（2 <= n <= 20000），输出 "n=p1*p2*...*pk"，
//   质因数（含重复）按从小到大排列。样例 36 -> "36=2*2*3*3"。
//
// 做法：i 从 2 起枚举，i*i <= n 时把 i 除尽（重复因子逐个输出）。
//   从小到大枚举保证命中的 i 一定是质数：若 i 是合数，它的更小质因子
//   早已被除尽，此时 n 不可能还被 i 整除。
//
// 为什么循环退出后「剩余商 c > 1 ⇒ c 是素数」：
//   若 c 是合数，则 c 有质因子 q 满足 q <= sqrt(c)。循环退出条件是 i*i > c，
//   而 i 是从 2 逐个递增到该条件的，所以 q 早就被枚举过；又因 q | c 且 q | 原 n，
//   枚举到 q 时内层 while 会把 n 中所有因子 q 除尽，c 里就不可能再留下 q，矛盾。
//   故 c 只能是 1 或素数，c > 1 时必须再输出一次，否则会漏掉最后一个质因子。
//
// 注意（易错）：判断「要不要补打」不能写成「最大质因数 > sqrt(n)」。
//   例如 n = 19950 = 2*3*5*5*7*19，最大质因数 19 < sqrt(19950) ≈ 141.2，
//   但把 2,3,5,7 除尽后剩余商正是 19 > 1，必须补打。
//   准确的判据是：剩余商 > 1 当且仅当最大质因数的指数恰为 1。
//   题面只要求「质因数必须由小到大」，这层判断对素数输入（如 2、19997）同样正确。

#include <iostream>

using namespace std;

typedef long long ll;

// 从小到大试除分解 n，按升序输出 "n=p1*p2*...*pk"。
void solve() {
    ll n;
    if (!(cin >> n)) return; // 空输入：不输出任何东西

    cout << n << "=";
    bool first = true; // 还没输出过任何因子，用来决定乘号的位置

    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) { // 除尽因子 i，重复因子按出现次数逐个输出
            if (!first) cout << "*";
            first = false;
            cout << i;
            n /= i;
        }
    }

    if (n > 1) { // 剩余商必为素数，补打最后一个质因子
        if (!first) cout << "*";
        cout << n;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
