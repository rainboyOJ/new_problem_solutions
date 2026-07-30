import sys

text = input().strip()
length = len(text)
is_palindrome = [[False] * length for _ in range(length)]
answer = []

for index in range(length):
    is_palindrome[index][index] = True

for substring_length in range(2, length + 1):
    for start in range(length - substring_length + 1):
        end = start + substring_length - 1
        if text[start] == text[end] and (substring_length == 2 or is_palindrome[start + 1][end - 1]):
            is_palindrome[start][end] = True
            answer.append(text[start : end + 1])

sys.stdout.write("\n".join(answer))
if answer:
    sys.stdout.write("\n")
