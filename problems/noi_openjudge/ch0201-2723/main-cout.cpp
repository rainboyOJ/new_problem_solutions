#include <bits/stdc++.h>
using namespace std;


int n,m;

int main(){
    std::cin >> n >> m;
    int i;
    for(i=1;i<m;i++){
        if( 
                n % i == 0 &&
                n % (m-i) == 0
                ){
            std::cout << i << "\n";
            return 0;
        }
    }
    std::cout << "-1";
    return 0;
}
