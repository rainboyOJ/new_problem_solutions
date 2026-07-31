#include <iostream>
int main(){
    int n,a,b,c = 0,max = -1;
    std::cin >> n;
    int i;
    for (i=1;i<=n;i++){
        std::cin >> a >> b;
        if( a  < 90 || a > 140 || b <60 || b > 90){
            if( max < c )
                max = c;
            c = 0;
        }
        else {
            c++;
        }
    }
    if( max < c )
        max = c;
    std::cout << max << "\n";
    return 0;
}
