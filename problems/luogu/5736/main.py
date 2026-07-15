def is_prime(x):
    if x < 2:
        return False
    divisor = 2
    while divisor * divisor <= x:
        if x % divisor == 0:
            return False
        divisor += 1
    return True


n = int(input())
numbers = list(map(int, input().split()))

answer = [x for x in numbers if is_prime(x)]
print(*answer)
