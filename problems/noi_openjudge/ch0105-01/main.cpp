/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    std::cin >> n;
    int sum = 0;
    for(int i=1;i<=n;++i){
        int t;
        std::cin >> t;
        sum += t;
    }
    double ans = sum * 1.0 / n;
    std::cout <<fixed <<  std::setprecision(2) << ans << std::endl;
    return 0;
}
