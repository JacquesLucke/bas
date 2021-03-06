#include <forward_list>

#include "bas/vector.h"

#include "gtest/gtest.h"

using namespace bas;

TEST(vector, DefaultConstructor)
{
    Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
}

TEST(vector, SizeConstructor)
{
    Vector<int> vec(3);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec[1], 0);
    EXPECT_EQ(vec[2], 0);
}

TEST(vector, SizeValueConstructor)
{
    Vector<int> vec(4, 10);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 10);
    EXPECT_EQ(vec[2], 10);
    EXPECT_EQ(vec[3], 10);
}

TEST(vector, InitializerListConstructor)
{
    Vector<int> vec = {1, 3, 4, 6};
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 4);
    EXPECT_EQ(vec[3], 6);
}

TEST(vector, SequenceConstructor)
{
    std::forward_list<int> list;
    list.push_front(3);
    list.push_front(1);
    list.push_front(5);

    Vector<int> vec = Vector<int>::FromSequence(list);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec[2], 3);
}

TEST(vector, CopyConstructor)
{
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2(vec1);
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);

    vec1[1] = 5;
    EXPECT_EQ(vec1[1], 5);
    EXPECT_EQ(vec2[1], 2);
}

TEST(vector, CopyConstructor2)
{
    Vector<int, 2> vec1 = {1, 2, 3, 4};
    Vector<int, 3> vec2(vec1);

    EXPECT_EQ(vec1.size(), 4);
    EXPECT_EQ(vec2.size(), 4);
    EXPECT_NE(vec1.begin(), vec2.begin());
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);
    EXPECT_EQ(vec2[3], 4);
}

TEST(vector, CopyConstructor3)
{
    Vector<int, 20> vec1 = {1, 2, 3, 4};
    Vector<int, 1> vec2(vec1);

    EXPECT_EQ(vec1.size(), 4);
    EXPECT_EQ(vec2.size(), 4);
    EXPECT_NE(vec1.begin(), vec2.begin());
    EXPECT_EQ(vec2[2], 3);
}

TEST(vector, CopyConstructor4)
{
    Vector<int, 5> vec1 = {1, 2, 3, 4};
    Vector<int, 6> vec2(vec1);

    EXPECT_EQ(vec1.size(), 4);
    EXPECT_EQ(vec2.size(), 4);
    EXPECT_NE(vec1.begin(), vec2.begin());
    EXPECT_EQ(vec2[3], 4);
}

TEST(vector, MoveConstructor)
{
    Vector<int> vec1 = {1, 2, 3, 4};
    Vector<int> vec2(std::move(vec1));

    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec2.size(), 4);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);
    EXPECT_EQ(vec2[3], 4);
}

TEST(vector, MoveConstructor2)
{
    Vector<int, 2> vec1 = {1, 2, 3, 4};
    Vector<int, 3> vec2(std::move(vec1));

    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec2.size(), 4);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);
    EXPECT_EQ(vec2[3], 4);
}

TEST(vector, MoveConstructor3)
{
    Vector<int, 20> vec1 = {1, 2, 3, 4};
    Vector<int, 1> vec2(std::move(vec1));

    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec2.size(), 4);
    EXPECT_EQ(vec2[2], 3);
}

TEST(vector, MoveConstructor4)
{
    Vector<int, 5> vec1 = {1, 2, 3, 4};
    Vector<int, 6> vec2(std::move(vec1));

    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec2.size(), 4);
    EXPECT_EQ(vec2[3], 4);
}

TEST(vector, MoveAssignment)
{
    Vector<int> vec = {1, 2};
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);

    vec = Vector<int>({5});
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 5);
}

TEST(vector, CopyAssignment)
{
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2 = {4, 5};
    EXPECT_EQ(vec1.size(), 3);
    EXPECT_EQ(vec2.size(), 2);

    vec2 = vec1;
    EXPECT_EQ(vec2.size(), 3);

    vec1[0] = 7;
    EXPECT_EQ(vec1[0], 7);
    EXPECT_EQ(vec2[0], 1);
}

TEST(vector, Append)
{
    Vector<int> vec;
    vec.append(3);
    vec.append(6);
    vec.append(7);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 3);
    EXPECT_EQ(vec[1], 6);
    EXPECT_EQ(vec[2], 7);
}

TEST(vector, AppendAndGetIndex)
{
    Vector<int> vec;
    EXPECT_EQ(vec.append_and_get_index(10), 0);
    EXPECT_EQ(vec.append_and_get_index(10), 1);
    EXPECT_EQ(vec.append_and_get_index(10), 2);
    vec.append(10);
    EXPECT_EQ(vec.append_and_get_index(10), 4);
}

TEST(vector, AppendNonDuplicates)
{
    Vector<int> vec;
    vec.append_non_duplicates(4);
    EXPECT_EQ(vec.size(), 1);
    vec.append_non_duplicates(5);
    EXPECT_EQ(vec.size(), 2);
    vec.append_non_duplicates(4);
    EXPECT_EQ(vec.size(), 2);
}

TEST(vector, ExtendNonDuplicates)
{
    Vector<int> vec;
    vec.extend_non_duplicates({1, 2});
    EXPECT_EQ(vec.size(), 2);
    vec.extend_non_duplicates({3, 4});
    EXPECT_EQ(vec.size(), 4);
    vec.extend_non_duplicates({0, 1, 2, 3});
    EXPECT_EQ(vec.size(), 5);
}

TEST(vector, Fill)
{
    Vector<int> vec(5);
    vec.fill(3);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 3);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 3);
    EXPECT_EQ(vec[4], 3);
}

