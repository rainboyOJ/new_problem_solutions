#include <iostream>


int main(){
    int i,n;
    int cnt=0;
    std::cin >> n;
    for (i=1;i<=n;i++){
        int t= i;
        while( t != 0){
            int a = t % 10;
            if( a == 1){
                cnt++;
            }
            t /= 10;
        }
    }
    std::cout << cnt << "\n";
    return 0;
}
