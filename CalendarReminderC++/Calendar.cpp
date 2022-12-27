//Author: Amber Ford

#include <string>
#include <stdexcept>
#include <cassert>
#include "Calendar.h"


// Default Constructor
// Create an empty Calendar (one with zero Reminders)
Calendar::Calendar() : remList(nullptr), numRem(0) {
}


// Copy ctor
Calendar::Calendar(const Calendar &rhs) : remList(nullptr), numRem(0) {
    if (rhs.remList != nullptr) {
        remList = new RemNode;
        remList->rem = rhs.remList->rem;
        remList->next = nullptr;
        RemNodePtr newPtr = remList;
        for (RemNodePtr origPtr = rhs.remList->next; origPtr != nullptr; origPtr = origPtr->next) {
            newPtr->next = new RemNode;
            newPtr = newPtr->next;
            newPtr->rem = origPtr->rem;
            newPtr->next = nullptr;
        }

    }
}


// Destructor
Calendar::~Calendar() {
    while (remList != nullptr) {
        RemNodePtr tmp = remList;
        remList = remList->next;
        delete tmp;
    }
}


// Assignment operator
const Calendar &Calendar::operator=(const Calendar &rhs) {
    if (this != &rhs) {
        Calendar tmp(rhs);
        std::swap(remList, tmp.remList);
        std::swap(numRem, tmp.numRem);
    }
    return *this;
}


// getNumRem
// Return the total number of Reminders in the Calendar
size_t Calendar::getNumRem() const {
    return numRem;
}


//addRem(const Reminder &r)
//
//Purpose: add/insert a reminder in the list of reminder objects
//Parameters: Reminder r - the reminder to be added
//Returns: size_t - the index position of the inserted reminder
//
//Behavior:
//1. In case of the list being empty: insert as the first element
//2. In case of a non-empty Calendar: insert Reminder in sorted order
//3. In case of already existing Reminder with same date: insert new reminder
//   before (ahead of) the existing one
//4. Return the index of the inserted reminder, using zero-based indexing
size_t Calendar::addRem(const Reminder &r) {
    RemNodePtr prev, cur;
    RemNodePtr newPtr = new RemNode;
    newPtr->rem = r;
    size_t indexCount = 0;
    for (prev = nullptr, cur = remList; cur != nullptr && newPtr->rem > cur->rem;
         prev = cur, cur = cur->next) {
        indexCount++;
    }
    if (prev == nullptr) {
        remList = newPtr;
        newPtr->next = nullptr;
        numRem++;
        return 0;
    } else {
        prev->next = newPtr;

    }
    newPtr->next = cur;
    numRem++;
    return indexCount;
}


// getRem(size_t index)
//
// Purpose:    returns the reminder at the specified index in the Calendar,
//             throw exception if index is bad
// Parameters: size_t index - the index of the desired reminder;
//                            using zero-based indexing
// Returns:    Reminder     - the reminder at the specified index
//
// Behavior:
// 1. If the index is invalid, throw an std::invalid_argument exception
// 2. Otherwise, return the reminder at the specified index
Reminder Calendar::getRem(size_t index) const {
    RemNodePtr cur;
    size_t count = 0;
    if (index < 0) {
        throw std::invalid_argument("This index is not valid");
    } else if (index >= numRem) {
        throw std::invalid_argument("This index is not valid");
    } else {
        for (cur = remList; cur != nullptr && count != index;
             cur = cur->next, count++) {

        }
        return cur->rem;
    }

}


// displayRem()
//
// Purpose:    Return a string of all reminders
// Parameters: None
// Returns:    string - containing all the reminders in sorted order with each
//             reminder followed immediately by a newline character.
//             Returns an empty string if the Calendar is empty
std::string Calendar::displayRem() const {
    std::string tmpStr("");
    for (RemNodePtr cur = remList; cur != nullptr; cur = cur->next) {
        tmpStr = tmpStr + (cur->rem).toString() + "\n";
    }
    return tmpStr;
}


