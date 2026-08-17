/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
#include <bits/stdc++.h>
using namespace std;

// 元素 -> 原子总数 的映射
typedef map<string, long long> AtomCount;

// 从 position 开始读一个整数；没有数字时按系数 1 处理。
long long read_number(const string &text, int &position) {
    if (position >= (int)text.size() || !isdigit(text[position])) return 1;
    long long result = 0;
    while (position < (int)text.size() && isdigit(text[position])) {
        result = result * 10 + text[position] - '0';
        position++;
    }
    return result;
}

// 把 source 中的元素计数乘 multiplier 后累加进 target。
void add_count(AtomCount &target, const AtomCount &source, long long multiplier) {
    for (AtomCount::const_iterator it = source.begin(); it != source.end(); ++it) {
        target[it->first] += it->second * multiplier;
    }
}

// 递归解析一个化学式：由若干“项+系数”组成，项可以是元素或括号括起来的化学式。
AtomCount parse_formula(const string &text, int &position) {
    AtomCount result;
    while (position < (int)text.size() && text[position] != ')'
            && text[position] != '+' && text[position] != '=') {
        AtomCount term;
        if (text[position] == '(') {
            position++;
            term = parse_formula(text, position); // 括号内整个化学式
            position++;                           // 跳过右括号
        } else {
            // 元素：一个大写字母加可选的一个小写字母。
            string element;
            element += text[position++];
            if (position < (int)text.size() && islower(text[position])) {
                element += text[position++];
            }
            term[element] = 1;
        }
        // 项后面的数字是整体系数，作用到该项包含的全部元素上。
        add_count(result, term, read_number(text, position));
    }
    return result;
}

// 解析一个表达式：若干带系数的化学式用 '+' 连接。
AtomCount parse_expression(const string &text, int &position) {
    AtomCount result;
    while (true) {
        long long multiplier = read_number(text, position);
        AtomCount formula = parse_formula(text, position);
        add_count(result, formula, multiplier);
        if (position >= (int)text.size() || text[position] != '+') break;
        position++;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        string equation;
        cin >> equation;
        int position = 0;
        AtomCount left = parse_expression(equation, position);
        position++; // 跳过 '='
        AtomCount right = parse_expression(equation, position);
        cout << (left == right ? 'Y' : 'N') << '\n';
    }

    return 0;
}