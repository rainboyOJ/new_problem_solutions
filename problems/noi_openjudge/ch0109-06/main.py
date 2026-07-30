from collections import Counter

word = input().strip()
frequencies = Counter(word).values()
difference = max(frequencies) - min(frequencies)

is_prime = difference >= 2 and all(difference % divisor for divisor in range(2, int(difference**0.5) + 1))
print("Lucky Word" if is_prime else "No Answer")
print(difference if is_prime else 0)