// displayRem(size_t index)
//
// Purpose:    Return a string of the reminder at a particular index in the Calendar
// Parameters: size_t index
// Return:     string - containing the reminder
//
// Behavior:
// 1. Returns string containing the reminder at the given index
//    (no newline character added)
// 2. Follows 0-indexing
// 3. If list is empty or the index is invalid, returns an empty string
std::string Calendar::displayRem(size_t index) const {
    Reminder tempRem;
    if (index > numRem || index < 0) {
        return "";
    }else{
        tempRem = getRem(index);
        return tempRem.toString() + "\n";
    }

}


// displayRem(const string& str)
//
// Purpose:    Return a string of all reminders whose message matches the provided
//             string
// Parameters: string str - the string we are supposed to check for match
// Returns:    string     - containing all the matching reminders, in sorted order,
//                          each reminder followed immediately by a newline character.
//
// Behavior:
// 1. Finds any reminders having its message same as the provided string (in a case
//    sensitive manner)
// 2. If no match is found, returns an empty string
// 3. If matches are found, append them on the return string in sorted order each
//    followed by a newline character.
std::string Calendar::displayRem(const std::string &str) const {
    RemNodePtr cur;
    std:: string displayString;
    for (cur = remList; cur != nullptr; cur = cur->next) {
        if ((cur->rem).getMsg() == str) {
            displayString += (cur->rem).toString() + "\n";
        }
    }
    return displayString;
}


// displayRem(const Date& d)
//
// Purpose:    Return a string of all reminders for a given date
// Parameters: Date d - the date we are supposed to check for match
// Return:     string - containing all the matching reminders, in sorted order,
//             each reminder followed immediately by a newline character.
//
// Behavior:
// 1. Finds any reminders on the provided date
// 2. If no match is found, returns an empty string
// 3. If matches are found, append them on the return string in sorted order each
//    followed by a newline character.
//
// Note: see addRem() for the definition of sorted order of Reminders with
//       the same date.
std::string Calendar::displayRem(const Date &d) const    // searches reminders by date
{
    RemNodePtr cur;
    std:: string displayString = "";
    for (cur = remList; cur != nullptr && (cur -> rem).getDate() <= d; cur = cur->next) {
        if((cur->rem).getDate() == d) {
            displayString += (cur->rem).toString() + "\n";
        }
    }
    return displayString;
}


// displayRem(const Date& d1, const Date& d2)
//
// Purpose:    Displays reminders in a range of two given dates
// Parameters: Date d1, Date d2 (the range of Dates)
// Return:     string containing all the matching reminders, in sorted order,
//             each reminder followed immediately by a newline character.
//
// Behavior:
// 1. If the Calendar contains no dates in the given range, return an empty string
// 2. Create a string containing all the reminders, in sorted order, which are later
//    than or equal to the smaller of the two dates and are earlier than or equal to
//    the larger of the two dates, with each reminder followed immediately by a
//    newline character.
std::string Calendar::displayRem(const Date &d1, const Date &d2) const {
    if (findRem(d1) == -1 || findRem(d2) == -1) {
        return "";
    }
    if (d1 == d2) {
        return displayRem(d1);
    } else {
        std::string displayString;
        Date a(d1);
        Date b(d2);
        if (a > b) {
            std::swap(a, b);
        }
        for (int i = findRem(a); i <= findRem(b); i++) {
            displayString += displayRem(i) + "\n";
        }
        return displayString;
    }
}


// findRem(const Date& d)
//
// Purpose:    Find first reminder for the given date and return its index
// Parameters: Date d - the date to search for
// Return:     int    - value containing the index of the first reminder with
//                      the specified date or -1 if no reminders with that date exist
int Calendar::findRem(const Date &d) const {
    RemNodePtr cur;
    int indexCount = 0;
    for (cur = remList; cur != nullptr && (cur->rem).getDate() != d;
         cur = cur->next, indexCount++) {
    }
    if (cur == nullptr) {
        return -1;
    }
    return indexCount;
}


//findRem(const std::string& str)
//
//Purpose: Find first reminder with the given message and return its index
//Parameters: string str, the message to search for
//Return: int value containing the index of the first reminder with the specified
//        message, or -1 if no reminders with that message exist
int Calendar::findRem(const std::string &str) const {
    RemNodePtr cur;
    int indexCount = 0;
    for (cur = remList; cur != nullptr && (cur->rem).getMsg() != str;
         cur = cur->next, indexCount++) {
    }
    if (cur == nullptr) {
        return -1;
    }
    return indexCount;
}


