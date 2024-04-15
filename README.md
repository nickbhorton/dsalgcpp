In the world of a computer science student the importance of data structures 
and algorithms is repeatedly beaten into you. To be fair, teachers and mentors 
informing on this importance are correct. Correctness doesn't imply painless.

### Implementations
#### **Singley Linked List**: `linked_list.h`
- Each node is allocated separately on the heap.

| Method    | Worst Case Complexly  |
| -------- | ------- |
| `bool push_front(const T&)`                    | $O(1)$ |
| `bool push_back(const T&)`                     | $O(n)$ |
| `T pop_front()`                                | $O(1)$ |
| `T pop_back()`                                 | $O(n)$ |
| `T delete_at(size_t)`                          | $O(n)$ |
| `bool contains(const T&) const`                | $O(n)$ |
| `std::optinal<size_t> index_of(size_t) const`  | $O(n)$ |
| `size_t get_length() const`                    | $O(1)$ |
| `T at(size_t) const`                           | $O(n)$ |
| `T& operator[](size_t)`                        | $O(n)$ |


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
