encrypted = input().strip()
original = input().strip()

if len(encrypted) == len(original) and sorted(
    encrypted.count(character) for character in set(encrypted)
) == sorted(original.count(character) for character in set(original)):
    print("YES")
else:
    print("NO")
