# Tests

1. bad input

    * missing arguments
    * nonexistent file or directory
    * extra arguments (besides -q)
    * wrong order of parameters (ex: ./main lengths.txt 15 -q)
    * wrong letter for quiet parameter (ex: typing -a instead of -q)

    - for testing if the program reliably detects a bad input and terminates early

2. invalid length

    * length <= 0
        - lengths of 0 or less do not make sense, so program should detect this
    * length > MAX_INT
        - program should detect to prevent bugs or crashes from integer overflow

3. input file tests

    * different file types
        - to test if any file types cause crashes or unintended behavior
    * blank lines and lines starting with # are ignored
        - testing if program actually ignores these lines
    * empty file
        - if passes above test, this should pass
    * duplicate lengths
        - test to make sure only one of the lengths is used by the program
    * negative lengths
        - does not make sense, so it should be detected
    * negative prices
        - testing for logical errors. lengths with negative prices shouldn't be picked
    * non-number symbols
        - testing detection of bad input
    * more than 2 numbers on one line, such as: 1, 2, 3
        - also testing detection of bad input
    * formatting:
        * 1, 2
        * 1,2
        * 1,     2
        * 1   ,   2
        * 1   ,2
        *   1, 2
        - test to see if program ignores whitespace
        
        * 1,2,
        * 1,,2
        * ,1,2
        * 1 2
        - test to see if commas are also ignored

4. other cases

    * all prices are 0 or negative
        - all 0: no cuts, 0 profit, and remainder == initial length
        - all negative: same?
    * rod too small for any cut
        - similar output to all prices being 0
    * lengths are shuffled
        - testing if results are not affected by the order of lengths given
        - exception for duplicates: the first length read is the one chosen and subsequent dupes are ignored
            * (meaning the order would matter here)
    * multiple solutions give same profit
        - test if one is reliably picked, not random

5. output validation

    * including "-q" in command line, in correct place
        - expected result: program runs like normal, but prompt for rod length does not display. can still input values and calculate them

    * lengths:
        - 1, 1
        - 2, 5
        - 3, 8
        - 4, 9
        - 5, 10
        - 6, 17
        - 7, 17
        - 8, 20
    * rod length = 8
    * expected result:
        - cuts: 1 @ 2, 1 @ 6
        - value = 22
        - remainder = 0

    * lengths:
        - 1, 3
        - 2, 5
        - 3, 8
        - 4, 9
        - 5, 10
        - 6, 17
        - 7, 17
        - 8, 20
    * rod length = 8
    * expected result:
        - cuts: 8 @ 1
        - value = 24
        - remainder = 0

    * lengths:
        - 1, 2
        - 2, 5
        - 3, 7
        - 4, 8
    * rod length = 5
    * expected result:
        - cuts: 1 @ 2, 1 @ 3
        - value = 12
        - remainder = 0

    * lengths:
        - 3, 5
    * rod length = 11
    * expected result:
        - cuts: 3 @ 3
        - value = 15
        - remainder = 2
    
    * lengths:
        - 1, -1
        - 2, 1
    * rod length = 5
    * expected result:
        - cuts: 2 @ 2
        - value = 2
        - remainder = 1
