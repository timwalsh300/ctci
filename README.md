# ctci
These are my solutions to the exercises in Cracking the Coding Interview, 6th Edition.
I make no guarantees about the correctness of my code or analysis. This is just practice
for me, but might be helpful for others.

Chapter 1... Arrays

1.1: Implement an algorithm to determine if a string has all unique characters. What if you
cannot use additional data structures? The naive solution would take O(n^2)-time. My
algorithm runs in O(n)-time with O(1) additional space, but with no additional data structures
I'd be stuck with the naive solution.

1.2: Given two strings, write a method to decide if one is a permutation of the other. The
naive solution would take O(n^2) time to check each character against each character of the
other string. I do this in O(n log n)-time and no additional space.

1.3: Write a method to replace all spaces in a string with '%20.' You may assume the string
has sufficient space at the end to hold the additional characters, and that you are given
the true length of the string. The naive solution would run in O(n^2)-time to shift all the
characters two spaces to the right each time a space appears. Mine runs in O(n)-time with no
additional space.

1.4: Given a string, write a function to check if it is a permutation of a palindrome. I'm
not sure what the naive solution would be. Mine takes O(n)-time and O(n)-space.

1.5: There are three types of edits that can be performed on strings: insert, remove, or
replace a character. Given two strings, write a function to check if they are one edit
away from each other.

1.6: Implement a method to perform basic string compression using counts of repeated
characters. For example, the string aabcccccaaa would become a2bc5a3. If the compressed
string would not become smaller than the original string, your method should return
the original string. Assume only upper case and lower case letters. My solution takes
O(n)-time.

1.7: Given an image represented by an NxN matrix, where each pixel in the image is 4
bytes, write a method to rotate the image by 90 degrees. Can you do this in place? I do
this in place by transposing the matrix and then reversing the rows. I took the exercise
further by reading and writing PPM image files to actually see the rotation. I also played
around with tinting the PPM image a shade of blue.

1.8: Write an algorithm such that if an element in an MxN matrix is 0, its entire row
and column are set to 0. My solution takes O(M x N)-time and O(M + N)-space. I generate
a random matrix as a test input.

1.9: Assume you have a method isSubstring which checks if one word is a substring of
another. Given two strings, s1 and s2, write code to check if s2 is a rotation of s1
using only one call to isSubstring (e.g. "waterbottle" is a rotation of "erbottlewat").

Chapter 2... Linked-Lists

2.1: Write code to remove duplicates from an unsorted linked-list. The naive solution
would run in O(n^2)-time. Mine runs in O(n)-time with O(n) additional space.

2.2: Implement an algorithm to find the kth to last element of a singly linked list.

2.3: Implement an algorithm to delete a node in the middle (not the head or tail) of
a singly linked list, given only access to that node.
