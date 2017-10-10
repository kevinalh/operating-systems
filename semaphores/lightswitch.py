from threading import Semaphore


class LightSwitch:
    def __init__(self):
        self.counter = 0
        self.mutex = Semaphore(1)

    def lock(self, sem: Semaphore):
        self.mutex.acquire()
        self.counter += 1
        if self.counter == 1:
            sem.acquire()
        self.mutex.release()

    def unlock(self, sem: Semaphore):
        self.mutex.acquire()
        self.counter -= 1
        if self.counter == 0:
            sem.release()
        self.mutex.release()