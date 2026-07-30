limit = int(input())


def is_prime(number: int) -> bool:
    if number < 2:
        return False
    for divisor in range(2, int(number**0.5) + 1):
        if number % divisor == 0:
            return False
    return True


count = sum(
    is_prime(number) and str(number) == str(number)[::-1]
    for number in range(11, limit + 1)
)
print(count)
