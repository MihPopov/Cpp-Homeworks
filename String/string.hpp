#pragma once

#include <iostream>
#include <cstring>
#include <algorithm>

// YOUR CODE HERE
class String {
public:

    // Constructors, Destructor
    String(const char* str) {
        size = std::strlen(str);
        capacity = size * 2 + 1;
        data = new char[capacity];
        std::strcpy(data, str);
    }
    String(size_t n, char c) {
        size = n;
        capacity = 2 * n + 1;
        data = new char[capacity];
        std::fill(data, data + n, c);
        data[n] = '\0';
    }
    String() {
        size = 0;
        capacity = 1;
        data = new char[capacity];
        data[0] = '\0';
    }
    String(const String& str): size(str.size), capacity(str.capacity) {
        data = new char[capacity];
        std::copy(str.data, str.data + size + 1, data);
    }
    ~String() {
        delete[] data;
    }

    //Operators, String and String
    bool operator==(const String& other) const {
        if (size != other.size) return false;
        return std::strcmp(data, other.data) == 0;
    }
    bool operator!=(const String& other) const {
        return !(*this == other);
    }
    bool operator<(const String& other) const {
        return std::strcmp(data, other.data) < 0;
    }
    bool operator>(const String& other) const {
        return std::strcmp(data, other.data) > 0;
    }
    bool operator<=(const String& other) const {
        return !(*this > other);
    }
    bool operator>=(const String& other) const {
        return !(*this < other);
    }

    //Operators, String and Char*
    bool operator==(const char* other) const {
        return std::strcmp(data, other) == 0;
    }
    bool operator!=(const char* other) const {
        return !(*this == other);
    }
    bool operator<(const char* other) const {
        return std::strcmp(data, other) < 0;
    }
    bool operator>(const char* other) const {
        return std::strcmp(data, other) > 0;
    }
    bool operator<=(const char* other) const {
        return !(*this > other);
    }
    bool operator>=(const char* other) const {
        return !(*this < other);
    }

    //Operators, Char* and String
    friend bool operator<(const char* lhs, const String& rhs) {
        return std::strcmp(lhs, rhs.data) < 0;
    }
    friend bool operator>(const char* lhs, const String& rhs) {
        return std::strcmp(lhs, rhs.data) > 0;
    }
    friend bool operator==(const char* lhs, const String& rhs) {
        return std::strcmp(lhs, rhs.data) == 0;
    }
    friend bool operator!=(const char* lhs, const String& rhs) {
        return !(lhs == rhs);
    }
    friend bool operator<=(const char* lhs, const String& rhs) {
        return !(lhs > rhs);
    }
    friend bool operator>=(const char* lhs, const String& rhs) {
        return !(lhs < rhs);
    }

    //Operator []
    char& operator[](size_t index) {
        return data[index];
    }
    const char& operator[](size_t index) const {
        return data[index];
    }

    //Operator =
    String& operator=(const String& other) {
        if (this == &other) return *this;
        if (capacity >= other.size + 1) std::strcpy(data, other.data);
        else {
            char* newData = new char[other.capacity];
            std::strcpy(newData, other.data);
            delete[] data;
            data = newData;
            capacity = other.capacity;
        }
        size = other.size;
        return *this;
    }

    //Operator +=
    String& operator+=(const String& other) {
        if (this == &other) {
            String copy(other);
            return *this += copy;
        }
        size_t new_size = size + other.size;
        if (new_size + 1 > capacity) {
            capacity = 2 * new_size + 1;
            char* new_data = new char[capacity];
            std::strcpy(new_data, data);
            delete[] data;
            data = new_data;
        }
        std::strcat(data, other.data);
        size = new_size;
        return *this;
    }
    String& operator+=(const char* c) {
        String temp(c);
        return *this += temp;
    }
    String& operator+=(char c) {
        PushBack(c);
        return *this;
    }

    //Operator +
    String operator+(const String& other) const {
        String result(size + other.size, '\0');
        std::copy(data, data + size, result.data);
        std::copy(other.data, other.data + other.size, result.data + size);
        result.data[result.size] = '\0';
        return result;
    }
    String operator+(char c) const {
        String result(*this);
        result += c;
        return result;
    }
    friend String operator+(char c, const String& str) {
        String result(1, c);
        result += str;
        return result;
    }
    friend String operator+(const char* c, const String& other) {
        String result(c);
        result += other;
        return result;
    }

    //Length, Size, Capacity
    size_t Length() const {
        return size;
    }
    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return capacity - 1;
    }

    //PushBack, PopBack
    void PushBack(const char ch) {
        if (size + 1 == capacity) {
            capacity = capacity * 2 + 1;
            char* newData = new char[capacity];
            std::strcpy(newData, data);
            delete[] data;
            data = newData;
        }
        data[size] = ch;
        data[size + 1] = '\0';
        size++;
    }
    void PopBack() {
        if (size != 0) {
            data[size - 1] = '\0';
            size--;
        }
    }

    //Front, Back
    char& Front() {
        return data[0];
    }
    const char& Front() const {
        return data[0];
    }
    char& Back() {
        if (size == 0) return data[0];
        return data[size - 1];
    }
    const char& Back() const {
        if (size == 0) return data[0];
        return data[size - 1];
    }

    //Find, Rfind
    size_t Find(const String& substring) const {
        size_t substring_size = substring.size;
        if (substring_size > size || substring_size == 0) return Length();
        size_t equals;
        for (size_t i = 0; i <= size - substring_size; i++) {
            equals = 0;
            for (size_t j = 0; j < substring_size; j++) {
                if (substring.data[j] != data[i + j]) break;
                equals++;
            }
            if (equals == substring_size) return i;
        }
        return Length();
    }
    size_t Find(const char* substring) const {
        return Find(String(substring));
    }
    size_t Rfind(const String& substring) const {
        size_t substring_size = substring.size;
        if (substring_size > size || substring_size == 0) return Length();
        size_t equals;
        for (size_t i = size - substring_size; i >= 0; i--) {
            equals = 0;
            for (size_t j = 0; j < substring_size; j++) {
                if (substring.data[j] != data[i + j]) break;
                equals++;
            }
            if (equals == substring_size) return i;
            if (i == 0) break;
        }
        return Length();
    }

    //Substr
    String Substr(size_t start, size_t count) const {
        String substring(count, '\0');
        const char* start_pointer = data + start;
        const char* end_pointer = start_pointer + count;
        std::copy(start_pointer, end_pointer, substring.Data());
        return substring;
    }

    //Empty, Clear
    bool Empty() const {
        return size == 0;
    }
    void Clear() {
        size = 0;
        data[0] = '\0';
    }

    //ShrinkToFit
    void ShrinkToFit() {
        capacity = size + 1;
        char* newData = new char[capacity];
        std::strcpy(newData, data);
        delete[] data;
        data = newData;
    }

    //Operators << and >> (declaration)
    friend std::ostream& operator<<(std::ostream& os, const String& str);

    friend std::istream& operator>>(std::istream& is, String& str);


    //Data
    char* Data() {
        return &data[0];
    }
    const char* Data() const {
        return &data[0];
    }

private:
    char* data;
    size_t size;
    size_t capacity;
};

inline std::ostream& operator<<(std::ostream& os, const String& str) {
    for (size_t i = 0; i < str.size; i++) {
        os << str.data[i];
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, String& str) {
    str.Clear();
    is >> std::ws;
    char c;
    while (is.get(c)) {
        if (c == ' ' || c == '\n' || c == '\t' ||
            c == '\r' || c == '\f' || c == '\v') {
            is.unget();
            break;
        }
        str.PushBack(c);
    }
    return is;
}