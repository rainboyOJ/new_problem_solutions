#include <bits/stdc++.h>
using namespace std;

int n,k;
int a[1005];

int main(){
    std::cin >> n >> k;
    int i,j;
    for(i=1;i<=n;i++){
        std::cin >> a[i];
    }
    for(i=1;i<=n;i++){
        for(j=i+1;j<=n;j++){
            if( a[i]+a[j] == k)
            {
                std::cout << "yes";
                return 0;
            }
        }
    }
    std::cout << "no";
    return 0;
}
