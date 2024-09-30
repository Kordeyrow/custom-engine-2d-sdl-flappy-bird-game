#pragma once

#include "BaseEvent.h"
#include <typeindex>
#include <unordered_map>
#include <functional>
#include <memory>

class EventManager {
public:
    using ListenerID = std::size_t;

    // Register a member function for an event type using shared_ptr
    template <typename ObjectType, typename EventType>
    ListenerID Register(std::shared_ptr<ObjectType> obj, void(ObjectType::* func)(const EventType&)) {
        auto id = nextListenerID++;
        std::type_index eventType = typeid(EventType);

        // Capture the shared_ptr to extend object lifetime
        listeners[eventType][id] = [obj, func](const BaseEvent& event) {
            auto derivedEvent = dynamic_cast<const EventType*>(&event);
            if (derivedEvent) {
                (obj.get()->*func)(*derivedEvent);  // Use shared_ptr to access the object
            }
        };
        return id;
    }

    // Emit an event of any type
    void Emit(const BaseEvent& event) const {
        std::type_index eventType = typeid(event);
        auto it = listeners.find(eventType);
        if (it != listeners.end()) {
            for (const auto& listener : it->second) {
                listener.second(event);  // Call each listener
            }
        }
    }

    // Unsubscribe a listener by ID and event type
    void Unsubscribe(ListenerID id) {
        for (auto it = listeners.begin(); it != listeners.end(); ++it) {
            auto listenerIt = it->second.find(id);  // Find the listener ID in the map
            if (listenerIt != it->second.end()) {
                it->second.erase(listenerIt);  // Remove the listener if found
                if (it->second.empty()) { // Remove the entire event type if no listeners are left
                    listeners.erase(it);
                }
                break;  // Listener ID is unique, break after removal
            }
        }
    }

private:
    std::size_t nextListenerID = 0;
    std::unordered_map<std::type_index, std::unordered_map<ListenerID, std::function<void(const BaseEvent&)>>> listeners;
};
