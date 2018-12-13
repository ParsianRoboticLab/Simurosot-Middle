//     Copyright Toru Niina 2017.
// Distributed under the MIT License.
#ifndef TOML11_RESULT_H
#define TOML11_RESULT_H
#include <type_traits>
#include <stdexcept>
#include <utility>
#include <new>
#include <string>
#include <sstream>
#include <cassert>

namespace toml
{

#if __cplusplus >= 201703L

template<typename F, typename ... Args>
using return_type_of_t = std::invoke_result_t<F, Args...>;

#else
// result_of is deprecated after C++17
template<typename F, typename ... Args>
using return_type_of_t = typename std::result_of<F(Args...)>::type;

#endif


template<typename T>
struct success
{
    using value_type = T;
    value_type value;

    explicit success(const value_type& v)
        noexcept(std::is_nothrow_copy_constructible<value_type>::value)
        : value(v)
    {}
    explicit success(value_type&& v)
        noexcept(std::is_nothrow_move_constructible<value_type>::value)
        : value(std::move(v))
    {}

    template<typename U>
    explicit success(U&& v): value(std::forward<U>(v)) {}

    template<typename U>
    explicit success(const success<U>& v): value(v.value) {}
    template<typename U>
    explicit success(success<U>&& v): value(std::move(v.value)) {}

    ~success() = default;
    success(const success&) = default;
    success(success&&)      = default;
    success& operator=(const success&) = default;
    success& operator=(success&&)      = default;
};

template<typename T>
struct failure
{
    using value_type = T;
    value_type value;

    explicit failure(const value_type& v)
        noexcept(std::is_nothrow_copy_constructible<value_type>::value)
        : value(v)
    {}
    explicit failure(value_type&& v)
        noexcept(std::is_nothrow_move_constructible<value_type>::value)
        : value(std::move(v))
    {}

    template<typename U>
    explicit failure(U&& v): value(std::forward<U>(v)) {}

    template<typename U>
    explicit failure(const failure<U>& v): value(v.value) {}
    template<typename U>
    explicit failure(failure<U>&& v): value(std::move(v.value)) {}

    ~failure() = default;
    failure(const failure&) = default;
    failure(failure&&)      = default;
    failure& operator=(const failure&) = default;
    failure& operator=(failure&&)      = default;
};

template<typename T>
success<typename std::remove_cv<typename std::remove_reference<T>::type>::type>
ok(T&& v)
{
    return success<
        typename std::remove_cv<typename std::remove_reference<T>::type>::type
        >(std::forward<T>(v));
}
template<typename T>
failure<typename std::remove_cv<typename std::remove_reference<T>::type>::type>
err(T&& v)
{
    return failure<
        typename std::remove_cv<typename std::remove_reference<T>::type>::type
        >(std::forward<T>(v));
}

inline success<std::string> ok(const char* literal)
{
    return success<std::string>(std::string(literal));
}
inline failure<std::string> err(const char* literal)
{
    return failure<std::string>(std::string(literal));
}


template<typename T, typename E>
struct result
{
    using value_type = T;
    using error_type = E;
    using success_type = success<value_type>;
    using failure_type = failure<error_type>;

    result(const success_type& s): is_ok_(true)
    {
        auto tmp = ::new(std::addressof(this->succ)) success_type(s);
        assert(tmp == std::addressof(this->succ));
    }
    result(const failure_type& f): is_ok_(false)
    {
        auto tmp = ::new(std::addressof(this->fail)) failure_type(f);
        assert(tmp == std::addressof(this->fail));
    }
    result(success_type&& s): is_ok_(true)
    {
        auto tmp = ::new(std::addressof(this->succ)) success_type(std::move(s));
        assert(tmp == std::addressof(this->succ));
    }
    result(failure_type&& f): is_ok_(false)
    {
        auto tmp = ::new(std::addressof(this->fail)) failure_type(std::move(f));
        assert(tmp == std::addressof(this->fail));
    }

    template<typename U>
    result(const success<U>& s): is_ok_(true)
    {
        auto tmp = ::new(std::addressof(this->succ)) success_type(s.value);
        assert(tmp == std::addressof(this->succ));
    }
    template<typename U>
    result(const failure<U>& f): is_ok_(false)
    {
        auto tmp = ::new(std::addressof(this->fail)) failure_type(f.value);
        assert(tmp == std::addressof(this->fail));
    }
    template<typename U>
    result(success<U>&& s): is_ok_(true)
    {
        auto tmp = ::new(std::addressof(this->succ)) success_type(std::move(s.value));
        assert(tmp == std::addressof(this->succ));
    }
    template<typename U>
    result(failure<U>&& f): is_ok_(false)
    {
        auto tmp = ::new(std::addressof(this->fail)) failure_type(std::move(f.value));
        assert(tmp == std::addressof(this->fail));
    }

