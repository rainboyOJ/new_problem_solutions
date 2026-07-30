left, right = map(int, input().split())


def largest_prime_factor(number: int) -> int:
    factor = 2
    largest = 1
    while factor * factor <= number:
        while number % factor == 0:
            largest = factor
            number //= factor
        factor += 1
    return max(largest, number)


print(",".join(str(largest_prime_factor(number)) for number in range(left, right + 1)))
