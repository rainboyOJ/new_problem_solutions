n=int(input()); v=1
for i in range(n):
    print(''.join(f'{v+j:02d}' for j in range(n-i)))
    v+=n-i
