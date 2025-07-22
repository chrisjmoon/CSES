# Containers

unordered_set
    average time complexity O(1)
    worst time complexity O(n)
    vulnerable to hash collision

set
    red-black tree (balanced BST)
    average time complexity O(log n)
    worst time complexity O(log n)
    stable performance consistency

multiset
    - associative container (elements referred to by keys, used to query membership, as opposed to indices)
    - set with duplicates
    - implemented using red-black tree
    - insertion, removal, search have logarithmic complexity
    - supports lower/upper_bound
        - cannot grab the index using ms.upper_bound(x) - ms.begin() | vectors use random-access iterators (like pointers); multiset and set use bidirectional iterators which support ++it and --it but not it2 - it1

# Statistics

Given a set of numbers x[], argmin_t |x_i - t| is when t = median(x)


