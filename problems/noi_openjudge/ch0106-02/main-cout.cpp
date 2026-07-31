#include <iostream>

int n=10,h;
int a[10+5];

int main(){
    int i;
    for (i=1;i<=n;i++){
        std::cin >> a[i];
    }
    std::cin >> h;
    h += 30;
    int cnt = 0;
    for (i=1;i<=n;i++){
        if( h >= a[i]){
            cnt++;
        }
    }
    std::cout << cnt;

    return 0;
}
