/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:30
 * update_at: 2026-10-09 22:55
 */
// main.cpp：判断 q 是不是 s1 的子序列（q 中字符的相对位置要和 s1 中一致）。
// 双指针顺序扫描：i 扫 s1，j 扫 q；s1[i] 与 q[j] 相等就把 j 前推一格，i 每轮都前推。
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

string s1, q;

void solve() {
    if (!(cin >> s1 >> q)) return; // 没有读满两个字符串就直接结束

    ll i = 0, j = 0; // i 扫 s1，j 扫 q
    ll n = s1.size();
    ll m = q.size();

    while (i < n && j < m) {
        if (s1[i] == q[j]) { // q 的当前字符在 s1 中按序匹配上了
            j++;
        }
        i++;
    }

    if (j == m) { // q 的字符全部按原相对位置匹配完成
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
