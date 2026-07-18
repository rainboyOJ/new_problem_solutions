word_to_number = {
    "zero": 0, "one": 1, "two": 2, "three": 3, "four": 4, "five": 5,
    "six": 6, "seven": 7, "eight": 8, "nine": 9, "ten": 10, "eleven": 11,
    "twelve": 12, "thirteen": 13, "fourteen": 14, "fifteen": 15, "sixteen": 16,
    "seventeen": 17, "eighteen": 18, "nineteen": 19, "twenty": 20,
    "a": 1, "both": 2, "another": 1, "first": 1, "second": 2, "third": 3,
}

words = input().strip().rstrip(".").lower().split()
parts = sorted(
    f"{word_to_number[w] * word_to_number[w] % 100:02d}"
    for w in words
    if w in word_to_number
)
print("".join(parts).lstrip("0") or "0")
