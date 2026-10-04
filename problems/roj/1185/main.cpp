/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:41
 * update_at: 2026-10-05 04:41
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<string> words;      // 自动去重，并按 ASCII 字典序排序
    string w;
    while (cin >> w) {      // 按任意空白切分，可处理 1 个或多个空格
        words.insert(w);
    }

    for (auto it = words.begin(); it != words.end(); ++it) {
        cout << *it << '\n';
    }
    return 0;
}
