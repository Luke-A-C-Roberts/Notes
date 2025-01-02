```python
# https://docs.python.org/3/library/itertools.html
from itertools import *
from functools import reduce
```

# Infinite Iterators

The three infinite iterators are:
- count(start, [step])
- cycle(p)
- repeat(elem [,n])

These should be used very carefully since creating a list of an infinite iterator
will definately crash your program. Generally you only want to use these in a
for loop and break after a certain point.


```python
# Count

# count is the infinite version of range, having a start and step but no stop.
# this means you must stop it explicitly
for i in count(0, 1):
    if i >= 10: break
    print(i, end=", ")
```

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 


```python
# Cycle

# cycle repeats a list infinitely
# again you need to break the loop.
# here I have zipped it with count so that we have an iteration index to break by
for (v, i) in zip(cycle(["A","B","C"]), count()):
    if i >= 10: break
    print(v, end=", ")
```

    A, B, C, A, B, C, A, B, C, A, 


```python
# Repeat

# repeat can be infinite or not depending on if you specify an [n] parameter
# it simply repeats the same value

# infinite
print("infinite: ", end="\t")
for (v, i) in zip(repeat(3), count()):
    if i >= 10: break
    print(v, end=", ")

# finite
print("\nfinite: ", end="\t")
for v in repeat(3, 10):
    print(v, end=", ")

# finite repetition is often redundant since the same thing can be achieved by
# multiplying a sequence, although I havent investigated if it is more efficient
print("\nusing *: ", end="\t")
for v in [3] * 10:
    print(v, end=", ")
```

    infinite: 	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
    finite: 	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
    using *: 	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 

# Finite iterators

There are many more finite iterators that apply something to a pre-existing list.
Often they involve applying a function to something.

There are 14 finite iterators in total:
- accumulate(p [,func])
- batched(p, n) !!coming soon
- chain(p, q, ...)
- chain.from_iterable(iterable)
- compress(data, selectors)
- dropwhile(pred, seq)
- filterfalse(pred, seq)
- groupby(iterable [,key])
- islice(seq, start, stop, [,step])
- pairwise(iterable)
- starmap(func, seq)
- tee(it, n)
- zip_longest(p, q, ...)


```python
# Accumulate

# accumulate is similar to sum() except that it keeps intermediate values
# if a function is given it acts like functools.reduce() but keeping intermediates

seq = list(range(10))
print(f"seq = {seq}")

print(f"accumulation = {list(accumulate(seq))}")

print(f"mult accumulation = {list(accumulate(seq[1:], lambda x, y: x * y))}")
```

    seq = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    accumulation = [0, 1, 3, 6, 10, 15, 21, 28, 36, 45]
    mult accumulation = [1, 2, 6, 24, 120, 720, 5040, 40320, 362880]



```python
# Chain

# chain appends two other iteraterable together and
# treats them as a singe iterable

print("chain(range(10), range(10)):")
print(list(chain(range(10), range(10))))

# chain.from_iterable worrks the same but from a list of iterables, rather than
# the variadic *iterables in regulat chain

print("\nchain.from_iterables([range(10), range(10)]):")
print(list(chain.from_iterable([range(10), range(10)])))
```

    chain(range(10), range(10)):
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    
    chain.from_iterables([range(10), range(10)]):
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]



```python
# Compress

# compress takes a data sequence and compares it to a selector sequence.
# if a value in the selector sequence returns True then the value in the
# data sequence is outputted.

data = list(range(10))
selector = [0, 1, 0, 1, 1, 0, 1, 0, 0, 1]

print(f"data     = {data}")
print(f"selector = {selector}")
print(f"compress = {list(compress(data, selector))}")
```

    data     = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    selector = [0, 1, 0, 1, 1, 0, 1, 0, 0, 1]
    compress = [1, 3, 4, 6, 9]



```python
# Dropwhile

# dropwhile drops all the values in a sequence until a condition is met
# then the remainder of the input sequence is given

seq = list(range(10))
print(f"seq           = {seq}")
print(f"dropwhile < 6 = {list(dropwhile(lambda x: x < 6, seq))}")
```

    seq           = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    dropwhile < 6 = [6, 7, 8, 9]



