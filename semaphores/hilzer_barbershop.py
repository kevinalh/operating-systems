# Hilzer's Barbershop
from threading import Semaphore, Thread

m = 1000
n = 20 # Max amount of customers
customers = 0

mutex = Semaphore(1)
sofa = Semaphore(4)
customer1 = Semaphore(0)
customer2 = Semaphore(0)
barber = Semaphore(0)
payment = Semaphore(0)
receipt = Semaphore(0)
queue1 = []
queue2 = []


def customer_f():
    global customers
    sem1 = Semaphore(0)
    sem2 = Semaphore(0)

    mutex.acquire()
    if customers == n:
        mutex.release()
        return
    else:
        customers += 1
        queue1.append(sem1)
    mutex.release()

    # Enter shop
    customer1.release()
    sem1.acquire()

    sofa.acquire()
    # Sit on sofa

    sem1.release()

    mutex.acquire()
    queue2.append(sem2)
    mutex.release()

    customer2.release()
    sem2.acquire()

    sofa.release()

    # Sit in barber chair

    # Pay
    payment.release()
    receipt.acquire()

    mutex.acquire()
    customers -= 1
    mutex.release()


def barber_f():
    global customers
    customer1.acquire()

    mutex.acquire()
    sem: Semaphore = queue1.pop(0)
    sem.release()
    sem.acquire()
    mutex.release()
    sem.release()

    customer2.acquire()
    mutex.acquire()
    sem: Semaphore = queue2.pop(0)
    mutex.release()
    sem.release()

    barber.release()
    # Cut Hair

    payment.acquire()
    # Accept payment
    receipt.release()


t_customers = [Thread(target=customer_f, name="Customer " + str(x)) for x in range(m)]
t_barber = Thread(target=barber_f, name="Barber")

t_barber.start()
[x.start() for x in t_customers]