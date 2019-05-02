import sys

def checkDuplicates(str):
    if len(str) > 128:
        # by pigeon-hole principle for ASCII character set
        return 'yes'
    else:
        # the set() data structure drops duplicates for us
        uniqueChars = set()
        for c in str:
            uniqueChars.add(c)
        if len(uniqueChars) < len(str):
            return 'yes'
        else:
            return 'no'

print('enter strings and find out if they contain duplicate characters')
print('exit with ctrl-c\n')
while True:
    print(checkDuplicates(sys.stdin.readline()[:-1]))
