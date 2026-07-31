#include <iostream>

int fab(int n){
    if( n== 0 || n == 1)
        return 1;
    return fab(n-1)+fab(n-2);
}
int main(){
    int t;
    while (std::cin >> t){
        int ans = fab(t);
        std::cout << ans << "\n";
    }
    return 0;
}
