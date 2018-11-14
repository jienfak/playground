# <a name="exercises"></a>Exercises

1) [Variables and Print](#variables-and-print)
2) [Functions](#functions)
3) [Control structures](#control-structures)
4) [Arrays](#arrays)
5) [File](#file)
6) [Text processing](#text-processing)
7) [Misc](#misc)

<br>

* For some questions, Ruby program with `raise` statements is provided to automatically test your solution in the [exercise_files](https://github.com/learnbyexample/Ruby_Scripting/tree/master/exercise_files) directory
* You can also solve these exercises on [repl.it](https://repl.it/community/classrooms/53963), with an option to submit them for review
    * or use [gitter group chat](https://gitter.im/learnbyexample/scripting_course) for discussion

<br>

## <a name="variables-and-print"></a>1) Variables and Print

**Q1a)** Ask user information, for ex: `name`, `department`, `college` etc and display them using print function

```
# Sample of how program might ask user input and display output afterwards
$ ./usr_ip.rb 
Please provide the following details
Enter your name: learnbyexample
Enter your department: ECE
Enter your college: PSG Tech

------------------------------------
Name       : learnbyexample
Department : ECE
College    : PSG Tech
------------------------------------
```

<br>

## <a name="functions"></a>2) Functions

**Q2a)** Write a function to return length of integer numbers

```ruby
>> len_int(962306349871524124750813401378124)
=> 33
>> len_int(+42)
=> 2
>> len_int(-42)
=> 2

# len_int('a') should give
TypeError (provide only integer input)
```

**Q2b)** Compare if two strings are same irrespective of case

```ruby
>> str_cmp('nice', 'nice')
=> true
>> str_cmp('how', 'who')
=> false
>> str_cmp('GoOd DaY', 'gOOd dAy')
=> true
>> str_cmp('foo', 'food')
=> false
```

**Q2c)** Compare if two strings are anagrams (assume input consists of ASCII alphabets only)

```ruby
>> str_anagram('god', 'Dog')
=> true
>> str_anagram('beat', 'table')
=> false
>> str_anagram('Tap', 'paT')
=> true
>> str_anagram('beat', 'abet')
=> true
>> str_anagram('seat', 'teal')
=> false
```

**Q2d)** Write a function to return corresponding integer or floating-point number for given number/string input

```ruby
# number input
>> num(3)
=> 3
>> num(0x1f)
=> 31
>> num(3.32)
=> 3.32

# string input
>> num('123')
=> 123
>> num('-78')
=> -78
>> num(" 42  \n ")
=> 42
>> num('3.14')
=> 3.14
>> num('3.982e5')
=> 398200.0

>> s = '56'
=> "56"
>> num(s) + 44
=> 100
```

Raise exception if input is not valid or if the input cannot be converted to a number

```ruby
# num(['1', '2.3'])
TypeError (not a valid input)

# num('foo')
ArgumentError (could not convert string to int or float)
```

<br>

## <a name="control-structures"></a>3) Control structures

**Q3a)** Write a function that returns

* 'Good' for numbers divisible by 7
* 'Food' for numbers divisible by 6
* 'Universe' for numbers divisible by 42
* 'Oops' for all other numbers
* Only one output, divisible by 42 takes precedence

```ruby
>> six_by_seven(66)
=> "Food"
>> six_by_seven(13)
=> "Oops"
>> six_by_seven(42)
=> "Universe"
>> six_by_seven(14)
=> "Good"
>> six_by_seven(84)
=> "Universe"
>> six_by_seven(235432)
=> "Oops"
```

*bonus*: use a loop to print number and corresponding string for numbers 1 to 100

```
1 Oops
2 Oops
3 Oops
4 Oops
5 Oops
6 Food
7 Good
...
41 Oops
42 Universe
...
98 Good
99 Oops
100 Oops
```

**Q3b)** Write a function that

* accepts two integers
* for all integers in the range defined by them, find all numbers that are simultaneously palindromes in decimal, binary and octal representations - for example, **585** is palindrome in all three representations
* return the result as array of arrays
* first array should contain pairs of decimal and binary numbers
* second array should contain groups of decimal, binary and octal numbers

```ruby
>> num_palindrome(6, 20)
=> [[["7", "111"], ["9", "1001"]], [["7", "111", "7"], ["9", "1001", "11"]]]
>> num_palindrome(300, 600)
=> [[["313", "100111001"], ["585", "1001001001"]], [["585", "1001001001", "1111"]]]
```

<br>

## <a name="arrays"></a>4) Arrays

**Q4a)** Write a function that returns product of all numbers of an array/range

```ruby
>> product([1, 4, 21])
=> 84
>> product([-4, 2.3e12, 77.23, 982, 0b101])
=> -3.48863356e+18
>> product([-3, 11, 2])
=> -66
>> product([8, 300])
=> 2400
>> product([234, 121, 23, 945, 0])
=> 0
>> product(1..5)
=> 120
```

**Q4b)** Write a function that returns nth lowest of an array/string. Return the lowest if second argument is not specified

*Note* that duplicates shouldn't affect determining nth lowest

