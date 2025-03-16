''' Python - Scopes and Closures
Code based on Code from GeeksforGeeks [https://www.geeksforgeeks.org/python-closures] | [https://www.geeksforgeeks.org/python-scope-of-variables/]
'''

## Define functions of inner and outer.
def outer_function(x):
    def inner_function(y):
        return x + y #Note 'x' is captured in the outer scope.

closure_instance = outer_function(5)
result = closure_instance(3)
print(result) # Output: 8

def create_counter():
    count = 0
    def increment():
        nonlocal count # have to specify nonlocal to modify the outer scope variable.
        count += 1
        return count
    return increment

counter = create_counter()
print(counter()) # First Count: 1
print(counter()) # Second Count: 2
print(counter()) # Third Count: 3