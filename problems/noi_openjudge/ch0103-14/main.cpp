/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int h,r;
    cin >> h >> r;
    double pi = 3.14159;
    double v = pi *r *r *h;
    int a = 20000 / v;
    if( a * v < 20000)
        a = a +1;
    cout << a;

    return 0;
}