    result& operator=(const success_type& s)
    {
        this->cleanup();
        this->is_ok_ = true;
        auto tmp = ::new(std::addressof(this->succ)) success_type(s);
        assert(tmp == std::addressof(this->succ));
        return *this;
    }
    result& operator=(const failure_type& f)
    {
        this->cleanup();
        this->is_ok_ = false;
        auto tmp = ::new(std::addressof(this->fail)) failure_type(f);
        assert(tmp == std::addressof(this->fail));
        return *this;
    }
    result& operator=(success_type&& s)
    {
        this->cleanup();
        this->is_ok_ = true;
        auto tmp = ::new(std::addressof(this->succ)) success_type(std::move(s));
        assert(tmp == std::addressof(this->succ));
        return *this;
    }
    result& operator=(failure_type&& f)
    {
        this->cleanup();
        this->is_ok_ = false;
        auto tmp = ::new(std::addressof(this->fail)) failure_type(std::move(f));
        assert(tmp == std::addressof(this->fail));
        return *this;
    }

    template<typename U>
    result& operator=(const success<U>& s)
    {
        this->cleanup();
        this->is_ok_ = true;
        auto tmp = ::new(std::addressof(this->succ)) success_type(s.value);
        assert(tmp == std::addressof(this->succ));
        return *this;
    }
    template<typename U>
    result& operator=(const failure<U>& f)
    {
        this->cleanup();
        this->is_ok_ = false;
        auto tmp = ::new(std::addressof(this->fail)) failure_type(f.value);
        assert(tmp == std::addressof(this->fail));
        return *this;
    }
    template<typename U>
    result& operator=(success<U>&& s)
    {
        this->cleanup();
        this->is_ok_ = true;
        auto tmp = ::new(std::addressof(this->succ)) success_type(std::move(s.value));
        assert(tmp == std::addressof(this->succ));
        return *this;
    }
    template<typename U>
    result& operator=(failure<U>&& f)
    {
        this->cleanup();
        this->is_ok_ = false;
        auto tmp = ::new(std::addressof(this->fail)) failure_type(std::move(f.value));
        assert(tmp == std::addressof(this->fail));
        return *this;
    }

    ~result() noexcept {this->cleanup();}

    result(const result& other): is_ok_(other.is_ok())
    {
        if(other.is_ok())
        {
            auto tmp = ::new(std::addressof(this->succ)) success_type(other.as_ok());
            assert(tmp == std::addressof(this->succ));
        }
        else
        {
            auto tmp = ::new(std::addressof(this->fail)) failure_type(other.as_err());
            assert(tmp == std::addressof(this->fail));
        }
    }
    result(result&& other): is_ok_(other.is_ok())
    {
        if(other.is_ok())
        {
            auto tmp = ::new(std::addressof(this->succ)) success_type(std::move(other.as_ok()));
            assert(tmp == std::addressof(this->succ));
        }
        else
        {
            auto tmp = ::new(std::addressof(this->fail)) failure_type(std::move(other.as_err()));
            assert(tmp == std::addressof(this->fail));
        }
    }

    template<typename U, typename F>
    result(const result<U, F>& other): is_ok_(other.is_ok())
    {
        if(other.is_ok())
        {
            auto tmp = ::new(std::addressof(this->succ)) success_type(other.as_ok());
            assert(tmp == std::addressof(this->succ));
        }
        else
        {
            auto tmp = ::new(std::addressof(this->fail)) failure_type(other.as_err());
            assert(tmp == std::addressof(this->fail));
        }
    }
    template<typename U, typename F>
    result(result<U, F>&& other): is_ok_(other.is_ok())
    {
        if(other.is_ok())
        {
            auto tmp = ::new(std::addressof(this->succ)) success_type(std::move(other.as_ok()));
            assert(tmp == std::addressof(this->succ));
        }
        else
        {
            auto tmp = ::new(std::addressof(this->fail)) failure_type(std::move(other.as_err()));
            assert(tmp == std::addressof(this->fail));
        }
    }

    result& operator=(const result& other)
    {
        this->cleanup();
        if(other.is_ok())
        {
            auto tmp = ::new(std::addressof(this->succ)) success_type(other.as_ok());
            assert(tmp == std::addressof(this->succ));
        }
        else
        {
            auto tmp = ::new(std::addressof(this->fail)) failure_type(other.as_err());
            assert(tmp == std::addressof(this->fail));
        }
        is_ok_ = other.is_ok();
        return *this;
    }
    result& operator=(result&& other)
    {
        this->cleanup();
        if(other.is_ok())
        {
            auto tmp = ::new(std::addressof(this->succ)) success_type(std::move(other.as_ok()));
            assert(tmp == std::addressof(this->succ));
        }
        else
        {
            auto tmp = ::new(std::addressof(this->fail)) failure_type(std::move(other.as_err()));
            assert(tmp == std::addressof(this->fail));
        }
        is_ok_ = other.is_ok();
        return *this;
    }

