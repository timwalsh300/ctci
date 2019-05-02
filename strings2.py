import sys

def checkAnagrams(strA, strB):
    if len(strA) != len(strB):
        # trivial case
        return 'no'
    else:
        if sorted(strA) == sorted(strB):
            return 'yes'
        else:
            return 'no'


print('enter strings and find out if they are anagrams')
print('exit with ctrl-c\n')
while True:
    print('string A: ')
    a = sys.stdin.readline()[:-1]
    print('string B: ')
    b = sys.stdin.readline()[:-1]
    print(checkAnagrams(a, b) + '\n')
