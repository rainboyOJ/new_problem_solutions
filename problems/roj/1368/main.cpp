/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:13
 * update_at: 2026-10-12 14:55
 */
// main.cpp：二叉树顺序存储判对称——位置 k 的孩子在 2k+1/2k+2，逐对兄弟判同空或同非空。
//
// 这题的树就存在一个字符串里，不需要再建结点结构：s[k] 是位置 k 的结点字母，
// '#' 表示空位。把串补到 2n 长后，相邻位置 (1,2)、(3,4)、... 恰好是一对对兄弟，
// 每对兄弟"同空或同非空"就等价于"每个结点要么没孩子、要么孩子齐全"，
// 正是题目给的对称定义。

#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;

const int maxn = 100005; // 题面没给串长上限，按 1e5 留余量（串中一位对应一个结点或空位）

char s[maxn * 2]; // 顺序存储串，s[k] 是位置 k 的结点字母，'#' 是空位；末尾会补 '#' 到 2n 长
ll n;             // 原串长度（补 '#' 之前）

// 末尾省略不写的孩子补成空位。补出来的位置只会增加"同空"的兄弟对，不影响判定
void pad_tail() {
    ll len = strlen(s);
    while (len < 2 * n) {
        s[len] = '#';
        len++;
    }
    s[len] = '\0'; // 补完封口，后面继续按 C 字符串遍历
}

// 逐对兄弟检查：(2k+1, 2k+2) 是结点 k 的两个孩子。
// 一对里出现"一个空、一个非空"，就说明有结点只有一个孩子，树不对称
bool is_symmetric() {
    ll len = strlen(s);
    for (ll i = 1; i + 1 < len; i += 2) {
        bool left_empty = (s[i] == '#');
        bool right_empty = (s[i + 1] == '#');
        if (left_empty != right_empty) {
            return false;
        }
    }
    return true;
}

void solve() {
    cin >> s;
    n = strlen(s);
    pad_tail();
    if (is_symmetric()) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
