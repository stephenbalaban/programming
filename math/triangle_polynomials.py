import sys


def apply_op(row, op, op_width=3):
    for i in range(len(row) - op_width + 1):
        yield op(row[i], row[i+2])


def pyramid(n, op=lambda a, b: a + b):
    z = list(range(n))
    while len(z) > 0:
        yield z
        z = list(apply_op(z, op=op))


if __name__ == '__main__':
    n = int(sys.argv[1])
    print(list(pyramid(n)))
