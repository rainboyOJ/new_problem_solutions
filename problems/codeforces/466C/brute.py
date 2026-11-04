import sys
def main():
    data=list(map(int,sys.stdin.buffer.read().split()))
    n=data[0]; a=data[1:1+n]
    p=[0]*(n+1)
    for i in range(n): p[i+1]=p[i]+a[i]
    tot=p[n]; ans=0
    for i in range(1,n):
        for j in range(i+1,n):
            if p[i]==p[j]-p[i]==tot-p[j]: ans+=1
    print(ans)
main()
