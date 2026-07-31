#include <bits/stdc++.h>
using namespace std;

int a,b,c;


int main(){
    std::cin >> a >> b >> c;
    int x_limit = c / a;
    int y_limit = c / b;
    int cnt=0;
    int i,j;
    for(i=0;i<=x_limit;i++){
        for(j=0;j<=y_limit;j++){
            if( a*i + b*j == c)
                cnt++;
        }
    }
    std::cout << cnt << "\n";
    return 0;
}
