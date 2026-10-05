/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:11
 * update_at: 2026-10-06 02:11
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 25;

string a[MAXN]; // 每个数字保留为字符串，方便拼接比较

// 比较器：a 放在 b 前面拼出的数更大时返回 true，用于按最大拼接排序
bool cmp(const string &a, const string &b) {
    return a + b > b + a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a, a + n, cmp); // 按拼接后的字典序降序排列

    for (int i = 0; i < n; ++i) {
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
