#include <cstring>
#include <iostream>

#define inf 0x7f7f7f7f

int n;
int a[200];
int max = -inf;
int main(){
    std::cin >> n;
    int i;
    for (i=1;i<=n;i++){
        std::cin >> a[i];
        if( max  < a[i])
            max = a[i];
    }
    int sum = 0;
    for (i=1;i<=n;i++){
        if( max != a[i])
            sum += a[i];
    }
    std::cout << sum << "\n";
    return 0;
}
