# What are Sequences?
Infinite sequences are infinite sets of numbers in a particular order sharing a method of formulation. They are always **analytical** meaning that they have to be formulated by indexing or recursion.
## Indexing
The term $y_n$ is described in relation to a position/ index $n$, which represents any positive natural number. For example the piecewise equation:
$$
n \in \mathbb{Z}^+,\space n>0, \space y_n = \begin{cases}
{1 \over n} \text{ if } n = 2k \\
n \text{ if } n = 2k+1
\end{cases}
$$
This equation can be preferably rewritten without the piecewise using the terms $a$ and $b$
$$
y_n = a {n \over 2} + b {1 \over 2n}, \space a = 1-(-1)^n, \space b = 1+(-1)^n
$$
$$
y_n = {n[1 - (-1)^n] \over 2} + {1 + (-1)^n \over 2n}
$$
## Recursion
A recursive sequence describes first terms and the method by which further terms are constructed. For example the Fibonacci sequence:
$$
y_1 = 1, \space y_2 = 1, \space y_n = y_{n-1} + y_{n-2}
$$
# Bounded Sequences
A sequence is **bounded** if it is not infinite, starting with lower bound $A$ and ending with upper bound $B$. Some sequences exhibit behaviour depending on the bounds: $A \le y_n \le B$ (**non-decreasing**) or $A \ge y_n \ge B$ (**non-increasing**). When a sequence is either non-increasing or non-decreasing it is considered **monotonic**. When a sequence is both bounded and monotonic it is also **asymptotic** meaning it converges to a limit.

## Limit Transition
Limit transition is the operation behind differentiation and integration. The definition of limit transition is "The number $a$ is said to be the limit of a sequence $y_n$ if for any positive number $\epsilon$ there is a real number $N$ such that all $n > N$ continues to hold the equality $|y_n-a|<\epsilon$."
For any $\epsilon >0$ there is a number $n > N$  where $n$ is the sequence position. It is necessary that for any $\epsilon$ a certain number $N$ should exist. Limit transition narrows a sequence down so as $\epsilon$ decreases to $0$, $N$ increases to $\infty$.
