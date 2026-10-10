/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 00:06
 * update_at: 2026-10-09 00:14
 */
// 一本通 2049《【例5.19】字符串判等》（ROJ 5051）
// 题意：两行，每行只由大小写字母和空格组成；忽略大小写、忽略空格后相等输出 YES，否则 NO。
// 考点：某一行可能整行全是空格 ⇒ 绝不能 cin >> s（会在第 1 个空格处截断），必须整行读入。
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

string line_a; // 第 1 行原文（整行读入，空格原样保留）
string line_b; // 第 2 行原文（整行读入，空格原样保留）

// 读入两行原文。行尾的 '\r' 是 CRLF 数据在 Linux 评测时被 getline 留下的残留，
// 统一在规范化阶段丢弃，与本 skill 对 CRLF 数据的一贯处理一致。
void read_input() {
    getline(cin, line_a);
    getline(cin, line_b);
}

// 返回「删去所有空格与 '\r'，并把 ASCII 大写字母折叠成小写」后的规范串。
// 只折叠 'A'..'Z'，不受 locale 影响（题面保证每行只由字母和空格组成）。
string normalize(const string& s) {
    string res;
    ll len = s.size();
    for (ll i = 0; i < len; i++) {
        char c = s[i];
        if (c == ' ' || c == '\r') {
            continue;                     // 忽略空格；顺手丢掉 CRLF 的行尾残留
        }
        if (c >= 'A' && c <= 'Z') {
            c += 32;                      // 忽略大小写：ASCII 大写统一转小写
        }
        res += c;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    read_input();
    // 文件只有 0/1 行时对应的那行是空串，normalize 后仍为空串，自然与「空行」等价
    if (normalize(line_a) == normalize(line_b)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
