/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:05
 * update_at: 2026-10-05 04:05
 */
// main.cpp：按题面给出的连分式递归定义直接计算 f(x,n)，保留两位小数。

#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

double x; // 题目输入的第一个数 x
ll n;     // 题目输入的第二个数 n

// 按定义计算连分式：f(x,1) = x/(1+x)，f(x,n) = x/(n + f(x,n-1))
double f(ll k) {
    if (k == 1) {
        return x / (1.0 + x);
    }
    return x / (k + f(k - 1));
}

int main() {
    cin >> x >> n;
    printf("%.2f\n", f(n));
    return 0;
}
