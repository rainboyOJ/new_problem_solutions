text = input()
result = [chr(ord(left) + ord(right)) for left, right in zip(text, text[1:] + text[:1])]
print("".join(result))
