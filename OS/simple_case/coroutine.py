# generator function
def coroutine_example():
    print("Start coroutine")
    x = yield
    print(f"Received {x}")
    y = yield x + 1  # noting that 11 is the return value of yield, but not catch or use. so it won't be used. 
    print(f"Received {y}")

# using coroutine
co = coroutine_example()
value0 = next(co)  # start coroutine, run until the first yield
print(f"Yield returned: {value0}")

value = co.send(10)  # keep running, send 10 to coroutine, should be received by x. return the next yield value, 11
print(f"Yield returned: {value}")
try:
    co.send(20) # co.send 20 to y, no yield after, so we don't have yield value anymore
except StopIteration:
    print("Coroutine has finished execution")

# Start coroutine
# Received 10
# Yield returned: 11
# Received 20
# Coroutine has finished execution #