#pragma once

template<typename T>
class Property
{
private:

    T value;

public:

    Property() = default;
    Property(const T& val) : value{ val } {};
    Property(T& val) : value{ val } {};
    Property(T&& val) : value{ val } {};
    operator const T&() const { return value; }

    const Property& operator=(const T& val) { value = val; return *this; }
    const Property& operator=(T& val) { value = val; return *this; }

    template<typename R> friend inline bool operator==(const Property<T>& val1, const Property<R>& val2) { return val1.value == val2.value; }
    template<typename R> friend inline bool operator!=(const Property<T>& val1, const Property<R>& val2) { return val1.value != val2.value; }
    friend inline bool operator==(const Property<T>& val1, const T& val2) { return val1.value == val2; }
    friend inline bool operator!=(const Property<T>& val1, const T& val2) { return val1.value != val2; }

    template<typename R> friend inline bool operator<(const Property<T>& val1, const Property<R>& val2) { return val1.value < val2.value; }
    template<typename R> friend inline bool operator>(const Property<T>& val1, const Property<R>& val2) { return val1.value > val2.value; }
    friend inline bool operator<(const Property<T>& val1, const T& val2) { return val1.value < val2; }
    friend inline bool operator>(const Property<T>& val1, const T& val2) { return val1.value > val2; }

    template<typename R> friend inline bool operator<=(const Property<T>& val1, const Property<R>& val2) { return val1.value <= val2.value; }
    template<typename R> friend inline bool operator>=(const Property<T>& val1, const Property<R>& val2) { return val1.value >= val2.value; }
    friend inline bool operator<=(const Property<T>& val1, const T& val2) { return val1.value <= val2; }
    friend inline bool operator>=(const Property<T>& val1, const T& val2) { return val1.value >= val2; }
};
