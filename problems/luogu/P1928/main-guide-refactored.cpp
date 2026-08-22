/**
 * P1928 外星密码 - 重构版：拆分职责，便于阅读
 * 原版将所有逻辑写在一个 decode() 里，这里按语义拆分为若干小函数。
 */

#include <iostream>
#include <string>

std::string compressed;
int pos = 0;

// ---------- 基础工具 ----------
bool at_end() { return pos >= (int)compressed.size(); }
char peek() { return at_end() ? '\0' : compressed[pos]; }
void advance() { if (!at_end()) ++pos; }

// ---------- 语义解析函数 ----------

// 解析一个正整数（重复次数）
int parse_number() {
    int num = 0;
    while (!at_end() && isdigit(peek())) {
        num = num * 10 + (peek() - '0');
        advance();
    }
    return num;
}

// 解析一段“普通字母序列”（不含 [ ] 数字）
std::string parse_letters() {
    std::string result;
    while (!at_end() && isupper(peek())) {
        result += peek();
        advance();
    }
    return result;
}

// 解析 [...] 括号内的完整内容（含嵌套），返回解压后的字符串
std::string parse_bracketed() {
    advance();                    // 跳过 '['
    int repeat = parse_number();  // 读取重复次数
    std::string inner = decode(); // 递归解析内层
    advance();                    // 跳过 ']'

    std::string expanded;
    for (int i = 0; i < repeat; ++i) expanded += inner;
    return expanded;
}

// 核心递归：解析当前层级直到 ']' 或串尾
std::string decode() {
    std::string result;
    while (!at_end() && peek() != ']') {
        if (isupper(peek())) {
            result += parse_letters();
        } else if (peek() == '[') {
            result += parse_bracketed();
        } else {
            advance(); // 题目保证不会出现其他字符，防御性跳过
        }
    }
    return result;
}

int main() {
    std::cin >> compressed;
    std::cout << decode() << '\n';
    return 0;
}