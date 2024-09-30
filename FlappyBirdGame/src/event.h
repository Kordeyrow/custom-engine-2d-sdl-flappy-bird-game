#pragma once
#include <functional>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <type_traits>
#include "IListener.h"

// Event class for storing and invoking listeners
class Event {
private:
    std::set<std::unique_ptr<IListener>> listeners;

public:
    // Subscribe a listener
    void Subscribe(std::unique_ptr<IListener> listener) {
        listeners.insert(std::move(listener));
    }

    // Remove a listener by comparing pointers
    void Unsubscribe(const IListener* listener) {
        auto it = std::find_if(listeners.begin(), listeners.end(),
            [listener](const std::unique_ptr<IListener>& existingListener) {
                return existingListener->Equals(listener);
            });
        if (it != listeners.end()) {
            listeners.erase(it);
        }
    }

    // Invoke all listeners
    void Invoke(int x, const std::string& msg) {
        for (const auto& listener : listeners) {
            listener->Invoke(x, msg);
        }
    }
};