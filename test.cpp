#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"

using namespace custom_bst;
using namespace std;

class Logger {
    ofstream file;
public:
    Logger(const string& filename) { file.open(filename); }
    ~Logger() { if(file.is_open()) file.close(); }

    void log(const string& msg) {
        cout << msg << endl;
        if(file.is_open()) file << msg << endl;
    }
};

Logger testLogger("log.txt");
int passedCount = 0;
int totalCount = 0;

void assertTest(const string& testName, bool condition) {
    totalCount++;
    if (condition) {
        passedCount++;
        testLogger.log(testName + " [PASS]");
    } else {
        testLogger.log(testName + " [FAIL]");
    }
}

int main() {
    BST t1;
    assertTest("Initial size is 0", t1.size() == 0);

    testLogger.log("\nAdding elements 10, 5 and 15.");
    t1 += 10; t1 += 5; t1 += 15;

    assertTest("Tree size is 3", t1.size() == 3);

    assertTest("Search finds existing element (10)", t1[10] == true);
    assertTest("Search finds existing element (5)", t1[5] == true);
    assertTest("Search finds existing element (15)", t1[15] == true);

    assertTest("Search doesn't find element (100)", t1[100] == false);
    assertTest("Search doesn't find element (-5)", t1[-5] == false);
    assertTest("Search doesn't find element (30)", t1[30] == false);
    
    testLogger.log("\nMaking a copy of the BST.");
    BST t2 = t1; 
    assertTest("Deep copy test", t1 == t2);

    testLogger.log("\nAdding 20 to the copy.");
    t2 += 20;
    assertTest("Modifying copy does not affect original", t1 != t2);
    assertTest("Operator < evaluates correctly", t1 < t2);
    assertTest("Operator > evaluates correctly", t2 > t1);
    assertTest("Operator <= evaluates correctly", t1 <= t2);
    assertTest("Operator >= evaluates correctly", t2 >= t1);

    t2 -= 20;
    assertTest("Deleting 20 from copy restoring balance with the original", t1 == t2);

    testLogger.log("\nChanging 15 to 18.");
    t2 *= make_pair(15, 18);
    assertTest("Update: 18 exists after changing 15", t2[18] == true);
    assertTest("Update: 15 no longer exists", t2[15] == false);

    bool caughtCustom = false;
    try { t1 += 10; } catch (const DuplicateNodeException&) { caughtCustom = true; }
    assertTest("Duplicate insertion throws DuplicateNodeException", caughtCustom);

    bool caughtStandard = false;
    try { t1 -= 99; } catch (const std::invalid_argument&) { caughtStandard = true; }
    assertTest("Invalid deletion throws std::invalid_argument", caughtStandard);

    !t1;
    assertTest("Clear operator empties tree", t1.size() == 0 && t1.toString() == "BST [Size: 0] Elements: {  }");

    testLogger.log("\nTests completed: " + to_string(passedCount) + "/" + to_string(totalCount) + " passed.");
    return 0;
}