/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:12
 */
// brute.cpp：按 BNF 定义递归展开每个化学式，直接累计元素个数。
#include <bits/stdc++.h>
using namespace std;

typedef map<string, long long> AtomCount;

long long read_number(const string &text, int &position) {
    if (position >= (int)text.size() || !isdigit(text[position])) return 1;
    long long value = 0;
    while (position < (int)text.size() && isdigit(text[position])) {
        value = value * 10 + text[position++] - '0';
    }
    return value;
}

void merge_count(AtomCount &target, const AtomCount &source, long long multiplier) {
    for (AtomCount::const_iterator it = source.begin(); it != source.end(); ++it) {
        target[it->first] += it->second * multiplier;
    }
}

AtomCount parse_formula(const string &text, int &position) {
    AtomCount result;
    while (position < (int)text.size() && text[position] != ')' && text[position] != '+'
            && text[position] != '=') {
        AtomCount term;
        if (text[position] == '(') {
            position++;
            term = parse_formula(text, position);
            position++;
        } else {
            string element(1, text[position++]);
            if (position < (int)text.size() && islower(text[position])) element += text[position++];
            term[element] = 1;
        }
        merge_count(result, term, read_number(text, position));
    }
    return result;
}

AtomCount parse_expression(const string &text, int &position) {
    AtomCount result;
    while (true) {
        long long multiplier = read_number(text, position);
        AtomCount formula = parse_formula(text, position);
        merge_count(result, formula, multiplier);
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
        position++;
        AtomCount right = parse_expression(equation, position);
        cout << (left == right ? 'Y' : 'N') << '\n';
    }

    return 0;
}
