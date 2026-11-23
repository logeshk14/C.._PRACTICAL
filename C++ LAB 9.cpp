
#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

/**
 * Observer Interface
 */
class Observer
{
public:
    virtual void notify(const string& message) = 0;

    virtual ~Observer() {}
};

/**
 * Email Notification Observer
 */
class EmailNotification : public Observer
{
private:
    string email;

public:
    EmailNotification(string e)
    {
        email = e;
    }

    void notify(const string& message) override
    {
        cout << "Email sent to " << email
             << ": " << message << endl;
    }
};

/**
 * SMS Notification Observer
 */
class SMSNotification : public Observer
{
private:
    string phoneNumber;

public:
    SMSNotification(string number)
    {
        phoneNumber = number;
    }

    void notify(const string& message) override
    {
        cout << "SMS sent to " << phoneNumber
             << ": " << message << endl;
    }
};

/**
 * Factory Class
 */
class NotificationFactory
{
public:
    static shared_ptr<Observer> createNotification(
        const string& type,
        const string& receiver)
    {
        if (type == "EMAIL")
        {
            return make_shared<EmailNotification>(receiver);
        }
        else if (type == "SMS")
        {
            return make_shared<SMSNotification>(receiver);
        }

        return nullptr;
    }
};

/**
 * Singleton Event Manager
 */
class EventManager
{
private:
    vector<shared_ptr<Observer>> observers;

    // Private Constructor
    EventManager()
    {
    }

public:
    // Delete Copy Constructor and Assignment Operator
    EventManager(const EventManager&) = delete;

    EventManager& operator=(const EventManager&) = delete;

    // Singleton Access Method
    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }

    // Subscribe Observer
    void subscribe(shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

    // Trigger Event
    void triggerEvent(const string& message)
    {
        cout << "\nEvent Triggered: "
             << message << endl;

        cout << "Sending Notifications...\n";

        for (auto observer : observers)
        {
            observer->notify(message);
        }
    }
};

int main()
{
    // Access Singleton EventManager
    EventManager& manager = EventManager::getInstance();

    // Create Observers using Factory Pattern
    shared_ptr<Observer> emailUser =
        NotificationFactory::createNotification(
            "EMAIL",
            "student@gmail.com");

    shared_ptr<Observer> smsUser =
        NotificationFactory::createNotification(
            "SMS",
            "9876543210");

    // Subscribe Observers
    manager.subscribe(emailUser);
    manager.subscribe(smsUser);

    // Trigger Event
    manager.triggerEvent(
        "University examination starts tomorrow!");

    return 0;
}
