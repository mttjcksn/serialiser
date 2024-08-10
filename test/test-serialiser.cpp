#include <gtest/gtest.h>
#include "Serialiser.hpp"

// Test serialization and deserialization of a std::map<int, int>
TEST(SerialiserTest, SerialiseDeserialiseMapIntToInt) {
    std::map<int, int> originalMap = {{1, 10}, {2, 20}, {3, 30}};
    std::vector<char> serialisedData = Serialiser::serialise(originalMap);

    std::map<int, int> deserialisedMap;
    Serialiser::deserialise(serialisedData.data(), deserialisedMap);

    // Verify that the deserialized map matches the original
    EXPECT_EQ(originalMap, deserialisedMap);
}

// Test serialization and deserialization of a std::map<std::string, double>
TEST(SerialiserTest, SerialiseDeserialiseMapStringToDouble) {
    std::map<std::string, double> originalMap = {{"pi", 3.14159}, {"e", 2.71828}};
    std::vector<char> serialisedData = Serialiser::serialise(originalMap);

    std::map<std::string, double> deserialisedMap;
    Serialiser::deserialise(serialisedData.data(), deserialisedMap);

    // Verify that the deserialized map matches the original
    EXPECT_EQ(originalMap, deserialisedMap);
}

// Test serialization and deserialization of an std::unordered_map<int, int>
TEST(SerialiserTest, SerialiseDeserialiseUnorderedMapIntToInt) {
    std::unordered_map<int, int> originalMap = {{1, 10}, {2, 20}, {3, 30}};
    std::vector<char> serialisedData = Serialiser::serialise(originalMap);

    std::unordered_map<int, int> deserialisedMap;
    Serialiser::deserialise(serialisedData.data(), deserialisedMap);

    // Verify that the deserialized unordered_map matches the original
    EXPECT_EQ(originalMap, deserialisedMap);
}

// Test serialization and deserialization of an std::unordered_map<std::string, double>
TEST(SerialiserTest, SerialiseDeserialiseUnorderedMapStringToDouble) {
    std::unordered_map<std::string, double> originalMap = {{"pi", 3.14159}, {"e", 2.71828}};
    std::vector<char> serialisedData = Serialiser::serialise(originalMap);

    std::unordered_map<std::string, double> deserialisedMap;
    Serialiser::deserialise(serialisedData.data(), deserialisedMap);

    // Verify that the deserialized unordered_map matches the original
    EXPECT_EQ(originalMap, deserialisedMap);
}

// Test serialization and deserialization of a std::vector<int>
TEST(SerialiserTest, SerialiseDeserialiseVectorInt) {
    std::vector<int> originalVector = {1, 2, 3, 4, 5};
    std::vector<char> serialisedData = Serialiser::serialise(originalVector);

    std::vector<int> deserialisedVector;
    Serialiser::deserialise(serialisedData.data(), deserialisedVector);

    // Verify that the deserialized vector matches the original
    EXPECT_EQ(originalVector, deserialisedVector);
}

// Test serialization and deserialization of a std::vector<std::string>
TEST(SerialiserTest, SerialiseDeserialiseVectorString) {
    std::vector<std::string> originalVector = {"one", "two", "three"};
    std::vector<char> serialisedData = Serialiser::serialise(originalVector);

    std::vector<std::string> deserialisedVector;
    Serialiser::deserialise(serialisedData.data(), deserialisedVector);

    // Verify that the deserialized vector matches the original
    EXPECT_EQ(originalVector, deserialisedVector);
}

// Test serialization and deserialization of a custom complex type
TEST(SerialiserTest, SerialiseDeserialiseComplexType) {
    struct ComplexType {
        int a;
        double b;

        bool operator==(const ComplexType& other) const {
            return a == other.a && b == other.b;
        }

        static std::vector<char> serialise(const ComplexType& obj) {
            std::vector<char> out;
            Serialiser::appendVector(out, Serialiser::serialise(obj.a));
            Serialiser::appendVector(out, Serialiser::serialise(obj.b));
            return out;
        }

        static size_t deserialise(const char* buffer, ComplexType& obj) {
            size_t bytesRead = 0;
            bytesRead += Serialiser::deserialise(buffer, obj.a);
            bytesRead += Serialiser::deserialise(buffer + bytesRead, obj.b);
            return bytesRead;
        }
    };

    ComplexType originalObj = {42, 3.14};
    std::vector<char> serialisedData = Serialiser::serialise(originalObj);

    ComplexType deserialisedObj;
    Serialiser::deserialise(serialisedData.data(), deserialisedObj);

    // Verify that the deserialized complex type matches the original
    EXPECT_EQ(originalObj, deserialisedObj);
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
