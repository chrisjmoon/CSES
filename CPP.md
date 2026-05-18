a **keyword** is a token that the language reserves for its own grammar; reserved means that you cannot use it as an identifier

preprocessor?

---


# Constants and Strings

a **constant** is a value that cannot be changed; there are two types of constants:
- **named constants**: constant values that are associated with an identifier
- **literal constants**: constant values that are not associated with an identifier

purpose of const
- reduces chance of bugs
- compiler optimizations
- reduce overall complexity; when determining what section of a code is doing or trying to debug an issue, we don't have to worry about const variables

three ways to define a named constant are
- constant variables
- object-like macros with substitution text (#define MAX_STUDENTS 30)
- enumerated constants

a constant variable can be declared before or after a variable's type but standard convention follows before | initializer of a const variable can be non-constant

```
const double gravity {9.8};
```

little point in declaring a value parameter as const as the variable is already a copy and only lives for the scope of the function; const by-value parameters are ignored for function declarations, meaning no overloading on the different

```
void foo(const int x); // x is already a copy
void foo(int x); // same function signature
```

a function should not declare its return type as const as the caller already receives a separate returned value

```
string make_name() {
    string s = "Alice";
    return s;
}

string name = make_name(); // name is separate from s in make_name
```

prefer constants over macros
- constants have type
- constants obey scope
- macros can cause hairy bugs

a **type qualifier** is a keyword that is applied to a type that modifies how that type behaves; there are only two type qualifiers as of C++ 23: const and volatile | the volatile qualifier informs the compiler that an object may have its value changed at any time; prevents certain optimizations like caching the value in a register

---


**const v. constexpr**
purpose?
compile time constants allow the compiler to know their value while compiling the program; this is useful for array sizes, case labels, template arguments, and optimization

```
constexpr int size = 10;
int arr[size]; // array size must be compile time constant

constexpr int quit = 0;
switch (choice) {
    case quit: // case label must be compile time constant
        break;
}
```
