import sys

MOD = 9901

def power_and_sum(base, terms):
    if terms == 0:
        return 1, 0
    half_power, half_sum = power_and_sum(base, terms // 2)
    power = half_power * half_power % MOD
    total = half_sum * (1 + half_power) % MOD
    if terms % 2:
        return power * base % MOD, (total + power) % MOD
    return power, total

def main():
    number, exponent = map(int, sys.stdin.buffer.read().split())
    answer = 1
    prime = 2
    while prime * prime <= number:
        if number % prime == 0:
            count = 0
            while number % prime == 0:
                number //= prime
                count += 1
            answer = answer * power_and_sum(prime % MOD, count * exponent + 1)[1] % MOD
        prime += 1
    if number > 1:
        answer = answer * power_and_sum(number % MOD, exponent + 1)[1] % MOD
    print(answer)

if __name__ == "__main__":
    main()
