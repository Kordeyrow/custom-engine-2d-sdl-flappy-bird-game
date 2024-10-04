//#include "EventManager.h"
//#include <iostream>
//
//// Example custom event class defined by the user
//class CustomEvent : public BaseEvent {
//public:
//    std::string msg;
//    CustomEvent(const std::string& message) : msg(message) {}
//};
//
//// Example class with a member function to handle the event
//class MyClass {
//public:
//    void MemberFunction(const CustomEvent& _event) {
//        std::cout << "Member Function Called with message: " << _event.msg << "\n";
//    }
//};
//
//// Example usage in main function
//int main() {
//    EventManager manager;
//    auto myObject = std::make_shared<MyClass>();
//
//    // Register a member function for the CustomEvent
//    auto registerID = manager.Register(myObject, &MyClass::MemberFunction);
//
//    // Emit the CustomEvent using a string argument
//    CustomEvent event1("message! show listen");
//    manager.Emit(event1);
//
//    // Unsubscribe the member function
//    manager.Unsubscribe(registerID);
//
//    // Emit again to see remaining listeners
//    CustomEvent event2("message! show not listen");
//    manager.Emit(event2);
//
//    return 0;
//}
