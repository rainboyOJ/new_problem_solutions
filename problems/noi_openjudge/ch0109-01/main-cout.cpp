#include <iostream>
using namespace std;

int n,x;
int a[10005];
int main(){
    std::cin >> n;
    int i,j;
    for (i=1;i<=n;i++){
        std::cin >> a[i];
    }
    std::cin >> x;
    for (i=1;i<=n;i++){
        if( a[i] == x){
            std::cout << i << "\n";
            return 0;
        }
    }
    std::cout << "-1";
    return 0;
}
