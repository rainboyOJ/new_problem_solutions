import re

numbers = sorted(int(text) for text in re.findall(r"\d+", input()))

print(",".join(map(str, numbers)) if numbers else 0)