```ruby
>> nums = [42, 23421341, 234.2e3, 21, 232, 12312, -2343]
=> [42, 23421341, 234200.0, 21, 232, 12312, -2343]
>> nth_lowest(nums, 3)
=> 42
>> nth_lowest(nums, 5)
=> 12312

>> nums = [1, -2, 4, 2, 1, 3, 3, 5]
=> [1, -2, 4, 2, 1, 3, 3, 5]
>> nth_lowest(nums)
=> -2
>> nth_lowest(nums, 4)
=> 3

>> nth_lowest('unrecognizable', 3)
=> "c"
>> nth_lowest('jump', 2)
=> "m"
>> nth_lowest('abracadabra', 5)
=> "r"
```

**Q4c)** Write a function that accepts a string input and returns slices

* if input string is less than 3 characters long, return an array with input string as the only element
* otherwise, return array with all string slices greater than 1 character long
* order of slices should be same as shown in examples below

```ruby
>> word_slices('i')
=> ["i"]
>> word_slices('to')
=> ["to"]

>> word_slices('are')
=> ["ar", "are", "re"]
>> word_slices('table')
=> ["ta", "tab", "tabl", "table", "ab", "abl", "able", "bl", "ble", "le"]
```

<br>

## <a name="file"></a>5) File

**Q5a)** Print sum of all numbers from a file containing only single column numbers (integer or float)

```
$ cat f1.txt 
8
53
3.14
84
73e2
100
2937

$ ./col_sum.rb 
10485.14
```

**Q5b)** Print sum of all numbers (assume only positive integer numbers) from a ASCII encoded file containing arbitrary string

```
$ cat f2.txt 
Hello123 World 35
341 2
Good 13day
How are 1784 you

$ ./extract_sum.rb 
2298
```

**Q5c)** Sort file contents in alphabetic order based on each line's extension

* extension here is defined as the string after the last `.` in the line
* if line doesn't have a `.`, those lines should come before lines with `.`
* sorting should be case-insensitive
* use rest of string as tie-breaker if there are more than one line with same extension
* assume input file is ASCII encoded and small enough to fit in memory

*bonus*: instead of printing results to stdout, change the input file itself with sorted result

```bash
$ cat f3.txt
power.Log
foo.123.txt
list
report_12.log
baz.TXT
hello.RB
loop.do.rb
Fav_books

$ ./sort_by_ext.rb
Fav_books
list
power.Log
report_12.log
hello.RB
loop.do.rb
baz.TXT
foo.123.txt
```

<br>

## <a name="text-processing"></a>6) Text processing

**Q6a)** Check if two words are same or differ by only one character (irrespective of case), input strings should have same length

See also [Levenshtein distance](https://en.wikipedia.org/wiki/Levenshtein_distance)

```ruby
>> is_one_char_diff('bar', 'bar')
=> true
>> is_one_char_diff('bar', 'Baz')
=> true
>> is_one_char_diff('Food', 'fold')
=> true
>> is_one_char_diff('A', 'b')
=> true

>> is_one_char_diff('a', '')
=> false
>> is_one_char_diff('Bar', 'Bark')
=> false
>> is_one_char_diff('Bar', 'art')
=> false
>> is_one_char_diff('Food', 'fled')
=> false
>> is_one_char_diff('ab', '')
=> false
```

**Q6b)** Check if each word of a sentence(separated by whitespace) is in ascending/descending alphabetic order or not (irrespective of case)

```ruby
>> is_alpha_order('bot')
=> true
>> is_alpha_order('AborT')
=> true
>> is_alpha_order('toe')
=> true

>> is_alpha_order('are')
=> false
>> is_alpha_order('Flee')
=> false

>> is_alpha_order('Toe got bit')
=> true
>> is_alpha_order('All is well')
=> false
>> is_alpha_order('Food is good')
=> false
```

**Q6c)** Find the maximum nested depth of curly braces

Unbalanced, empty or wrongly ordered braces should return `-1`

Hint: Iterate over string characters or use regular expressions

```ruby
>> max_nested_braces('a*b')
=> 0
>> max_nested_braces('{a+2}*{b+c}')
=> 1
>> max_nested_braces('{{a+2}*{{b+{c*d}}+e*d}}')
=> 4
>> max_nested_braces('{{a+2}*{b+{c*d}}+e}')
=> 3

>> max_nested_braces('a*b+{}')
=> -1
>> max_nested_braces('}a+b{')
=> -1
>> max_nested_braces('a*b{')
=> -1
```

<br>

## <a name="misc"></a>7) Misc

**Q7a)** Write a function that

* accepts a filesystem path(default) or a url(indicated by true as second argument)
* returns the longest word(here word is defined as one or more consecutive sequence of alphabets of either case)
* assume that input is small enough to fit in memory and that there's only one distinct longest word

```ruby
>> ip_path = 'poem.txt'
=> "poem.txt"
>> longest_word(ip_path)
=> "Violets"

>> ip_path = 'https://www.gutenberg.org/files/60/60.txt'
=> "https://www.gutenberg.org/files/60/60.txt"
>> longest_word(ip_path, true)
=> "misunderstandings"
```


<br>

<br>

<br>

*More to come*
