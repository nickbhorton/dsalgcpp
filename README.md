![example workflow](https://github.com/nickbhorton/dsalgcpp/actions/workflows/cmake-single-platform.yml/badge.svg)

*In the world of a computer science student the importance of data structures 
and algorithms is repeatedly beaten into you. To be fair, teachers and mentors 
informing us of this importance are correct. Being correct often times isn't 
pain free.*

## Implementations
### Basics
#### **Basic Stack**: `stack.h`
- Template takes type T aka the type of the elements and also a type List\<T\>.
The required method interface for `List` class is `push_front(const T&)`, 
`pop_front(const T&)` and `size_t length()`. See lists below.

| Method    |
| -------- |
| `bool push(const T&)`         |
| `T pop()`                     |
| `size_t size() const`         |

#### **Basic Queue**: `stack.h`
- Template takes type T aka the type of the elements and also a type List\<T\>. 
The required method interface for `List` class is `T push_front(const T&)`, 
`T pop_back(const T&)` and `size_t length()`. See lists below.

| Method    |
| -------- |
| `bool enqueue(const T&)`      |
| `T dequeue()`                 |
| `size_t size() const`         |

### Lists
#### **Singley Linked List**: `linked_list.h`
- Each element is allocated separately on the heap.
- Uses nodes with a value and next node unique_ptr.
- Head node is managed via unique_ptr as well

| Method    | Worst Case Complexly  |
| -------- | ------- |
| `bool push_front(const T&)`                    | $O(1)$ |
| `bool push_back(const T&)`                     | $O(n)$ |
| `bool insert(size_t, const T&)`                | $O(n)$ |
| `T pop_front()`                                | $O(1)$ |
| `T pop_back()`                                 | $O(n)$ |
| `T delete_at(size_t)`                          | $O(n)$ |
| `bool contains(const T&) const`                | $O(n)$ |
| `std::optinal<size_t> index_of(const T&) const`| $O(n)$ |
| `size_t get_length() const`                    | $O(1)$ |
| `T at(size_t) const`                           | $O(n)$ |
| `T& operator[](size_t)`                        | $O(n)$ |
| `std::string to_string(std::string_view)`      | $O(n)$ |

#### **Array List**: `linked_list.h`
- Each element is allocated continuously on the heap.
- Uses heap arrays managed by unique_ptr.

| Method    | Worst Case Complexly  |
| -------- | ------- |
| `bool push_front(const T&)`                    | $O(n)$ |
| `bool push_back(const T&)`                     | $O(n)$ |
| `bool insert(size_t, const T&)`                | $O(n)$ |
| `T pop_front()`                                | $O(n)$ |
| `T pop_back()`                                 | $O(n)$ |
| `T delete_at(size_t)`                          | $O(n)$ |
| `bool contains(const T&) const`                | $O(n)$ |
| `std::optinal<size_t> index_of(const T&) const`| $O(n)$ |
| `size_t get_length() const`                    | $O(1)$ |
| `T at(size_t) const`                           | $O(1)$ |
| `T& operator[](size_t)`                        | $O(1)$ |
| `std::string to_string(std::string_view)`      | $O(n)$ |


### Project goals
I have programmed in c++ for the mojority of my development time. This does 
not mean that I know much about c++. So this project is another opportunity to 
expand my c++ bredth. In c++ fashion I do not want to manage memory without the STL 
however, I would like to use it in a minimal way. Obviously all of the simple 
data structures I will be implementing will have the same behavior as several 
STL things. My implementations will be worse and have less features (obviously). 
This is for education, primarily mine. But my goal is to use as many 
`std::unique_ptr<T>` as nessisary to never touch `new` or `delete`.


I love Makefiles, but Makefiles are also infuriating (sometimes). I will use 
this project as a way to learn more about CMake.


My biggest developer confession is im not very good at git, this is mostly due 
to lazyness or excitement (kinda the same thing when talking coding). I will 
try to make smaller commits, and use git to a fuller extent.

### Caveat's
I may leave some enironment configs in some commits for later reference. For
example I use the clang formatter and I am still not happy with my config.


**Im sorry father for I am not very good at programming. Please forgive me.**
