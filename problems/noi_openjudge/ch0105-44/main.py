rank = int(input())
limit = 104_729
is_prime = [True] * (limit + 1)
is_prime[0] = is_prime[1] = False

for number in range(2, int(limit**0.5) + 1):
    if is_prime[number]:
        # 从 number 的平方开始，之前的倍数已经被更小质因子筛掉。
        is_prime[number * number : limit + 1 : number] = [False] * (((limit - number * number) // number) + 1)

primes = [number for number, prime in enumerate(is_prime) if prime]
print(primes[rank - 1])