    template<typename U, typename F>
    result& operator=(const result<U, F>& other)
    {
        this->cleanup();
        if(other.is_ok())
        {
            auto tmp = ::new(std::addressof(this->succ)) success_type(other.as_ok());
            assert(tmp == std::addressof(this->succ));
        }
        else
        {
            auto tmp = ::new(std::addressof(this->fail)) failure_type(other.as_err());
            assert(tmp == std::addressof(this->fail));
        }
        is_ok_ = other.is_ok();
        return *this;
    }
    template<typename U, typename F>
    result& operator=(result<U, F>&& other)
    {
        this->cleanup();
        if(other.is_ok())
        {
            auto tmp = ::new(std::addressof(this->succ)) success_type(std::move(other.as_ok()));
            assert(tmp == std::addressof(this->succ));
        }
        else
        {
            auto tmp = ::new(std::addressof(this->fail)) failure_type(std::move(other.as_err()));
            assert(tmp == std::addressof(this->fail));
        }
        is_ok_ = other.is_ok();
        return *this;
    }

    bool is_ok()  const noexcept {return is_ok_;}
    bool is_err() const noexcept {return !is_ok_;}

    operator bool() const noexcept {return is_ok_;}

    value_type&       unwrap() &
    {
        if(is_err())
        {
            throw std::runtime_error("toml::result: bad unwrap: " +
                                     format_error(this->as_err()));
        }
        return this->succ.value;
    }
    value_type const& unwrap() const&
    {
        if(is_err())
        {
            throw std::runtime_error("toml::result: bad unwrap: " +
                                     format_error(this->as_err()));
        }
        return this->succ.value;
    }
    value_type&&      unwrap() &&
    {
        if(is_err())
        {
            throw std::runtime_error("toml::result: bad unwrap: " +
                                     format_error(this->as_err()));
        }
        return std::move(this->succ.value);
    }

    template<typename U>
    value_type&       unwrap_or(U& opt) &
    {
        if(is_err()) {return opt;}
        return this->succ.value;
    }
    template<typename U>
    value_type const& unwrap_or(U const& opt) const&
    {
        if(is_err()) {return opt;}
        return this->succ.value;
    }
    template<typename U>
    value_type&&      unwrap_or(U&& opt) &&
    {
        if(is_err()) {return std::move(opt);}
        return std::move(this->succ.value);
    }

    error_type&       unwrap_err() &
    {
        if(is_ok()) {throw std::runtime_error("toml::result: bad unwrap_err");}
        return this->fail.value;
    }
    error_type const& unwrap_err() const&
    {
        if(is_ok()) {throw std::runtime_error("toml::result: bad unwrap_err");}
        return this->fail.value;
    }
    error_type&&      unwrap_err() &&
    {
        if(is_ok()) {throw std::runtime_error("toml::result: bad unwrap_err");}
        return std::move(this->fail.value);
    }

    value_type&       as_ok() &      noexcept {return this->succ.value;}
    value_type const& as_ok() const& noexcept {return this->succ.value;}
    value_type&&      as_ok() &&     noexcept {return std::move(this->succ.value);}

    error_type&       as_err() &      noexcept {return this->fail.value;}
    error_type const& as_err() const& noexcept {return this->fail.value;}
    error_type&&      as_err() &&     noexcept {return std::move(this->fail.value);}


    // prerequisities
    // F: T -> U
    // retval: result<U, E>
    template<typename F>
    result<return_type_of_t<F, value_type&>, error_type>
    map(F&& f) &
    {
        if(this->is_ok()){return ok(f(this->as_ok()));}
        return err(this->as_err());
    }
    template<typename F>
    result<return_type_of_t<F, value_type const&>, error_type>
    map(F&& f) const&
    {
        if(this->is_ok()){return ok(f(this->as_ok()));}
        return err(this->as_err());
    }
    template<typename F>
    result<return_type_of_t<F, value_type &&>, error_type>
    map(F&& f) &&
    {
        if(this->is_ok()){return ok(f(std::move(this->as_ok())));}
        return err(std::move(this->as_err()));
    }

