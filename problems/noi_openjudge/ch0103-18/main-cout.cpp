#include <iostream>
/* 
 * an = a1 +(n-1)*(a2-a1)
 * */

int main(){
    int a1,a2,n;
    std::cin >> a1 >> a2;
    std::cin >> n;
    int ans = a1+(n-1)*(a2-a1);
    std::cout << ans << "\n";
    return 0;
}
