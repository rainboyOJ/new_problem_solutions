/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:18
 * update_at: 2026-10-05 05:18
 */
// main.cpp：roj/1199 全排列，n<=6。
// 输入已按字母升序排好，用 STL 的 next_permutation 按字典序枚举全部排列。

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;

char s[7];          // 输入串，长度 1..6，s[n] 留给 '\0'
int n;              // 实际长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入一行小写字母串
    string t;
    if (!(cin >> t)) return 0;
    n = (int)t.size();
    for (int i = 0; i < n; i++) s[i] = t[i];
    s[n] = '\0';

    // 输入已升序，先输出一次当前排列，再反复调用 next_permutation
    cout << s << '\n';
    while (next_permutation(s, s + n)) {
        cout << s << '\n';
    }

    return 0;
}