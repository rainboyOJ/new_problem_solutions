n=int(input())
a=b=1
for _ in range(n-1):
    a,b=b,a+b
print(f"{a:.2f}" if n else "0.00")
