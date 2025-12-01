rotations = []

with open("input.txt", "r") as f:
    rotations = [line.strip() for line in f.readlines()]

dial = 50
code = 0

def parse(rotation: str) -> int:
    amount = int(rotation[1::])
    return amount if rotation[0] == 'R' else -amount

for rotation in rotations:
    dial = (dial + parse(rotation)) % 100

    if dial == 0:
        code += 1

print(f"Final code: {code}")