/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:11
 * update_at: 2026-08-08 23:11
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;

int n;

int b[maxn]; //桶

// 01序列，产生选或不选的所有可能情况
void dfs(int dep) {
    if( dep > n) {
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            cout << b[i] << " ";
        }
        std::cout << "\n";
        return;
    }
    for(int i = 0;i <= 1 ;++i ) // i: 0->1
    {
        b[dep] = i;
        dfs(dep+1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}
