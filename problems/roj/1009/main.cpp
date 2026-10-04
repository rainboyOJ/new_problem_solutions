/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:22
 * update_at: 2026-10-04 22:22
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll dividend, divisor; // 被除数 a 与除数 b（b 非零）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> dividend >> divisor;

    // C++ 的 / 向零截断、% 的符号随被除数，正是本题采用的带余除法语义：
    // 商与余数满足 a = q*b + r 且 |r| < |b|，直接输出即可，无需特殊处理。
    cout << dividend / divisor << " " << dividend % divisor << "\n";

    return 0;
}
