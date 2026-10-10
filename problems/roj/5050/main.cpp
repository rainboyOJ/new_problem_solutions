/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 00:06
 * update_at: 2026-10-09 00:06
 */
// main.cpp：读入 n 个国家名（n ≤ 20，名字长度 ≤ 20），按字典序升序逐行输出。
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

const int MAXN = 25; // 题面 n ≤ 20，留出余量

string name[MAXN]; // name[1..n] 存国家名，下标从 1 开始与题面一致

// 读入国名、按字典序排序后逐行输出。
// std::string 的 < 是逐字符比较编码值（ASCII），即题面要求的"字母顺序"，
// 与数据实测的区分大小写纯字典序一致；也天然支持"短前缀排在前面"。
void solve() {
    ll n;
    cin >> n;
    for (ll i = 1; i <= n; ++i) {
        cin >> name[i]; // 国名不含空格，直接按空白分隔读入即可
    }
    sort(name + 1, name + n + 1);
    for (ll i = 1; i <= n; ++i) {
        cout << name[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
