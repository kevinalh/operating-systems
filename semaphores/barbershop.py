# Barbershop
from threading import *

m = 1000
n = 5 # Max amount of customers
customers = 0

mutex = Semaphore(1)
customer = Semaphore(0)
barber = Semaphore(0)
customerDone = Semaphore(0)
barberDone = Semaphore(0)


def customer_f():
    global customers
    mutex.acquire()
    if customers == n:
        print("It's full!")
        mutex.release()
        return
    else:
        customers += 1
    mutex.release()

    customer.release()
    barber.acquire()
    print("Getting haircut: There are " + str(customers) + " customers.")
    customerDone.release()
    barberDone.acquire()

    print("Done")
    mutex.acquire()
    if customers > 0:
        customers -= 1
    mutex.release()


def barber_f():
    global customers
    while True:
        barber.release()
        customer.acquire()
        print("Cutting hair")
        barberDone.release()
        customerDone.acquire()


t_customers = [Thread(target=customer_f, name="Customer " + str(x)) for x in range(m)]
t_barber = Thread(target=barber_f, name="Barber")

t_barber.start()
[x.start() for x in t_customers]