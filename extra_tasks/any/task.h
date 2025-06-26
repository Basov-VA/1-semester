#pragma once
#include <cstdlib>
#include <typeinfo>
#include <memory>

struct Any {
    Any() : _inner(nullptr)
    {}


    Any(const Any& src) : _inner(src._inner->clone()) {}

    template <typename _Ty>
    Any(_Ty src) : _inner(new inner<_Ty>(std::forward<_Ty>(src))) {}

    template <typename _Ty>
    Any& operator=(_Ty src) {
        _inner = std::make_unique<inner<_Ty>>(std::forward<_Ty>(src));
        return *this;
    }

    Any(Any&& src) noexcept :
    _inner(std::move(src._inner)) {
        src._inner = nullptr;
    }

    Any& operator=(const Any& src) {
        Any oTmp(src);
        std::swap(oTmp._inner, this->_inner);
        return *this;
    }

    Any& operator=(Any&& src) {
        this->_inner = std::move(src._inner);
        src._inner = nullptr;
        return *this;
    }

    const std::type_info& Type() const { return _inner->Type(); }

    template <typename _Ty>
    _Ty& cast() {
        return dynamic_cast<inner<_Ty>&>(*_inner).get();
    }

    template <typename _Ty>
    const _Ty& cast() const {
        return dynamic_cast<inner<_Ty>&>(*_inner).get();
    }

    bool Empty() const {
        return _inner == nullptr;
    }

    void Reset() {
        _inner.reset();
    }

    template <typename _Ty>
    void Swap(_Ty src)
    {
        Any key = this->_inner->clone();
        this->_inner =  Any(src)._inner;
        src = key;
    }

    void Swap(Any& other) {
        std::swap(_inner, other._inner);
    }

    template <typename _Ty>
    _Ty Value() const {
        return dynamic_cast<inner<_Ty>&>(*_inner).get();
    }
    

private:
    struct inner_base {
        virtual ~inner_base() {}
        virtual inner_base* clone() const = 0;
        virtual const std::type_info& Type() const = 0;
    };

    template <typename _Ty>
    struct inner : inner_base {
        inner(_Ty newval) : _value(std::move(newval)) {}
        inner_base* clone() const override { return new inner(_value); }
        const std::type_info& Type() const override { return typeid(_Ty); }
        _Ty& get() { return _value; }
        const _Ty& get() const { return _value; }

    private:
        _Ty _value;
    };

    std::unique_ptr<inner_base> _inner;
};
