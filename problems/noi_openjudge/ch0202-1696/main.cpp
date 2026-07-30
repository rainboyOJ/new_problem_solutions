/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;
#define F(n) for(int i =1;i<=n;i++)

double calc() {
    string s;
    cin >> s;
    if( s[0] == '*'){
        return calc() * calc();
    }
    else if( s[0] == '-'){
        return calc() - calc();
    }
    else if( s[0] == '+'){
        return calc() + calc();
    }
    else if( s[0] == '/'){
        return calc() / calc();
    }
    else {
        return std::stod(s);
    }
}
int main(){
    double ans = calc();
    printf("%f\n",ans);
    return 0;
}
