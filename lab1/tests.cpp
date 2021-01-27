#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "tritset.h"

TEST_CASE("Memory tests") {

    TritSet set(1000);
    size_t alloc_size = set.capacity();
    REQUIRE(alloc_size >= 1000 * 2 / 8 / sizeof(uint));

    SECTION("UnknownBeyondLimitsTest") {
        set[1'000'000] = Trit::Unknown;

        REQUIRE(set.capacity() == alloc_size);
    }

    SECTION("ComparisonBeyondLimitsTest") {
        if (set[2'000'000] == Trit::True) {}

        REQUIRE(set.capacity() == alloc_size);
    }

    SECTION("UnknownInitialisationTest") {
        bool result = (set[500] == Trit::Unknown);
        REQUIRE(result == true);
    }

    SECTION("InitialisationTest") {
        set[500] = Trit::True;
        bool result = (set[500] == Trit::True);
        REQUIRE(result == true);
    }

    SECTION("InitialisationBeyondLimitsTest") {
        set[10'000] = Trit::True;

        REQUIRE(alloc_size < set.capacity());
    }

    SECTION("InitialisationAfterSizeChangeTest") {
        set[10'000] = Trit::True;
        alloc_size = set.capacity();
        set[10'000] = Trit::Unknown;
        set[1'000] = Trit::False;

        REQUIRE(alloc_size == set.capacity());
    }

    SECTION("ShrinkTest(not original size)") {
        set[10'000] = Trit::True;
        alloc_size = set.capacity();
        set[10'000] = Trit::Unknown;
        set[2'000] = Trit::False;
        set.shrink();

        REQUIRE(alloc_size > set.capacity());
    }

    SECTION("ShrinkTest(original size)") {
        set[10'000] = Trit::True;
        alloc_size = set.capacity();
        set[10'000] = Trit::Unknown;
        set.shrink();

        REQUIRE(alloc_size > set.capacity());
    }
}

TEST_CASE("Logic operations tests") {
    TritSet setA(1000);
    TritSet setB(2000);

    SECTION("& test") {
        setA = setA & setB;
        TritSet setC(setA);
        REQUIRE(setC.capacity() == setB.capacity());
    }

    SECTION("| test") {
        setA = setA | setB;
        TritSet setC(setA);
        REQUIRE(setC.capacity() == setB.capacity());
    }

    SECTION("~ test") {
        setA = ~setA;
        TritSet setC(setA);
        REQUIRE(setC.capacity() == setA.capacity());
    }

    SECTION("== test") {
        setA[500] = Trit::True;
        bool result = (setA == setA);
        REQUIRE(result == true);
    }

    SECTION("!= test") {
        TritSet setB(setA);
        setA[500] = Trit::True;
        bool result = setA != setB;
        REQUIRE(result == true);
    }
}

TEST_CASE("other operations tests") {
    TritSet set(7);

    set[0] = Trit::True;
    set[1] = Trit::Unknown;
    set[2] = Trit::False;
    set[3] = Trit::False;
    set[4] = Trit::Unknown;
    set[5] = Trit::True;
    set[6] = Trit::Unknown;
    SECTION("CardinalityTets") {
        REQUIRE(set.cardinality(Trit::False) == 2);
        REQUIRE(set.cardinality(Trit::True) == 2);
        REQUIRE(set.cardinality(Trit::Unknown) == 3);
    }

    SECTION("CardinalityTest(unordered_map)") {
        auto a = set.cardinality();

        REQUIRE(a[Trit::True] == 2);
        REQUIRE(a[Trit::False] == 2);
        REQUIRE(a[Trit::Unknown] == 3);
    }

    SECTION("TrimTest") {
        set.trim(3);
        bool result = set[3] == Trit::Unknown && set[4] == Trit::Unknown && set[5] == Trit::Unknown && set[6] == Trit::Unknown;
        REQUIRE(result == true);
    }

    SECTION("LengthTest") {
        REQUIRE(set.length() == 6);
    }
}