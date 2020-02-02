from collections import deque

class PetQueue:
    primary_list = deque()
    temp_list = deque()
    def enqueue_dog(self, name):
        self.primary_list.appendleft(('dog', name))
    def enqueue_cat(self, name):
        self.primary_list.appendleft(('cat', name))
    def dequeue_any(self):
        if not self.is_empty():
            (pet, name) = self.primary_list.pop()
            return name
        else:
            return 'queue is empty'
    def dequeue_cat(self):
        while self.primary_list:
            (pet, name) = self.primary_list.pop()
            if pet == 'cat':
                while self.temp_list:
                    self.primary_list.append(self.temp_list.pop())
                return name
            else:
                self.temp_list.append((pet, name))
        return 'no cats in the queue'
    def dequeue_dog(self):
        while self.primary_list:
            (pet, name) = self.primary_list.pop()
            if pet == 'dog':
                while self.temp_list:
                    self.primary_list.append(self.temp_list.pop())
                return name
            else:
                self.temp_list.append((pet, name))
        return 'no dogs in the queue'
    def is_empty(self):
        return not self.primary_list

shelter = PetQueue()
shelter.enqueue_dog('mark')
shelter.enqueue_dog('paul')
shelter.enqueue_cat('kate')
shelter.enqueue_dog('bill')
shelter.enqueue_cat('rosie')
print('pet shelter queue is...')
print(shelter.primary_list)
print('next cat is ' + shelter.dequeue_cat())
print('next cat is ' + shelter.dequeue_cat())
print('next dog is ' + shelter.dequeue_dog())
print('pet shelter queue is...')
print(shelter.primary_list)
print('adding dog named phil')
shelter.enqueue_dog('phil')
print('next pet is ' + shelter.dequeue_any())

