from collections import Counter

text = input().strip()
frequencies = Counter(text)
print(next((character for character in text if frequencies[character] == 1), "no"))