```python
# Filterfalse

# filter false is the exact opposite of normal python filter,
# meaning the values that match a predicate are dropped

seq = list(range(10))
print(f"seq               = {seq}")
print(f"filter x % 2 == 0 = {list(filter(lambda x: x % 2 == 0, seq))}")
print(f"filterfalse       = {list(filterfalse(lambda x: x % 2 == 0, seq))}")
```

    seq               = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    filter x % 2 == 0 = [0, 2, 4, 6, 8]
    filterfalse       = [1, 3, 5, 7, 9]



```python
# Groupby

# groupby seperates values into groups either as a singular instance or a whole group
# of the same thing depending on which value from the output zip you select
k = groupby('AAAABBBCCDAABBB')
print(f"values = {list(map(lambda v: v[0],k))}")

k = groupby('AAAABBBCCDAABBB')
print(f"values = {list(map(lambda v: list(v[1]),k))}")
```

    values = ['A', 'B', 'C', 'D', 'A', 'B']
    values = [['A', 'A', 'A', 'A'], ['B', 'B', 'B'], ['C', 'C'], ['D'], ['A', 'A'], ['B', 'B', 'B']]



```python
# Islice

# islice slices an iterable depending on the number of arguments given

seq = list(range(10))
print(f"seq                  = {seq}")
print(f"islice up to 4       = {list(islice(seq, 4))}")
print(f"islice from 2 to 4   = {list(islice(seq, 2, 4))}")
print(f"islice from 2        = {list(islice(seq, 2, None))}")
print(f"islice from 2 step 2 = {list(islice(seq, 2, None, 2))}")
```

    islice up to 4       = [0, 1, 2, 3]
    islice from 2 to 4   = [2, 3]
    islice from 2        = [2, 3, 4, 5, 6, 7, 8, 9]
    islice from 2 step 2 = [2, 4, 6, 8]



```python
# Pairwise

# pairwise simply pairs each value together with the next one and returns a zip

seq = list(map(lambda v: chr(v), range(65, 75)))
print(f"seq      = {seq}")
print(f"pairwise = {list(pairwise(seq))}")
```

    seq      = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
    pairwise = [('A', 'B'), ('B', 'C'), ('C', 'D'), ('D', 'E'), ('E', 'F'), ('F', 'G'), ('G', 'H'), ('H', 'I'), ('I', 'J')]



```python
# starmap

# starmap applies a function to a prezipped list of values

seq = list(map(lambda v: chr(v), range(65, 75)))
print(f"seq              = {seq}")
print(f"pairwise         = {list(pairwise(seq))}")
print(f"pairwise+starmap = {list(starmap(lambda a, b: ''.join([a, b]), pairwise(seq)))}")
```

    seq              = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
    pairwise         = [('A', 'B'), ('B', 'C'), ('C', 'D'), ('D', 'E'), ('E', 'F'), ('F', 'G'), ('G', 'H'), ('H', 'I'), ('I', 'J')]
    pairwise+starmap = ['AB', 'BC', 'CD', 'DE', 'EF', 'FG', 'GH', 'HI', 'IJ']



```python
# Takewhile

# takewhile drops all the values in a sequence after a condition is met
# then the remainder of the input sequence is given

seq = list(range(10))
print(f"seq           = {seq}")
print(f"takewhile < 6 = {list(takewhile(lambda x: x < 6, seq))}")
```

    seq           = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    takewhile < 6 = [0, 1, 2, 3, 4, 5]



```python
# Tee

# Not the drink, tee duplicates iterators and puts them in a tuple.
# this is useful for manipulating seperate iterator copies

(a, b) = tee(range(10), 2)
print(list(a))
print(list(b))
```

    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]



```python
# Zip Longest

# zip_longest takes two sequnces of differing length and zips them.
# the shorter iterator gets substituted for a fill value at the end.

a = [1, 2, 3]
b = [5, 4, 3, 2, 1]

print(f"a           = {a}")
print(f"b           = {b}")
print(f"zip_longest = {list(zip_longest(a, b, fillvalue=0))}")
```

    a           = [1, 2, 3]
    b           = [5, 4, 3, 2, 1]
    zip_longest = [(1, 5), (2, 4), (3, 3), (0, 2), (0, 1)]

