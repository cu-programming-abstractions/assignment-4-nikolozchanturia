#include "WinSumLoseSum.h"
using namespace std;

Optional<Set<int>> makeTarget(const Set<int>& elems, int target) {
    if (target == 0) {
        return Set<int>();
    }
    if (elems.isEmpty()) {
        return Nothing;
    }

    int first = *elems.begin();
    Set<int> rest = elems - first;

    Optional<Set<int>> exclude = makeTarget(rest, target);
    if (exclude != Nothing) {
        return exclude;
    }

    Optional<Set<int>> include = makeTarget(rest, target - first);
    if (include != Nothing) {
        include.value().add(first);
        return include;
    }

    return Nothing;
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

STUDENT_TEST("Can find subset that sums to 14") {
    Set<int> elems = {3, 4, 7, 10};
    int target = 14;

    Optional<Set<int>> result = makeTarget(elems, target);

    if (result != Nothing) {
        cout << "Subset found: " << result.value() << endl;
    } else {
        cout << "No subset found for target " << target << endl;
    }
}




/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("Works for an empty set of numbers.") {
    /* Can make 0, but not others. */
    EXPECT_EQUAL(makeTarget({ },  0), {});
    EXPECT_EQUAL(makeTarget({ },  1), Nothing);
    EXPECT_EQUAL(makeTarget({ }, -1), Nothing);
}

PROVIDED_TEST("Works for a one-element (singleton) set.") {
    /* Can make 0 and 137, but not others. */
    EXPECT_EQUAL(makeTarget({ 137 }, 0),   {});
    EXPECT_EQUAL(makeTarget({ 137 }, 137), {137});
    EXPECT_EQUAL(makeTarget({ 137 }, 1),   Nothing);
    EXPECT_EQUAL(makeTarget({ 137 }, -1),  Nothing);
}

PROVIDED_TEST("Works for a two-element (doubleton) set.") {
    EXPECT_EQUAL(makeTarget({ 1, 2 }, -1), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 0), {});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 1), {1});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 2), {2});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 3), {1, 2});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 4), Nothing);
}

PROVIDED_TEST("Works for a three-element set.") {

    /* Can make 0, 1, 3, 4, 5, 7, and 8, but not others. */
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 }, -1), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  0), {});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  1), {1});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  2), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  3), {3});
    EXPECT_NOT_EQUAL(makeTarget({ 1, 3, 4 }, 4), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  5), {1, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  6), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  7), {3, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  8), {1, 3, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  9), Nothing);
}
