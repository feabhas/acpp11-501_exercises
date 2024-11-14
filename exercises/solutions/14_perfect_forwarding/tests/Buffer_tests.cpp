// defined in CMakeLists.txt
// #define DOCTEST_CONFIG_NO_MULTITHREADING
// #define DOCTEST_CONFIG_NO_POSIX_SIGNALS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Buffer.h"

TEST_CASE("Testing empty state") {
    Utility::Buffer<unsigned, 10> buffer{};
    CHECK_EQ(buffer.size(), 0);
    CHECK(buffer.is_empty());
    CHECK_FALSE(buffer.get().has_value());
}

TEST_CASE("Testing single element add/get") {
    Utility::Buffer<unsigned, 10> buffer{};
    CHECK(buffer.add(42u));
    CHECK_EQ(buffer.size(), 1);
    CHECK_FALSE(buffer.is_empty());
    
    auto value = buffer.get();
    CHECK(value.has_value());
    CHECK_EQ(value.value(), 42u);
    CHECK(buffer.is_empty());
}

TEST_CASE("Testing fill and empty cycle") {
    Utility::Buffer<unsigned, 3> buffer{};
    
    // Fill buffer
    CHECK(buffer.add(1u));
    CHECK(buffer.add(2u));
    CHECK(buffer.add(3u));
    CHECK_FALSE(buffer.add(4u));  // Should fail, buffer full
    CHECK_EQ(buffer.size(), 3);

    // Empty buffer
    auto val1 = buffer.get();
    auto val2 = buffer.get();
    auto val3 = buffer.get();
    CHECK_EQ(val1.value(), 1u);
    CHECK_EQ(val2.value(), 2u);
    CHECK_EQ(val3.value(), 3u);
    CHECK_FALSE(buffer.get().has_value());  // Should be empty
}

TEST_CASE("Testing wrap-around behavior") {
    Utility::Buffer<unsigned, 4> buffer{};
    
    // Fill buffer
    CHECK(buffer.add(1u));
    CHECK(buffer.add(2u));
    CHECK(buffer.add(3u));
    CHECK(buffer.add(4u));

    // Read half
    CHECK_EQ(buffer.get().value(), 1u);
    CHECK_EQ(buffer.get().value(), 2u);
    
    // Add more (should wrap around)
    CHECK(buffer.add(5u));
    CHECK(buffer.add(6u));
    
    // Read all remaining
    CHECK_EQ(buffer.get().value(), 3u);
    CHECK_EQ(buffer.get().value(), 4u);
    CHECK_EQ(buffer.get().value(), 5u);
    CHECK_EQ(buffer.get().value(), 6u);
    CHECK(buffer.is_empty());
}