    // prerequisities
    // F: E -> F
    // retval: result<T, F>
    template<typename F>
    result<value_type, return_type_of_t<F, error_type&>>
    map_err(F&& f) &
    {
        if(this->is_err()){return err(f(this->as_err()));}
        return ok(this->as_ok());
    }
    template<typename F>
    result<value_type, return_type_of_t<F, error_type const&>>
    map_err(F&& f) const&
    {
        if(this->is_err()){return err(f(this->as_err()));}
        return ok(this->as_ok());
    }
    template<typename F>
    result<value_type, return_type_of_t<F, error_type&&>>
    map_err(F&& f) &&
    {
        if(this->is_err()){return err(f(std::move(this->as_err())));}
        return ok(std::move(this->as_ok()));
    }

    // prerequisities
    // F: T -> U
    // retval: U
    template<typename F, typename U>
    return_type_of_t<F, value_type&>
    map_or_else(F&& f, U&& opt) &
    {
        if(this->is_err()){return std::forward<U>(opt);}
        return f(this->as_ok());
    }
    template<typename F, typename U>
    return_type_of_t<F, value_type const&>
    map_or_else(F&& f, U&& opt) const&
    {
        if(this->is_err()){return std::forward<U>(opt);}
        return f(this->as_ok());
    }
    template<typename F, typename U>
    return_type_of_t<F, value_type&&>
    map_or_else(F&& f, U&& opt) &&
    {
        if(this->is_err()){return std::forward<U>(opt);}
        return f(std::move(this->as_ok()));
    }

    // prerequisities
    // F: E -> U
    // retval: U
    template<typename F, typename U>
    return_type_of_t<F, error_type&>
    map_err_or_else(F&& f, U&& opt) &
    {
        if(this->is_ok()){return std::forward<U>(opt);}
        return f(this->as_err());
    }
    template<typename F, typename U>
    return_type_of_t<F, error_type const&>
    map_err_or_else(F&& f, U&& opt) const&
    {
        if(this->is_ok()){return std::forward<U>(opt);}
        return f(this->as_err());
    }
    template<typename F, typename U>
    return_type_of_t<F, error_type&&>
    map_err_or_else(F&& f, U&& opt) &&
    {
        if(this->is_ok()){return std::forward<U>(opt);}
        return f(std::move(this->as_err()));
    }

    // prerequisities:
    // F: func T -> U
    // toml::err(error_type) should be convertible to U.
    // normally, type U is another result<S, F> and E is convertible to F
    template<typename F>
    return_type_of_t<F, value_type&>
    and_then(F&& f) &
    {
        if(this->is_ok()){return f(this->as_ok());}
        return err(this->as_err());
    }
    template<typename F>
    return_type_of_t<F, value_type const&>
    and_then(F&& f) const&
    {
        if(this->is_ok()){return f(this->as_ok());}
        return err(this->as_err());
    }
    template<typename F>
    return_type_of_t<F, value_type&&>
    and_then(F&& f) &&
    {
        if(this->is_ok()){return f(std::move(this->as_ok()));}
        return err(std::move(this->as_err()));
    }

    // prerequisities:
    // F: func E -> U
    // toml::ok(value_type) should be convertible to U.
    // normally, type U is another result<S, F> and T is convertible to S
    template<typename F>
    return_type_of_t<F, error_type&>
    or_else(F&& f) &
    {
        if(this->is_err()){return f(this->as_err());}
        return ok(this->as_ok());
    }
    template<typename F>
    return_type_of_t<F, error_type const&>
    or_else(F&& f) const&
    {
        if(this->is_err()){return f(this->as_err());}
        return ok(this->as_ok());
    }
    template<typename F>
    return_type_of_t<F, error_type&&>
    or_else(F&& f) &&
    {
        if(this->is_err()){return f(std::move(this->as_err()));}
        return ok(std::move(this->as_ok()));
    }

    void swap(result<T, E>& other)
    {
        result<T, E> tmp(std::move(*this));
        *this = std::move(other);
        other = std::move(tmp);
        return ;
    }

  private:

    static std::string format_error(std::exception const& excpt)
    {
        return std::string(excpt.what());
    }
    template<typename U, typename std::enable_if<!std::is_base_of<
        std::exception, U>::value, std::nullptr_t>::type = nullptr>
    static std::string format_error(U const& others)
    {
        std::ostringstream oss; oss << others;
        return oss.str();
    }

    void cleanup() noexcept
    {
        if(this->is_ok_) {this->succ.~success_type();}
        else             {this->fail.~failure_type();}
        return;
    }

  private:

    bool      is_ok_;
    union
    {
        success_type succ;
        failure_type fail;
    };
};

template<typename T, typename E>
void swap(result<T, E>& lhs, result<T, E>& rhs)
{
    lhs.swap(rhs);
    return;
}

} // toml11
#endif// TOML11_RESULT_H
