#include "gtest/gtest.h"

#include "bas/string_ref.h"
#include "bas/vector.h"

using namespace bas;

TEST(string_ref_null, DefaultConstructor)
{
    StringRefNull ref;
    EXPECT_EQ(ref.size(), 0);
    EXPECT_EQ(ref[0], '\0');
}

TEST(string_ref_null, CStringConstructor)
{
    const char *str = "Hello";
    StringRefNull ref(str);
    EXPECT_EQ(ref.size(), 5);
    EXPECT_EQ(ref.data(), str);
}

TEST(string_ref_null, CStringLengthConstructor)
{
    const char *str = "Hello";
    StringRefNull ref(str, 5);
    EXPECT_EQ(ref.size(), 5);
    EXPECT_EQ(ref.data(), str);
}

TEST(string_ref, DefaultConstructor)
{
    StringRef ref;
    EXPECT_EQ(ref.size(), 0);
}

TEST(string_ref, CStringConstructor)
{
    const char *str = "Test";
    StringRef ref(str);
    EXPECT_EQ(ref.size(), 4);
    EXPECT_EQ(ref.data(), str);
}

TEST(string_ref, PointerWithLengthConstructor)
{
    const char *str = "Test";
    StringRef ref(str, 2);
    EXPECT_EQ(ref.size(), 2);
    EXPECT_EQ(ref.data(), str);
}

TEST(string_ref, StdStringConstructor)
{
    std::string str = "Test";
    StringRef ref(str);
    EXPECT_EQ(ref.size(), 4);
    EXPECT_EQ(ref.data(), str.data());
}

TEST(string_ref, SubscriptOperator)
{
    StringRef ref("hello");
    EXPECT_EQ(ref.size(), 5);
    EXPECT_EQ(ref[0], 'h');
    EXPECT_EQ(ref[1], 'e');
    EXPECT_EQ(ref[2], 'l');
    EXPECT_EQ(ref[3], 'l');
    EXPECT_EQ(ref[4], 'o');
}

TEST(string_ref, ToStdString)
{
    StringRef ref("test");
    std::string str = ref;
    EXPECT_EQ(str.size(), 4);
    EXPECT_EQ(str, "test");
}

TEST(string_ref, Print)
{
    StringRef ref("test");
    std::stringstream ss;
    ss << ref;
    ss << ref;
    std::string str = ss.str();
    EXPECT_EQ(str.size(), 8);
    EXPECT_EQ(str, "testtest");
}

TEST(string_ref, Add)
{
    StringRef a("qwe");
    StringRef b("asd");
    std::string result = a + b;
    EXPECT_EQ(result, "qweasd");
}

TEST(string_ref, AddCharPtr1)
{
    StringRef ref("test");
    std::string result = ref + "qwe";
    EXPECT_EQ(result, "testqwe");
}

TEST(string_ref, AddCharPtr2)
{
    StringRef ref("test");
    std::string result = "qwe" + ref;
    EXPECT_EQ(result, "qwetest");
}

TEST(string_ref, AddString1)
{
    StringRef ref("test");
    std::string result = ref + std::string("asd");
    EXPECT_EQ(result, "testasd");
}

TEST(string_ref, AddString2)
{
    StringRef ref("test");
    std::string result = std::string("asd") + ref;
    EXPECT_EQ(result, "asdtest");
}

TEST(string_ref, CompareEqual)
{
    StringRef ref1("test");
    StringRef ref2("test");
    StringRef ref3("other");
    EXPECT_TRUE(ref1 == ref2);
    EXPECT_FALSE(ref1 == ref3);
    EXPECT_TRUE(ref1 != ref3);
    EXPECT_FALSE(ref1 != ref2);
}

TEST(string_ref, CompareEqualCharPtr1)
{
    StringRef ref("test");
    EXPECT_TRUE(ref == "test");
    EXPECT_FALSE(ref == "other");
    EXPECT_TRUE(ref != "other");
    EXPECT_FALSE(ref != "test");
}

TEST(string_ref, CompareEqualCharPtr2)
{
    StringRef ref("test");
    EXPECT_TRUE("test" == ref);
    EXPECT_FALSE("other" == ref);
    EXPECT_TRUE(ref != "other");
    EXPECT_FALSE(ref != "test");
}

TEST(string_ref, CompareEqualString1)
{
    StringRef ref("test");
    EXPECT_TRUE(ref == std::string("test"));
    EXPECT_FALSE(ref == std::string("other"));
    EXPECT_TRUE(ref != std::string("other"));
    EXPECT_FALSE(ref != std::string("test"));
}

TEST(string_ref, CompareEqualString2)
{
    StringRef ref("test");
    EXPECT_TRUE(std::string("test") == ref);
    EXPECT_FALSE(std::string("other") == ref);
    EXPECT_TRUE(std::string("other") != ref);
    EXPECT_FALSE(std::string("test") != ref);
}

TEST(string_ref, Iterate)
{
    StringRef ref("test");
    Vector<char> chars;
    for (char c : ref) {
        chars.append(c);
    }
    EXPECT_EQ(chars.size(), 4);
    EXPECT_EQ(chars[0], 't');
    EXPECT_EQ(chars[1], 'e');
    EXPECT_EQ(chars[2], 's');
    EXPECT_EQ(chars[3], 't');
}

