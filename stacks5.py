class SortedStack:
    stackA = []
    stackB = []
    def sorted_push(self, val):
        while self.stackA and self.stackA[-1] < val:
                self.stackB.append(self.stackA.pop())
        self.stackA.append(val)
        while self.stackB:
            self.stackA.append(self.stackB.pop())
    def sorted_pop(self):
        return self.stackA.pop()
    def is_empty(self):
        return not self.stackA

ss = SortedStack()
while True:
    values = input('enter a list of values separated by spaces\n').split(' ')
    for value in values:
        ss.sorted_push(int(value))
    print('sorted stack contents are...')
    while not ss.is_empty():
        print(ss.sorted_pop())
