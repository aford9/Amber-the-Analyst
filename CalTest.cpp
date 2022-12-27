#include <iostream>
#include <string>
#include <stdexcept>
#include "Calendar.h"


int main() {
    // Here is some sample code that does some simple testing of the Calendar class.
    // It creates an empty Calendar and performs some test on it.
    // It then adds a Reminder to the Calendar and performs some other tests on it.
    // This is only a simple sample, and is not considered to be very thorough.


    Calendar cal1;   // create an empty Calendar object via default ctor

    if (cal1.getNumRem() != 0) {  // test getNumRem()
        std::cout << "Default ctor failed to create an empty calendar" << std::endl;
        std::cout << "Reported that " << cal1.getNumRem() << " reminders exist"
                  << std::endl;
    }

    if (cal1.displayRem() != "") {  // test displayRem()
        std::cout << "Default ctor should produce an empty calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: " << cal1.displayRem()
                  << std::endl;
    }


    Date d1("01/07/2019");
    Reminder rem1(d1, "First day of classes");
    size_t index = cal1.addRem(rem1);   // test addRem(); Calendar now has one Reminder

    if (index != 0) {
        std::cout << "addRem failed to return index 0 for first insertion" << std::endl;
        std::cout << "Returned index == " << index << std::endl;
    }

    if (cal1.getNumRem() != 1) {
        std::cout << "addRem/getNumRem failed after inserting one reminder" << std::endl;
        std::cout << "Reported that " << cal1.getNumRem() << " reminders exist"
                  << std::endl;
    }

    if (cal1.displayRem() != "On 01/07/2019: First day of classes\n") {
        std::cout << "Unexpected reminder in calendar" << std::endl;
        std::cout << "displayRem returned the following reminders: " << cal1.displayRem()
                  << std::endl;
    }
    Date d2("01/08/2019");
    Reminder rem2(d2, "Second day of classes");
    cal1.addRem(rem2);
    if (cal1.getNumRem() != 2) {
        std::cout << "addRem/getNumRem failed after inserting more than one"
                     " reminder" << std::endl;
        std::cout << "Reported that " << cal1.getNumRem() << " reminders exist"
                  << std::endl;
    }

    if (cal1.displayRem(3) != "") {
        std::cout << "displayRem doesn't properly handle invalid index" << std::endl;
        std::cout << "displayRem should return an empty string" << std::endl;
    }
    if (cal1.displayRem() !=
        "On 01/07/2019: First day of classes\nOn 01/08/2019: Second day of classes\n") {
        std::cout << "displayRem doesn't successfully display multiple reminders." << std::endl;
    }
    std::string str = "Second day of classes";
    std::string badStr = "third";
    if (cal1.displayRem(str) != "On 01/08/2019: Second day of classes\n") {
        std::cout << "displayRem doesn't successfully return matching string" << std::endl;
    }
    if (cal1.displayRem(badStr) != "") {
        std::cout << "displayRem doesn't successfully return empty string for invalid match"
                  << std::endl;
    }
    //adding a reminder with same date as previous reminder
    Date d3(01, 07, 2019);
    Reminder rem3(d3, "Pick up syllabus");
    cal1.addRem(rem3);
    Date d4("01/10/2019");
    Reminder rem4(d4, "Go to lunch");
    cal1.addRem(rem4);
    //invalid dates
    Date d5("01/15/2019");
    Date d6("01/16/2019");
    Date d20(01, 29, 2019);
    Reminder rem20(d20, "");
    cal1.addRem(rem20);
    if (cal1.displayRem(d20) != "On 01/29/2019: No Message\n") {
        std::cout << "displayRem given date doesn't properly handle empty messages" << std::endl;
    }
    if (cal1.displayRem(d3) !=
        "On 01/07/2019: Pick up syllabus\nOn 01/07/2019: First day of classes\n") {
        std::cout << "displayRem given date doesn't properly display reminders for a given date"
                  << std::endl;
    }
    if (cal1.displayRem(d5) != "") {
        std::cout << "displayRem doesn't return an empty string for invalid date" << std::endl;
    }
    if (cal1.displayRem(d3, d4) !=
        "On 01/07/2019: Pick up syllabus\nOn 01/07/2019: First day of classes\n"
        "On 01/08/2019: Second day of classes\nOn 01/10/2019: Go to lunch\n") {
        std::cout
                << "displayRem doesn't successfully display reminders in a range of two given dates"
                << std::endl;
    }
    if (cal1.displayRem(d5, d6) != "") {
        std::cout << "displayRem doesn't display empty string for invalid date range" << std::endl;
    }
    if (cal1.findRem(d3) != 0) {
        std::cout << "findRem doesn't return correct index" << std::endl;
    }
    if (cal1.findRem(d6) != -1) {
        std::cout << "findRem doesn't return -1 for invalid index" << std::endl;
    }
    if (cal1.findRem(str) != 2) {
        std::cout << "findRem doesn't return correct index when given a string supposed to be 2 but shows"
                     "" << cal1.findRem(str)<< std::endl;
    }
    if (cal1.findRem(badStr) != -1) {
        std::cout << "findRem doesn't return -1 for invalid string" << std::endl;
    }

//reminders to be deleted

    Date d8(01, 11, 2019);
    Reminder rem8(d8, "Pick up syllabus");
    cal1.addRem(rem8);
    Date d9("01/25/2019");
    Reminder rem9(d9, "Go to lunch");
    cal1.addRem(rem9);

    if (cal1.deleteRem(3) != 1) {
        std::cout << "deleteRem doesn't delete properly at given index" << std::endl;
    }
    if (cal1.deleteRem(str) != 1) {
        std::cout << "deleteRem doesn't delete properly given a string" << std::endl;
    }
    if (cal1.deleteRem(d8) != 1) {
        std::cout << "deleteRem doesn't delete properly at given date" << std::endl;
    }

    if (cal1.deleteRem(d5, d6) != 0) {
        std::cout << "deleteRem doesn't return 0 when there is an invalid date range"
                  << std::endl;
    }

    if (cal1.findRem(d9) != 2) {
        std::cout << "The elements in the array didn't properly shift after a deletion"
                  << std::endl;
    }
    if (cal1.deleteRem() != 2) {
        std::cout << "deleteRem doesn't return the correct number of deleted reminders"
                  << std::endl;
    }
}