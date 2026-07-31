#include <iostream>
int n,m,a[1010][1010];
void init(){
    std::cin >> n >> m;
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            std::cin >> a[i][j];
        }
    }
}

int main(){
    init();
    int i,j;
    int r1=1,r2=n,c1=1,c2=m;
    while( r1 <= r2 && c1 <= c2){

        for(j=c1;j<=c2;j++)
            std::cout << a[r1][j] << "\n";

        for(i=r1+1;i<=r2;i++)
            std::cout << a[i][c2] << "\n";

        if( r1 != r2)
            for(j = c2-1;j>=c1;j--)
                std::cout << a[r2][j] << "\n";

        if(c1!=c2)
            for(int i=r2-1;i>r1;i--)
                std::cout << a[i][c1] << "\n";
        r1++;
        r2--;
        c1++;
        c2--;
    }
    return 0;
}
