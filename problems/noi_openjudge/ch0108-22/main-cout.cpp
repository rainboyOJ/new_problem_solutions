#include <iostream>
int n,a[1010][1010],x=1,y;
int main()
{
    std::cin >> n;
    y=n;
    int u=(2*n)-1;
    a[x][y]=1;
    for(int i=1;i<=u*u;i++)
    {
        int q=x,w=y;
        if((x==1&&y==u)||(a[x-1][y+1]>0))
            q++;
        else if(x==1){
            q=u;
            w++;
        }
        else if(y>=u){
            q--;
            w=1;
        }
        else if(x==q&&y==w){
            q--;
            w++;
        }
        a[q][w]=i+1;
        x=q;y=w;
    }
    for(int i=1;i<=u;i++)
    {
        for(int j=1;j<=u;j++)
            std::cout << a[i][j] << " ";
        std::cout << "\n";
    }
}
