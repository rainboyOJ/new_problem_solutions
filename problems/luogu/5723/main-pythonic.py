def is_prime(x):
    return x>1 and all(x%d for d in range(2,int(x**0.5)+1))
L=int(input()); s=0; ps=[]
for p in range(2,10**9):
    if is_prime(p):
        if s+p>L: break
        ps.append(p); s+=p
print(*ps, sep='\n')
print(len(ps))