// deleteRem()
//
// Purpose:    Deletes all reminders earlier than today’s date
// Parameters: None
// Return:     size_t - the number of reminders deleted (a size_t value)
//
// Implementation Notes:
// 1. The default constructor of the Date class initializes a Date object to
//    today's date.
size_t Calendar::deleteRem() {
    RemNodePtr cur;
    Date today;
    size_t numDeleted = 0;
    size_t count = 0;
    for (cur = remList; cur != nullptr && (cur->rem).getDate() < today;
         cur = cur->next, count++) {
        deleteRem(count);
        numDeleted++;
    }
return numDeleted;
}


// deleteRem(size_t index)
//
// Purpose:    Deletes reminder object at a provided index position
// Parameters: size_t index
// Return:     size_t - the number of reminders deleted (a size_t value)
//
// Notes:
// 1. If the index is invalid, no deletions will be performed and zero is returned
size_t Calendar::deleteRem(size_t index) {
    RemNodePtr prev, cur;
    size_t count = 0;
    if (index > numRem) {
        return 0;
    } else if (index == 0) {
        cur = remList;
        remList = remList->next;
        delete cur;
        cur = nullptr;
        numRem--;
        return 1;
    }
    for (prev = nullptr, cur = remList; cur != nullptr && count != index;
         prev = cur, cur = cur->next, count++) {
    }
    prev->next = cur->next;
    delete cur;
    cur = nullptr;
    return 1;
}


// deleteRem(const string& str)
//
// Purpose:    Delete all reminders whose message matches a given string
// Parameters: string str - (whose match we want to find, case sensitive)
// Return:     size_t - number of reminders deleted (size_t value)
size_t Calendar::deleteRem(const std::string &str) {
    RemNodePtr cur;
    size_t numDeleted = 0;
    size_t count = 0;
    if (remList->rem.getMsg() == str) {
        deleteRem(0);
        numDeleted++;
    } else {
        for (cur = remList; cur != nullptr; cur = cur->next, count++) {
            if (cur->rem.getMsg() == str) {
                deleteRem(count);
                numDeleted++;
            }
        }
    }
    return numDeleted;
}


// deleteRem(const Date& d)
//
// Purpose:    Deletes all reminders on a particular date
// Parameters: Date d
// Return:     size_t - number of reminders deleted (size_t value)
size_t Calendar::deleteRem(const Date &d) {
    RemNodePtr cur;
    size_t numDeleted = 0;
    size_t count = 0;
    if (remList->rem.getDate() == d) {
        deleteRem(0);
        numDeleted++;
    }
    for (cur = remList; cur != nullptr; cur = cur->next, count++) {
        if (d == cur->rem.getDate()){
            deleteRem(count);
            numDeleted++;
        }
    }
    return numDeleted;
}


// deleteRem(const Date& d1, const Date& d2)
//
// Purpose:    Deletes all reminders between a range of two given dates
// Parameters: Date d1, Date d2 (the range of Dates)
// Return:     size_t - number of reminders deleted (size_t value)
//
// Behavior:
// 1. If the Calendar contains no dates in the given range, perform no deletions
//    and return zero
// 2. Delete all Reminders which are later than or equal to the smaller of the two
//    dates and are earlier than or equal to the larger of the two dates.
//    Return the number deleted.
size_t Calendar::deleteRem(const Date &d1, const Date &d2) {
    int indexD1 = findRem(d1);
    int indexD2 = findRem(d2);
    size_t numDeleted = 0;
    if (numRem == 0) {
        return 0;
    }
    if (findRem(d1) == -1 || findRem(d2) == -1) {
        return 0;
    }
    if (indexD1 > indexD2) {
        std::swap(indexD1, indexD2);
    }
    for (int i = indexD1; i <= indexD2; i++) {
        deleteRem(i);
        numDeleted++;
    }
    return numDeleted;

}