TEST(string_ref, StartsWith)
{
    StringRef ref("test");
    EXPECT_TRUE(ref.startswith(""));
    EXPECT_TRUE(ref.startswith("t"));
    EXPECT_TRUE(ref.startswith("te"));
    EXPECT_TRUE(ref.startswith("tes"));
    EXPECT_TRUE(ref.startswith("test"));
    EXPECT_FALSE(ref.startswith("test "));
    EXPECT_FALSE(ref.startswith("a"));
}

TEST(string_ref, EndsWith)
{
    StringRef ref("test");
    EXPECT_TRUE(ref.endswith(""));
    EXPECT_TRUE(ref.endswith("t"));
    EXPECT_TRUE(ref.endswith("st"));
    EXPECT_TRUE(ref.endswith("est"));
    EXPECT_TRUE(ref.endswith("test"));
    EXPECT_FALSE(ref.endswith(" test"));
    EXPECT_FALSE(ref.endswith("a"));
}

TEST(string_ref, DropPrefixN)
{
    StringRef ref("test");
    StringRef ref2 = ref.drop_prefix(2);
    StringRef ref3 = ref2.drop_prefix(2);
    EXPECT_EQ(ref2.size(), 2);
    EXPECT_EQ(ref3.size(), 0);
    EXPECT_EQ(ref2, "st");
    EXPECT_EQ(ref3, "");
}

TEST(string_ref, DropPrefix)
{
    StringRef ref("test");
    StringRef ref2 = ref.drop_prefix("tes");
    EXPECT_EQ(ref2.size(), 1);
    EXPECT_EQ(ref2, "t");
}

TEST(string_ref, Substr)
{
    StringRef ref("hello world");
    EXPECT_EQ(ref.substr(0, 5), "hello");
    EXPECT_EQ(ref.substr(4, 0), "");
    EXPECT_EQ(ref.substr(3, 4), "lo w");
    EXPECT_EQ(ref.substr(6, 5), "world");
}

TEST(string_ref, StartsWithChar)
{
    StringRef ref("hello world");
    EXPECT_TRUE(ref.startswith('h'));
    EXPECT_FALSE(ref.startswith('a'));
}

TEST(string_ref, EndsWithChar)
{
    StringRef ref("hello world");
    EXPECT_TRUE(ref.endswith('d'));
    EXPECT_FALSE(ref.endswith('a'));
}

TEST(string_ref, StartsWithLowerAscii)
{
    {
        StringRef ref("hello");
        EXPECT_TRUE(ref.startswith_lower_ascii("hel"));
        EXPECT_FALSE(ref.startswith_lower_ascii("el"));
    }
    {
        StringRef ref("HELLO");
        EXPECT_TRUE(ref.startswith_lower_ascii("hel"));
        EXPECT_FALSE(ref.startswith_lower_ascii("el"));
    }
    {
        StringRef ref("Hello");
        EXPECT_TRUE(ref.startswith_lower_ascii("hel"));
        EXPECT_FALSE(ref.startswith_lower_ascii("el"));
    }
}

TEST(string_ref, DropSuffixN)
{
    StringRef ref1("hello world");
    StringRef ref2 = ref1.drop_suffix(4);
    StringRef ref3 = ref2.drop_suffix(7);
    EXPECT_EQ(ref2, "hello w");
    EXPECT_EQ(ref3, "");
}

TEST(string_ref, DropSuffix)
{
    StringRef ref1("hello world");
    StringRef ref2 = ref1.drop_suffix("orld");
    StringRef ref3 = ref2.drop_suffix("hello w");
    EXPECT_EQ(ref2, "hello w");
    EXPECT_EQ(ref3, "");
}

TEST(string_ref, Strip)
{
    StringRef ref("  \ttest \n ");
    EXPECT_EQ(ref.lstrip(), "test \n ");
    EXPECT_EQ(ref.rstrip(), "  \ttest");
    EXPECT_EQ(ref.strip(), "test");
    EXPECT_EQ(ref.lstrip({' ', '\t', 't'}), "est \n ");
    EXPECT_EQ(ref.strip({' ', '\t', '\n', 't'}), "es");
}

TEST(string_ref_null, Strip)
{
    StringRefNull ref1("  test  ");
    StringRefNull ref2 = ref1.lstrip();
    EXPECT_EQ(ref2, "test  ");
}

static void test_valid_float_conversion(StringRef str, float expected)
{
    bool success = false;
    float value = str.to_float(&success);
    EXPECT_TRUE(success);
    EXPECT_EQ(value, expected);
}

static void test_invalid_float_conversion(StringRef str)
{
    bool success = true;
    float value = str.to_float(&success);
    EXPECT_FALSE(success);
    EXPECT_EQ(value, 0.0f);
}

TEST(string_ref, ToFloat)
{
    test_valid_float_conversion("25", 25.0f);
    test_valid_float_conversion("2e3", 2000.0f);
    test_valid_float_conversion("12.25", 12.25f);
    test_invalid_float_conversion("abc");
    test_invalid_float_conversion("");
}

TEST(string_ref, Copy)
{
    StringRef ref("hello");
    char dst[10];
    memset(dst, 0xFF, 10);
    ref.copy(dst);
    EXPECT_EQ(dst[5], '\0');
    EXPECT_EQ(dst[6], (char)0xFF);
    EXPECT_EQ(ref, dst);
}
