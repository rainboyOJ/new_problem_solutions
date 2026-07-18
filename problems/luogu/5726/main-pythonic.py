n=int(input())
a=list(map(int,input().split()))
print(f"{(sum(a)-max(a)-min(a))/(n-2):.2f}")
