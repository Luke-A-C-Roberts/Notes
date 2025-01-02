# Iterators and Itertools

## Python Iterators

Iterators and iterables are one of my favourite features of the python language, for several important reasons. Whenever we deal with lists, arrays and other structures within projects, the first instinct is to use for and while loops to accomplish tasks over many items. While old trusty imperitive loops is the most intuitive for both newcomers and experienced devs alike, migrating from this style to a more functional and array oriented style improves code clarity and efficiency while decreasing cognative load on the programmer. Iterables are defined by having a `__iter__` magic method/ protocol which converts the collection into an iterator. Iterators have both a `__iter__` and `__next__` protocol, where the latter yields the next item out of the iterator until the `StopIteration` error is raised signifying that all items have been consumed. Because of the abstract interfacing requirements, it means iterators are a subset of iterables. Iterators also fully consume items so that once `__next__` has been called the item within the iterator is used. In practical terms if you store and use an iterator somewhere then used again, no more items will be returned. This feature may be usefull if you want to consume some of the items but not all.

### On Clarity

This is probably the most contravertial benifit of using iterators in your code. In some ways using higher order iterator functions may make a lot of sense to you programming at the time, but much more difficult for some one else or you in the future to read. This coaleces when writing particularly long and complicated one liners with many iterator functions being chained together as it is unclear what is acually happening to the data. This can make for programs that are difficult to debug or read. However, if not too heavily combined, iterators make for very clear code by abstracting away things like array access and calculations which are both more verbose and more easily implemented incorrectly. This is aided by good documentation and good naming of iterator functions.

### On Efficiency

There are two types of efficiency. Efficiency of writing code and efficiency of running code. For all of the same reasons on clarity, with all of the strengths and drawbacks, using iterators also effects speed of writing code. Iterators in python are what is refered to in the functional programming world as lazily evaluated althogh to a lesser degree. In essence when an iterator function takes an iterable as an argument, the operation performed on that iterator does not evaluate until the values are needed, such as using `list()` or as the iterator in a for loop. This is most pronounced with infinate iterators where fully instanciating them would never finish executing in some contexts.

## Implementing iterables and iterators

While not always necessary to implement your own iterables and iterators, it is nevertheless a tool at your disposal. 

### Implementing iterables

If you have a class that specifies something in a list it is an option to use a `__iter__` so you can later loop over the options. For example, I was recently implementing a set of resnet models where I described their layer architecture using classes with lists of sub classes. I found it convenient use an iterator method to loop over all of the specification items so I could later use them in model construction.

Code Snippet:
```python
@dataclass(frozen=True)
class LayerSpec(Iterable):
    kernel_size: int
    filters: int

    def __iter__(self) -> Iterator:
        return iter([self.kernel_size, self.filters])


@dataclass(frozen=True)
class MultiLayerSpec(Iterable):
    layer_specs: list[LayerSpec]
    repetitions: int
    use_strides: bool = True

    def __iter__(self) -> Iterator:
        return iter(map(tuple, self.layer_specs))

    def __len__(self) -> int:
        return len(self.layer_specs)
```

### Implementing Iterators

By implementing both a `__iter__` and `__next__` method, it is also possible to construct an iterator. I have not yet found a use for them.

Basic example:
```python
class ListIterator(Iterator):
    def __init__(self, l: list[any]) -> None:
        self._list = l
        self._index = 0
        self._length = len(l)

    def __iter__(self) -> 'ListIterator':
        return self

    def __next__(self) -> any:
        if self._index < self._length:
            self._list[self._index]
            yield self._list[self._index]
        else:
            raise StopIteration()
```

## Commonly used iterator functions

### Basic iterator functions and objects.

One of the earliest functions encountered is the `range` function as it is often in for loops (although I am increasingly not using it). The `range` function is considered a iterator generator function because it creates new values. Its arguments are start, \[stop\], \[step\], creating a numeric range.

`zip` is another basic iterator function that takes iterables and combines them element wise in a tuple: `zip([a¹,a²,a³,...], [b¹,b²,b³,...])` → `[(a¹,b¹),(a²,b²),(a³,b³),...]`.

`enumerate` combines both `range` and `zip`, zipping together an index for each item with items from an iterable.

`sorted` sorts a iterable if the items of the iterable support a `__lt__` or `__gt__` protocol. The function also supports a `key=` keyword, where a comparisson function can be used to overwrite the default sorting procedure.

`reversed` reversed a iterable or iterator. Nothing more to tell.

```python
[*range(4, 10)]
>>> [4,5,6,7,8,9]

[*zip([1,2,3],[4,5,6])]
>>> [(1,4),(2,5),(3,6)]

[*enumerate(['a','b','c'])]
>>> [(1,'a'),(2,'b'),(3,'c')]

[*sorted([6,2,3,8])]
>>> [2,3,6,8]

[*sorted([(5,2),(8,1),(6,3)], key=lambda x, y: x[1] < y[1])]
>>> [(8,1),(5,2),(6,3)]

[*reversed(range(10))]
>>> [9,8,7,6,5,4,3,2,1,0]
```

### The trinity
The holy trinity of basic array functions are `map`, `filter` and `reduce`, used a lot in datascience for dataset transformations. Python provides in-build support (`reduce` in `functools`).

