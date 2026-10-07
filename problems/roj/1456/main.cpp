/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:12
 * update_at: 2026-10-06 00:12
 */
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

typedef long long ll;

unordered_set<string> book_set; // 存储已添加的图书名称
int n;
string op, s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    string leftover;
    getline(cin, leftover); // 吃掉 n 后面的换行

    for (int i = 1; i <= n; i++) {
        cin >> op;
        getline(cin, s);
        // 去掉 op 与书名之间的那个空格
        if (!s.empty() && s[0] == ' ') {
            s.erase(0, 1);
        }

        if (op == "add") {
            book_set.insert(s);
        } else if (op == "find") {
            if (book_set.count(s)) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }

    return 0;
}
