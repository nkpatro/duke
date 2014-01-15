#include <gtest/gtest.h>

#include <duke/attributes/AttributeKeys.hpp>
#include <duke/attributes/NewAttributes.hpp>
#include <glm/glm.hpp>

using namespace std;

struct PlainOldData {
    double a;
    int b;
    bool operator==(const PlainOldData& other) const {
        return a == other.a && b == other.b;
    }
};

enum Enum { ONE, TWO };

namespace attribute {

DECLARE_ATTRIBUTE(std::string, StringAttribute);
DECLARE_ATTRIBUTE(uint64_t, Uint64Attribute);
DECLARE_ATTRIBUTE(PlainOldData, PODAttribute);
DECLARE_ATTRIBUTE(Enum, EnumAttribute);

} /* namespace attribute */

using namespace attribute;

template<typename T>
void testSuite(const typename T::value_type& defaultValue, const typename T::value_type& value) {
    Attributes attributes;
    EXPECT_FALSE(attributes.contains<T>());
    EXPECT_EQ(attributes.getWithDefault<T>(defaultValue), defaultValue);
    attributes.set<T>(value);
    EXPECT_TRUE(attributes.contains<T>());
    EXPECT_EQ(attributes.getOrDie<T>(), value);
    EXPECT_EQ(attributes.getWithDefault<T>(defaultValue), value);
    attributes.erase<T>();
    EXPECT_FALSE(attributes.contains<T>());
}

TEST(Attributes, string) {
    testSuite<StringAttribute>("default", "value");
}

TEST(Attributes, integral) {
    testSuite<Uint64Attribute>(0ULL, 123ULL);
}

TEST(Attributes, POD) {
    testSuite<PODAttribute>( { 0.0, 0 }, { 1.0, 1 });
}

TEST(Attributes, enum) {
    testSuite<EnumAttribute>(Enum::ONE, Enum::TWO);
}
