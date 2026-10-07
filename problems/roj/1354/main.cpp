/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:24
 * update_at: 2026-10-05 11:24
 */
// roj 1354 括弧匹配检验：用栈判断圆括号与方括号是否两两配对且不交叉。
#include <iostream>
#include <string>

typedef long long ll;
using namespace std;

char st[4096]; // 栈：存尚未闭合的左括号，栈底是最外层的左括号
char br[4096]; // 折算后的括号串：全角括号换成半角，其它字符全部滤掉

int main() {
    string all;
    string line;
    // 数据行可能是 CRLF 也可能夹杂空行，逐行读入拼接；换行与匹配无关，后面会被滤掉
    while (getline(cin, line)) {
        all += line;
    }

    // 第一步：题面样例用的是全角括号（UTF-8 三字节），先折算成半角，同时滤掉非括号字符
    ll blen = 0;      // 折算后括号串的长度
    ll n = all.size();
    for (ll i = 0; i < n; ) {
        char c = all[i];
        if (c == '(' || c == ')' || c == '[' || c == ']') {
            br[blen] = c;
            blen++;
            i++;
        } else if (c == '\xef' && i + 2 < n && all[i + 1] == '\xbc') {
            // 全角 （ ） ［ ］ 的 UTF-8 编码是 EF BC 88 / 89 / BB / BD
            char last = all[i + 2];
            if (last == '\x88') {
                br[blen] = '(';
                blen++;
            } else if (last == '\x89') {
                br[blen] = ')';
                blen++;
            } else if (last == '\xbb') {
                br[blen] = '[';
                blen++;
            } else if (last == '\xbd') {
                br[blen] = ']';
                blen++;
            }
            i += 3;
        } else {
            i++; // 空格、换行等字符不影响匹配，直接跳过
        }
    }

    // 第二步：扫一遍括号串，右括号只允许消耗栈顶那个同类左括号
    ll top = 0;   // 栈内元素个数，栈顶是 st[top-1]
    ll ok = 1;    // 1 表示目前仍然合法
    for (ll i = 0; i < blen; i++) {
        char c = br[i];
        if (c == '(' || c == '[') {
            st[top] = c; // 左括号入栈，等它对应的右括号
            top++;
        } else if (top == 0) {
            ok = 0; // 栈空却来了右括号：右括号多了
            break;
        } else {
            char need; // 这个右括号唯一能配的左括号
            if (c == ')') {
                need = '(';
            } else {
                need = '[';
            }
            if (st[top - 1] != need) {
                ok = 0; // 栈顶是另一类左括号：类型错配，或与外层交叉
                break;
            }
            top--; // 配对成功，最内层这一层闭合
        }
    }
    if (ok && top > 0) {
        ok = 0; // 扫完栈非空：还有左括号没人配
    }

    if (ok) {
        cout << "OK" << "\n";
    } else {
        cout << "Wrong" << "\n";
    }
    return 0;
}
