#include <cstring>
#include <iostream>


int n,m;
int a[1400][1400];

void init(){
    std::cin >> n >> m;
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            std::cin >> a[i][j];
        }
    }
}
void print(int x,int y){
    while( x >= 1 && x <= n && y >=1 && y <=m){
        std::cout << a[x][y] << "\n";
        x +=1;
        y -=1;
    }
}
int main(){
    init();
    int i;
    for (i=1;i<=n+m-1;i++){
        int x,y;
        if( i <= m){
            y = i;
            x = 1;
        }
        else {
            y = m;
            x = (i-m) +1;
        }
        print(x,y);
        //std::cout << x << " " << y << "\n";
    }
    return 0;
}
