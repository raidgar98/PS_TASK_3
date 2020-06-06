#pragma once

#include <stdexcept>

#define THROW( exc ) try{ throw exc{}; }catch(const exc& ){ throw; }
#define THROW_MSG( exc, msg ) try{ throw exc( msg ); }catch(const exc& ){ throw; }

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
    Deny(const T&) { THROW( PermissionAccessViolation ) }
};

template<typename _To, typename _From>
constexpr _To to( const _From& val ) { return static_cast<_To>(val); }

template<typename T, typename _Write = Allow<T>, typename _Read = Allow<T> >
class _Property
{
private:

    T value;

public:

    _Property() = default;
    _Property(const T& val) : value{ val } {};
    _Property(T& val) : value{ val } {};
    _Property(T&& val) : value{ val } {};
    operator const T&() const { _Read{value}; return value; }
    const T& operator->() const { _Read{value}; return value; }
    template<typename _Index, typename _Value>
    const _Value& operator[](const _Index& val) const { _Read{value}; return value[val]; }

    const _Property& operator=(const T& val) { _Write{val}; value = val; return *this; }
    // const _Property& operator=(T&& val) { value = val; return *this; }
    // const _Property& operator=(T& val) { value = val; return *this; }
    
    const _Property& operator=(const _Property& val) { _Write{val}; value = val.value; return *this; }
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
using Property = _Property<T, Allow<T>, Allow<T>>;

template<typename T>
using ReadOnyProperty = _Property<T, Deny<T>, Allow<T> >;

template<typename T>
using WriteOnyProperty = _Property<T, Allow<T>, Deny<T> >;

// Any possible usage?
// template<typename T>
// using RestrictedProperty = _Property<T, Deny<T>, Deny<T> >;

