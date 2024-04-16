#ifndef ARRAY_LIST_HEADER
#define ARRAY_LIST_HEADER
#include <algorithm>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>

template <typename T> class ArrayList
{
    size_t cap_;
    size_t length_;
    std::unique_ptr<T[]> data_;

    void double_capacity()
    {
        std::unique_ptr<T[]> p(new T[cap_ * 2]);
        for (size_t i = 0; i < length_; i++) {
            p[i] = data_[i];
        }
        data_ = std::move(p);
        cap_ = cap_ * 2;
    }

public:
    ArrayList() : cap_(), length_(), data_()
    {
        std::unique_ptr<T[]> p(new T[1]);
        data_ = std::move(p);
        length_ = 0;
        cap_ = 1;
    }
    ArrayList(ArrayList&& other)
    {
        data_ = std::move(other.data_);
        cap_ = other.cap_;
        length_ = other.length_;
        other.cap_ = 0;
        other.length_ = 0;
    }
    ArrayList& operator=(ArrayList&& other)
    {
        data_ = std::move(other.data_);
        cap_ = other.cap_;
        length_ = other.length_;
        other.cap_ = 0;
        other.length_ = 0;
        return *this;
    };

    // Deleted copy stuff for now
    ArrayList(const ArrayList& other) = delete;
    ArrayList& operator=(const ArrayList& other) = delete;

    bool insert(size_t index, const T& new_data)
    {
        if (length_ + 1 >= cap_) {
            double_capacity();
        }
        if (index > length_) {
            throw std::out_of_range("array list index out of range");
        } else if (index == length_) {
            data_[length_] = new_data;
        } else {
            T temp = data_[index];
            for (size_t i = index; i < length_; i++) {
                int save = data_[i + 1];
                data_[i + 1] = temp;
                temp = save;
            }
            data_[index] = new_data;
        }
        length_++;
        return true;
    }

    bool push_front(const T& new_data) { return insert(0, new_data); }

    bool push_back(const T& new_data) { return insert(length_, new_data); }

    T delete_at(size_t index)
    {
        if (index >= length_ || length_ == 0) {
            throw std::out_of_range("linked list index out of range");
        }
        T save = data_[index];
        for (size_t i = index; i < length_ - 1; i++) {
            data_[i] = data_[i + 1];
        }
        length_--;
        return save;
    }

    T pop_front() { return delete_at(0); }

    T pop_back() { return delete_at(length_ - 1); }

    bool contains(const T& value) const
    {
        for (size_t i = 0; i < length_; i++) {
            if (data_[i] == value) {
                return true;
            }
        }
        return false;
    }

    std::optional<size_t> index_of(const T& value) const
    {
        for (size_t i = 0; i < length_; i++) {
            if (data_[i] == value) {
                return i;
            }
        }
        return {};
    }

    /// accessors
    size_t length() const { return length_; }

    T at(size_t index) const
    {
        if (index >= length_) {
            throw std::out_of_range("linked list index out of range");
        }
        return data_[index];
    }

    /// @breif Does not perform range checks. Will segfault if index is wrong.
    T& operator[](size_t index) { return data_[index]; }

    std::string to_string(std::string_view sep = " ") const
    {
        std::stringstream ss;
        if (length_ > 0) {
            for (size_t i = 0; i < length_ - 1; i++) {
                ss << data_[i] << sep;
            }
            ss << data_[length_ - 1];
        }
        return ss.str();
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const ArrayList<T>& ll)
{
    os << ll.to_string(" ");
    return os;
}
#endif
