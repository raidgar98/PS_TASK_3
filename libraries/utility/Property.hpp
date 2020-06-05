#pragma once

#include <stdexcept>

#define THROW( exc ) try{ throw exc{}; }catch(const exc& ){ throw; }

struct PermissionAccessViolation : std::exception
{
    virtual const char * what() const noexcept override
    {
        return "Access Violation";
    }
};

template<typename T>
struct Allow
{
    Allow( const T& ) {}
};

template<typename T>
struct Deny
{
    Dent(const T&) { THROW( PermissionAccessViolation ) }
};

template<typename _To, typename _From>
constexpr _To to( const _From& val ) { return static_cast<_To>(val); }

template<typename T, typename _Write = Allow<T>, typename _Read = Allow<T> >
class __Property
{
private:

    T value;

public:

    _Property() = default;
    _Property(const T& val) : value{ val } {};
    _Property(T& val) : value{ val } {};
    _Property(T&& val) : value{ val } {};
    operator const T&() const { _Read(value); return value; }

    const _Property& operator=(const T& val) { _Write(val); value = val; return *this; }
    // const _Property& operator=(T&& val) { value = val; return *this; }
    // const _Property& operator=(T& val) { value = val; return *this; }
    
    const _Property& operator=(const _Property& val) { _Write(val); value = val.value; return *this; }
    // const _Property& operator=(_Property&& val) { return *this = val.value; }

    template<typename R> friend inline bool operator==(const _Property& val1, const _Property<R>& val2) { return to<T>(val1) == to<R>(val2); }
    template<typename R> friend inline bool operator!=(const _Property& val1, const _Property<R>& val2) { return to<T>(val1) != to<R>(val2); }
    friend inline bool operator==(const _Property& val1, const T& val2) { return val1.value == val2; }
    friend inline bool operator!=(const _Property& val1, const T& val2) { return val1.value != val2; }

    template<typename R> friend inline bool operator<(const _Property& val1, const _Property<R>& val2) { return to<T>(val1) < to<R>(val2); }
    template<typename R> friend inline bool operator>(const _Property& val1, const _Property<R>& val2) { return to<T>(val1) > to<R>(val2); }
    friend inline bool operator<(const _Property& val1, const T& val2) { return to<T>(val1) < val2; }
    friend inline bool operator>(const _Property& val1, const T& val2) { return to<T>(val1) > val2; }

    // template<typename R> friend inline bool operator<=(const _Property<T>& val1, const _Property<R>& val2) { return val1.value <= val2.value; }
    // template<typename R> friend inline bool operator>=(const _Property<T>& val1, const _Property<R>& val2) { return val1.value >= val2.value; }
    // friend inline bool operator<=(const _Property<T>& val1, const T& val2) { return val1.value <= val2; }
    // friend inline bool operator>=(const _Property<T>& val1, const T& val2) { return val1.value >= val2; }
};


template<typename T>
using Property = __Property<T, Allow<T>, Allow<T>>;

template<typename T>
using ReadOnyProperty = __Property<T, Deny<T>, Allow<T> >;

template<typename T>
using WriteOnyProperty = __Property<T, Allow<T>, Deny<T> >;

// Any possible usage?
// template<typename T>
// using RestrictedProperty = __Property<T, Deny<T>, Deny<T> >;

