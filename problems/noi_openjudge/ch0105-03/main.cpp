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
    double sum = 0;
    for(int i=1;i<=n;++i){
        double a;
        std::cin >> a;
        sum += a;
    }
    std::cout << 
        fixed << setprecision(4)
        << sum / n
        << std::endl;


    return 0;
}
