/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <iostream>
using namespace std;

//gcd 求最大公约数的算法, 辗转相除法
int gcd(int a, int b)
{
    if( b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    long long a, b; // c++ long int -> int
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    return 0;
}
