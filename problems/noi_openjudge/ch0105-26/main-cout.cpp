#include <iostream>

int main(){
    int n,i,a;
    std::cin >> n;
    int cnt =0;
    for (i=1;i<=n;i++){
        std::cin >> a;
        int t1 = a % 10;
        a = a/10;
        int t2 = a % 10;
        a = a/10;
        int t3 = a % 10;
        a = a/10;
        int t4 = a % 10;

        if( t1>t2+t3+t4){
            cnt++;
        }
    }
    std::cout << cnt << "\n";
    return 0;
}
