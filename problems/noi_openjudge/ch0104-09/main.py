number = int(input())
divisors = [divisor for divisor in (3, 5, 7) if number % divisor == 0]
print(" ".join(map(str, divisors)) if divisors else "n")