TEST(vector, FillIndices)
{
    Vector<int> vec(5, 0);
    vec.fill_indices({1, 2}, 4);
    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec[2], 4);
    EXPECT_EQ(vec[3], 0);
    EXPECT_EQ(vec[4], 0);
}

TEST(vector, Iterator)
{
    Vector<int> vec({1, 4, 9, 16});
    int i = 1;
    for (int value : vec) {
        EXPECT_EQ(value, i * i);
        i++;
    }
}

TEST(vector, BecomeLarge)
{
    Vector<int> vec;
    for (int i = 0; i < 100; i++) {
        vec.append(i * 5);
    }
    EXPECT_EQ(vec.size(), 100);
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(vec[i], i * 5);
    }
}

static Vector<int> return_by_value_helper()
{
    return Vector<int>({3, 5, 1});
}

TEST(vector, ReturnByValue)
{
    Vector<int> vec = return_by_value_helper();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 3);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 1);
}

TEST(vector, VectorOfVectors_Append)
{
    Vector<Vector<int>> vec;
    EXPECT_EQ(vec.size(), 0);

    Vector<int> v({1, 2});
    vec.append(v);
    vec.append({7, 8});
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0][0], 1);
    EXPECT_EQ(vec[0][1], 2);
    EXPECT_EQ(vec[1][0], 7);
    EXPECT_EQ(vec[1][1], 8);
}

TEST(vector, VectorOfVectors_Fill)
{
    Vector<Vector<int>> vec(3);
    vec.fill({4, 5});

    EXPECT_EQ(vec[0][0], 4);
    EXPECT_EQ(vec[0][1], 5);
    EXPECT_EQ(vec[1][0], 4);
    EXPECT_EQ(vec[1][1], 5);
    EXPECT_EQ(vec[2][0], 4);
    EXPECT_EQ(vec[2][1], 5);
}

TEST(vector, RemoveLast)
{
    Vector<int> vec = {5, 6};
    EXPECT_EQ(vec.size(), 2);
    vec.remove_last();
    EXPECT_EQ(vec.size(), 1);
    vec.remove_last();
    EXPECT_EQ(vec.size(), 0);
}

TEST(vector, IsEmpty)
{
    Vector<int> vec;
    EXPECT_TRUE(vec.is_empty());
    vec.append(1);
    EXPECT_FALSE(vec.is_empty());
    vec.remove_last();
    EXPECT_TRUE(vec.is_empty());
}

TEST(vector, RemoveReorder)
{
    Vector<int> vec = {4, 5, 6, 7};
    vec.remove_and_reorder(1);
    EXPECT_EQ(vec[0], 4);
    EXPECT_EQ(vec[1], 7);
    EXPECT_EQ(vec[2], 6);
    vec.remove_and_reorder(2);
    EXPECT_EQ(vec[0], 4);
    EXPECT_EQ(vec[1], 7);
    vec.remove_and_reorder(0);
    EXPECT_EQ(vec[0], 7);
    vec.remove_and_reorder(0);
    EXPECT_TRUE(vec.is_empty());
}

TEST(vector, RemoveFirstOccurrenceAndReorder)
{
    Vector<int> vec = {4, 5, 6, 7};
    vec.remove_first_occurrence_and_reorder(5);
    EXPECT_EQ(vec[0], 4);
    EXPECT_EQ(vec[1], 7);
    EXPECT_EQ(vec[2], 6);
    vec.remove_first_occurrence_and_reorder(6);
    EXPECT_EQ(vec[0], 4);
    EXPECT_EQ(vec[1], 7);
    vec.remove_first_occurrence_and_reorder(4);
    EXPECT_EQ(vec[0], 7);
    vec.remove_first_occurrence_and_reorder(7);
    EXPECT_EQ(vec.size(), 0);
}

TEST(vector, ExtendVector)
{
    Vector<int> a = {2, 3, 4};
    Vector<int> b = {11, 12};
    b.extend(a);
    EXPECT_EQ(b.size(), 5);
    EXPECT_EQ(b[0], 11);
    EXPECT_EQ(b[1], 12);
    EXPECT_EQ(b[2], 2);
    EXPECT_EQ(b[3], 3);
    EXPECT_EQ(b[4], 4);
}

TEST(vector, ExtendArray)
{
    int array[] = {3, 4, 5, 6};

    Vector<int> a;
    a.extend(array, 2);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a[0], 3);
    EXPECT_EQ(a[1], 4);
}

TEST(vector, Last)
{
    Vector<int> a{3, 5, 7};
    EXPECT_EQ(a.last(), 7);
}

TEST(vector, AppendNTimes)
{
    Vector<int> a;
    a.append_n_times(5, 3);
    a.append_n_times(2, 2);
    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(a[0], 5);
    EXPECT_EQ(a[1], 5);
    EXPECT_EQ(a[2], 5);
    EXPECT_EQ(a[3], 2);
    EXPECT_EQ(a[4], 2);
}

TEST(vector, UniquePtrValue)
{
    Vector<std::unique_ptr<int>> vec;
    vec.append(std::unique_ptr<int>(new int()));
    vec.append(std::unique_ptr<int>(new int()));
    vec.append(std::unique_ptr<int>(new int()));

    std::unique_ptr<int> &a = vec.last();
    std::unique_ptr<int> b = vec.pop_last();
    vec.remove_and_reorder(0);

    BAS_UNUSED_VAR(a);
    BAS_UNUSED_VAR(b);
}
