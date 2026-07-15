word_to_number = {
    "zero": 0, "one": 1, "two": 2, "three": 3, "four": 4,
    "five": 5, "six": 6, "seven": 7, "eight": 8, "nine": 9,
    "ten": 10, "eleven": 11, "twelve": 12, "thirteen": 13,
    "fourteen": 14, "fifteen": 15, "sixteen": 16,
    "seventeen": 17, "eighteen": 18, "nineteen": 19, "twenty": 20,
    "a": 1, "both": 2, "another": 1, "first": 1, "second": 2,
    "third": 3,
}

words = input().strip().rstrip(".").lower().split()
numbers = map(lambda word: word_to_number.get(word), words)
parts = sorted(f"{x * x % 100:02d}" for x in filter(lambda x: x is not None, numbers))
password = "".join(parts).lstrip("0")
print(password if password else "0")