`map` is a higher order function that applies a inner function to all of the items. You can use it instead of list composition or for loops where you modify each item by index. The expectation is that you will end up with a `map` iterator that contatins the same number of items as the inputed iterable.

`filter` applies a function to each item, and if the returned item is truthy, the original item is retained. If the returned item is falsy then it is dropped from the items in the returned iterator. The output `filter` iterator contains the same number of items in the input iterable (if all returns are truthy) or less than the number of items if some are dropped.

`reduce` applies a function between each item in the input iterable. If the input iterator is N-dimentional then the output iterator should be (N-1)-dimentional. For single 1D lists reduce returns a single item. The input function must have 2 arguments for the result of all previous item reductions and the next item to reduce. Reduce also provides a third optional argument that is used as the first item. If it is not provided the first item is simply the first item of the input iterable. Reduce is good when you would otherwise continously update a single value using an array. Many binary functions that perform numeric operations can be found in the `operator` module

```python
increment = lambda x: x + 1
[*map(increment, range(1,5))]
>>> [2,3,4,5]

even = lambda x: x % 2 == 0
[*filter(even, range(10))]
>>> [0,2,4,6,8]

add = lambda x, y: x + y
reduce(add, [*range(4)])
# (((0 + 1) + 2) + 3)
>>> 6
```

## Itertools

The itertools library provides more advanced tools to manipulate or create iterator streams. Itertools is broadly split into infinate, finite and combinatory iterators.

### Infinate iterators

The three infinite iterators are:
- `count(start, [step])`
- `cycle(p)`
- `repeat(elem [,n])`

These should be used very carefully since creating a list of an infinite iterator will definately crash your program. Generally you only want to use these in a for loop and break after a certain point.

`count` is the infinite version of `range`, having a start and step but no stop. this means you must stop it explicitly when iterating through the items.

`cycle` repeats a iterable infinitely in a cycle of items.

`repeat` can be both a infinate and finite iterator depending on whether the last `n=` parameter is filled or not. If it is not a single value will be repeated indefinately, while if `n=` is provided then the value will be iterated N times.

```print
# This will break your code because it is unbound
[*count(0,1)]

# This is fine
for i in count(0, 1):
    if i >= 10: break
    print(i, end=", ")
>>> 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

l = ["a","b","c"]
for v, i in zip(cycle(l)):
    if i >= 10: break
    print(i, end=", ")
>>> a, b, c, a, b, c, a, b, c, a,

# infinite
print("infinite: ", end="\t")
for (v, i) in zip(repeat(3), count()):
    if i >= 10: break
    print(v, end=", ")
>>> 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,

# finite
print("\nfinite: ", end="\t")
for v in repeat(3, 10):
    print(v, end=", ")
>>> 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
```

### Finite iterators
There are many more finite iterators that apply something to a pre-existing iterable. Often they involve applying a function to something and some of them are enhanced versions of more basic python iterator functions. I personally organise these iterators into 4 groups.

- Data manipulation
    - `accumulate(p [,func])`
    - `starmap(func, seq)`

- Data joining and splitting
    - `chain(p, q, ...)`
    - `chain.from_iterable(iterable)`
    - `tee(it, n)`
    - `zip_longest(p, q, ...)`

- Data grouping/ distributing
    - `batched(p, n) !!coming soon`
    - `groupby(iterable [,key])`
    - `pairwise(iterable)`

- Data filtering
    - `compress(data, selectors)`
    - `dropwhile(pred, seq)`
    - `filterfalse(pred, seq)`
    - `islice(seq, start, stop, [,step])`
    - `takewhile(pred, seq)`

`accumulate` is similar to `sum` except that it keeps intermediate values. If a function is given it acts like `reduce` but keeping intermediates

`starmap` as the name implies maps a function simmilar to `map`. However `map` only works on the highest level of an iterator if its nested, so that the function applied only takes one input parameter. `starmap` can be useful when each item of the iterator being worked on containes nested values, because it can apply a multi-parameter function on all the items of the inner iterable.

`chain` appends two or more other iterables together and treats them as a singe iterable.

```python
# Accumulate
seq = list(range(10))
print(f"seq = {seq}")
print(f"accumulation = {list(accumulate(seq))}")
print(f"mult accumulation = {list(accumulate(seq[1:], lambda x, y: x * y))}")

>>> seq = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
>>> accumulation = [0, 1, 3, 6, 10, 15, 21, 28, 36, 45]
>>> mult accumulation = [1, 2, 6, 24, 120, 720, 5040, 40320, 362880]

# Starmap
seq = list(map(lambda v: chr(v), range(65, 75)))
print(f"seq              = {seq}")
print(f"pairwise         = {list(pairwise(seq))}")
print(f"pairwise+starmap = {list(starmap(lambda a, b: ''.join([a, b]), pairwise(seq)))}")

>>> seq = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
>>> pairwise = [('A', 'B'), ('B', 'C'), ('C', 'D'), ('D', 'E'), ('E', 'F'), ('F', 'G'), ('G', 'H'), ('H', 'I'), ('I', 'J')]
>>> pairwise+starmap = ['AB', 'BC', 'CD', 'DE', 'EF', 'FG', 'GH', 'HI', 'IJ']

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

