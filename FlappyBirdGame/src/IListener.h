#pragma once
#include <functional>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <type_traits>

// Interface for listeners
class IListener {
public:
    virtual ~IListener() = default;

    // Pure virtual function to invoke the listener
    virtual void Invoke(int, const std::string&) = 0;

    // Virtual function for comparison
    virtual bool Equals(const IListener* other) const = 0;

    // Overload < operator to enable storing in std::set
    bool operator<(const IListener& other) const {
        return this < &other;
    }
};

// Listener for free functions
class FreeFunctionListener : public IListener {
public:
    using FuncType = void(*)(int, const std::string&);
    FuncType func;

    explicit FreeFunctionListener(FuncType f) : func(f) {}

    void Invoke(int x, const std::string& msg) override {
        func(x, msg);
    }

    bool Equals(const IListener* other) const override {
        auto* otherListener = dynamic_cast<const FreeFunctionListener*>(other);
        return otherListener && otherListener->func == this->func;
    }
};

// Listener for member functions
template <typename T>
class MemberFunctionListener : public IListener {
public:
    using FuncType = void (T::*)(int, const std::string&);

    T* object;
    FuncType func;

    MemberFunctionListener(T* obj, FuncType f) : object(obj), func(f) {}

    void Invoke(int x, const std::string& msg) override {
        (object->*func)(x, msg);
    }

    bool Equals(const IListener* other) const override {
        auto* otherListener = dynamic_cast<const MemberFunctionListener<T>*>(other);
        return otherListener && otherListener->object == this->object && otherListener->func == this->func;
    }

    bool operator<(const IListener& other) const override {
        return this < &other;
    }
};

// Listener for std::function or lambdas
class LambdaListener : public IListener {
public:
    std::function<void(int, const std::string&)> func;

    explicit LambdaListener(std::function<void(int, const std::string&)> f) : func(f) {}

    void Invoke(int x, const std::string& msg) override {
        func(x, msg);
    }

    bool Equals(const IListener* other) const override {
        return this == other;
    }

    /*bool operator<(const IListener& other) const override {
        return this < &other;
    }*/
};