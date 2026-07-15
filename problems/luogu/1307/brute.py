text = input().strip()

sign = ""
if text.startswith("-"):
    sign = "-"
    text = text[1:]

reversed_digits = text[::-1].lstrip("0")
print(sign + (reversed_digits if reversed_digits else "0"))
