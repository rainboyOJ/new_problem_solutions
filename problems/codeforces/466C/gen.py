import random,sys
n=random.randint(1,9)
lim=int(sys.argv[1]) if len(sys.argv)>1 else 4
print(n)
print(*[random.randint(-lim,lim) for _ in range(n)])
