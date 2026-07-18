days=[sum(map(int,input().split())) for _ in range(7)]
best=max(range(7), key=lambda i: (days[i], -i))
print(0 if days[best]<=8 else best+1)
