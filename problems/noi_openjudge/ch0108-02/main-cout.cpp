#include <iostream>
int a[20][20];
int n,x,y;
int main(){
    std::cin >> n >> x >> y;
    int i,j;
    for (i=1;i<=n;i++){
        std::cout << "(" << x << "," << i << ") ";
    }
    std::cout << "\n";

    for (i=1;i<=n;i++){
        std::cout << "(" << i << "," << y << ") ";
    }
    std::cout << "\n";
    
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            if( i-j == x - y){
                std::cout << "(" << i << "," << j << ") ";
                break;
            }
        }
    }
    std::cout << "\n";

    for (i=n;i>=1;i--){
        for (j=1;j<=n;j++){
            if( i+j == x + y){
                std::cout << "(" << i << "," << j << ") ";
                break;
            }
        }
    }
    std::cout << "\n";
    return 0;
}
