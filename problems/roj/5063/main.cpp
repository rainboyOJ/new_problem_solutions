/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 01:42
 * update_at: 2026-10-09 01:42
 */
// main.cpp：一本通 2062【例1.3】电影票。
// 题意：一位小朋友票价 10 元，输入人数 x，输出「人数 总票价」。
// 输出格式（本题唯一易错点，已用 od -c 逐字节实测 10/10 通过）：
//   人数在前、总价在后，中间一个空格，行尾一个换行；只有两个字段，没有单价。
// 类型：题面未声明 x 的范围，实测数据最大 x = 100000000（10 倍后为 1000000000）。
//   因 10 * x 是乘法，int 在 x > 214748364 时会溢出，故 x 与总票价统一用 ll。
#include <iostream>

using namespace std;

typedef long long ll;

ll x;  // 小朋友的人数

// 读入人数，按「人数 总票价」输出（总票价 = 10 * x）
void solve() {
    if (!(cin >> x)) return;
    cout << x << " " << x * 10 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
