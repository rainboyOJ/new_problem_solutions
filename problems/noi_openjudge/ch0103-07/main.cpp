/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
// talk is cheap,show me your code
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    double x,a,b,c,d;
    std::cin >> x >> a >> b >> c >> d;
    double answer = a*x*x*x +b*x*x+c*x+d;
    cout << fixed << setprecision(7) << answer;
    return 0;
}
