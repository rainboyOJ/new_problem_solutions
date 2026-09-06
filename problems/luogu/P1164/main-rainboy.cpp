/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2024-07-13 11:10
 * update_at: 2026-09-06 20:40
 */
//Author by [Rainboy](https://github.com/rainboylvx)
//date: 2024-07-13 11:10:15
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int w[maxn];
int f[10005];

int main (int argc, char *argv[]) {
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> w[i];
    }
    f[0] = 1;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j =m ;j>=w[i];j--)
        {
            f[j] += f[j-w[i]];
        }
    }
    std::cout << f[m] << "\n";

    return 0;
}