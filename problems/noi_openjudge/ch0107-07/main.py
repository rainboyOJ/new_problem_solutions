base_pair = str.maketrans({"A": "T", "T": "A", "G": "C", "C": "G"})
print(input().strip().translate(base_pair))
