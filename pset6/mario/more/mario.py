from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        if height > 0 and height <= 8:
            break
        
    for i in range(1, height + 1):
        spaces(height - i)
        hashes(i)
        spaces(2)
        hashes(i)
        print()


# print n number of hashes
def hashes(n):
    print("#" * n, end='')

# print n number of spaces


def spaces(n):
    print(" " * n, end='')


main()
