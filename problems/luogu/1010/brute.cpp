/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 15:17:33
 */
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：朴素验证解，用不断寻找不超过 x 的最大 2 的幂来构造表达式。

int n;

string build_expr(int x);

string build_term(int exp) {
    if (exp == 0) return "2(0)";
    if (exp == 1) return "2";
    return "2(" + build_expr(exp) + ")";
}

string build_expr(int x) {
    if (x == 1) return "2(0)";
    if (x == 2) return "2";

    vector<int> exps;
    int power = 1;
    int exp = 0;
    while (power * 2 <= x) {
        power *= 2;
        exp++;
    }

    int rest = x;
    while (power > 0) {
        if (rest >= power) {
            exps.push_back(exp);
            rest -= power;
        }
        power /= 2;
        exp--;
    }

    string ans = "";
    for (int i = 0; i < (int)exps.size(); i++) {
        if (i > 0) ans += "+";
        ans += build_term(exps[i]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cout << build_expr(n) << '\n';

    return 0;
}
