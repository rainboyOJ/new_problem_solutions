/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
/* P1928 外星密码：递归解析，遇到 [k...] 就递归展开括号内的内容。 */

#include <iostream>
#include <string>

std::string compressed;  // 待解压的密码
int pos = 0;             // 当前解析到压缩串的第几个字符

// 从 pos 开始解析一段内容，遇到 ']' 或串尾就结束，返回解压后的字符串。
// 调用栈天然对应嵌套括号：读到 [ 里的数字后递归，就是进入更里层。
std::string decode() {
    std::string result;
    while (pos < (int)compressed.size() && compressed[pos] != ']') {
        char ch = compressed[pos];
        if (ch >= 'A' && ch <= 'Z') {
            result += ch;  // 普通字母直接加入结果
            pos += 1;
        } else if (ch == '[') {
            pos += 1;  // 跳过 '['
            int repeat = 0;
            // 数字可能不止一位，逐位拼出重复次数。
            while (pos < (int)compressed.size() && compressed[pos] >= '0' && compressed[pos] <= '9') {
                repeat = repeat * 10 + (compressed[pos] - '0');
                pos += 1;
            }
            std::string inner = decode();  // 递归解析括号内的内容（可能还有嵌套）
            for (int i = 0; i < repeat; i += 1) {
                result += inner;  // 按重复次数展开
            }
        } else {
            pos += 1;  // 其余字符（题目保证不会出现）直接跳过
        }
    }
    if (pos < (int)compressed.size() && compressed[pos] == ']') {
        pos += 1;  // 跳过 ']'，让外层继续解析
    }
    return result;
}

int main() {
    std::cin >> compressed;
    std::cout << decode() << '\n';
    return 0;
}
