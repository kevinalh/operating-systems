# Producers-Consumers with finite buffer
from threading import *
from collections import deque

np = 10 # Amount of producers
nc = 30 # Amount of consumers
m = 12 # How much each consumer wants

# Buffer size
n = 5
buffer = deque()

# Semaphores
items = Semaphore(0)
mutex = Semaphore(1)
spaces = BoundedSemaphore(n)


def producer():
    for i in range(int(m*nc/np)):
        event = produce_item()

        spaces.acquire()
        mutex.acquire()

        buffer.append(event)

        mutex.release()
        items.release()


def consumer():
    for i in range(m):
        items.acquire()
        mutex.acquire()

        event = buffer.popleft()

        mutex.release()
        spaces.release()

        consume_item(event)


def consume_item(event):
    print(str(current_thread().getName()) + ': Consuming item produced by: ' + str(event))


def produce_item():
    return current_thread().getName()


producers = [Thread(target=producer, name='Producer ' + str(i)) for i in range(np)]
consumers = [Thread(target=consumer, name='Consumer ' + str(i)) for i in range(nc)]

[x.start() for x in set().union(consumers, producers)]