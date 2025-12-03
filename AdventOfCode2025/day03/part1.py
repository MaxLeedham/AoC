banks = []

with open("input.txt", "r") as f:
    banks = [[int(jolt) for jolt in line.strip()] for line in f.readlines()]

total = 0

for bank in banks:
    left = sorted(bank[:-1])[-1]
    left_index = bank.index(left)
    right = sorted(bank[left_index+1:])[-1]
    total += right + (left * 10)

print(f"Total: {total}")