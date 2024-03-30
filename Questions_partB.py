#9
fact = lambda n: [1,0][n>1] or fact(n-1)*n
print(fact(46))

#10
from functools import reduce
concat_strings = lambda lst: reduce(lambda x, y: x + ' ' + y, lst)
strings = ["Hello", "world", "this", "is", "Task", "number", "10"]
print(concat_strings(strings))

#11
def cumulative_sum_of_squares(lst):
    return list(map(lambda sublist: (
        lambda squares: (
            lambda even_squares: (
                lambda cumulative_sum: cumulative_sum
            )(sum(even_squares))
        )(filter(lambda square: square % 2 == 0, squares))
    )(map(lambda num: num**2, sublist)), lst))

print(cumulative_sum_of_squares([[1, 2, 3], [4, 5, 6], [7, 8, 9]]))

#12
nums = [1, 2, 3, 4, 5, 6]
sum_squared = reduce(lambda x, y: x + y, map(lambda x: x**2, filter(lambda x: x % 2 == 0, nums)))
print(sum_squared)

#13
def count_palindromes(lst):
    return list(map(lambda sublst: reduce(lambda acc, x: acc + 1 if x == x[::-1] else acc,filter(lambda x: isinstance(x, str), sublst), 0), lst))
print(count_palindromes([['madam', 'hello', 'level'], ['racecar', 'python', 'cat'], ['radar', 123, 'civic']]))
