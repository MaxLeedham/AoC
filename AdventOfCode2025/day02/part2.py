with open("input.txt", "r") as f:
    products = f.readline().strip().split(",")

# products = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124".split(",")

ids = [(int(product.split("-")[0]), int(product.split("-")[1])) for product in products]

def isInvalid(id: str) -> bool:    
    for i in range(len(id)):
        num_is = len(id) / len(id[:i+1])

        if int(num_is) != num_is:
            continue

        if num_is == 1:
            return False

        if id == (id[:i+1]) * int(num_is):
            return True

    return False

invalid = []
for id_start, id_end in ids:
    for i in range(id_start, id_end+1):            
        if isInvalid(str(i)):
            invalid.append(i)

print(sum(invalid))
