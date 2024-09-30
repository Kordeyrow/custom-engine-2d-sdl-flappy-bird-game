#include "pch.h"
#include "../FlappyBirdGame/src/EventManager.h"


class TestCustomEvent : public BaseEvent {
public:
    std::string msg;
    TestCustomEvent(const std::string& message) : msg(message) {}
};

// Custom class for testing
class TestReceiverClass {
public:
    std::string messageReceived;

    void MemberFunction(const TestCustomEvent& event) {
        messageReceived = event.msg;
    }
};


TEST(EventManagerTest,
    Given_MemberFunctionIsSubscribedToCustomEvent_When_CustomEventIsEmitted_Then_MemberFunctionShouldBeCalled) 
{
    // Arrange (Setup your objects)
    EventManager manager;
    auto myObject = std::make_shared<TestReceiverClass>();

    // Act (Subscribe the member function and emit the event)
    auto registerID = manager.Register(myObject, &TestReceiverClass::MemberFunction);
    TestCustomEvent customEvent("Test Message");
    manager.Emit(customEvent);

    // Add relevant assertions here, like:
    EXPECT_EQ(myObject->messageReceived, "Test Message");  // Assuming myObject has a messageReceived attribute
}

// Main function for Google Test
int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}