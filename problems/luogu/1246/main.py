from math import comb


word = input().strip()
letters = [ord(character) - 97 for character in word]

if len(word) > 6 or any(left >= right for left, right in zip(letters, letters[1:])):
    print(0)
else:
    rank = sum(comb(26, length) for length in range(1, len(word)))
    previous = -1
    for position, current in enumerate(letters):
        remaining = len(word) - position - 1
        rank += sum(comb(25 - candidate, remaining) for candidate in range(previous + 1, current))
        previous = current
    print(rank + 1)
