/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:32
 * update_at: 2026-10-05 05:32
 */

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

// 把 x 展开成约定的 0、2 表示，例如 5 -> 2(2)+2(0)；x=0 返回空串，方便拼接余项
string expand(ll x) {
    if (x == 0) {
        return "";
    }
    ll top = 0; // top 是 x 的最高二进制位下标，即最大那个 2 的幂的指数
    while ((1LL << (top + 1)) <= x) {
        top++;
    }
    string head; // 单个 2^top 的写法
    if (top == 0) {
        head = "2(0)"; // 2^0 必须显式写成 2(0)
    } else if (top == 1) {
        head = "2"; // 2^1 约定直接写 2
    } else {
        head = "2(" + expand(top) + ")"; // 指数自身继续展开
    }
    string tail = expand(x - (1LL << top)); // 去掉最高位后的剩余部分
    if (tail != "") {
        return head + "+" + tail;
    }
    return head;
}

int main() {
    ll n;
    cin >> n;
    cout << expand(n) << endl;
    return 0;
}
