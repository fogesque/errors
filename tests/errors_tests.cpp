#include <gtest/gtest.h>

#include "errors.hpp"

TEST(ErrorsTests, NewCreatesStringError)
{
    auto err = errors::New("test error");
    ASSERT_NE(err, nullptr);
    EXPECT_EQ(err->What(), "test error");
    EXPECT_EQ(err->Unwrap(), nullptr);
    EXPECT_TRUE(err->GetJoined().empty());
}

TEST(ErrorsTests, ErrorfCreatesFormattedStringError)
{
    auto err = errors::Errorf("code %d: %s", 42, "fail");
    ASSERT_NE(err, nullptr);
    EXPECT_EQ(err->What(), "code 42: fail");
}

TEST(ErrorsTests, WrapAddsContext)
{
    auto base = errors::New("base");
    auto wrapped = errors::Wrap(base, "context");
    ASSERT_NE(wrapped, nullptr);
    EXPECT_EQ(wrapped->What(), "context: base");
    EXPECT_EQ(wrapped->Unwrap(), base);
}

TEST(ErrorsTests, WrapfAddsFormattedContext)
{
    auto base = errors::New("base");
    auto wrapped = errors::Wrapf(base, "context %d", 7);
    ASSERT_NE(wrapped, nullptr);
    EXPECT_EQ(wrapped->What(), "context 7: base");
    EXPECT_EQ(wrapped->Unwrap(), base);
}

TEST(ErrorsTests, JoinCombinesMultipleErrors)
{
    auto e1 = errors::New("err1");
    auto e2 = errors::New("err2");
    auto joined = errors::Join(e1, e2);
    ASSERT_NE(joined, nullptr);
    auto joined_str = joined->What();
    EXPECT_NE(joined_str.find("err1"), std::string::npos);
    EXPECT_NE(joined_str.find("err2"), std::string::npos);
    auto joined_vec = joined->GetJoined();
    EXPECT_EQ(joined_vec.size(), 2);
    EXPECT_EQ(joined_vec[0], e1);
    EXPECT_EQ(joined_vec[1], e2);
}

TEST(ErrorsTests, JoinFiltersNullptr)
{
    auto e1 = errors::New("err1");
    error e2 = nullptr;
    auto joined = errors::Join(e1, e2);
    ASSERT_NE(joined, nullptr);
    EXPECT_EQ(joined, e1);  // Only one non-nullptr error
}

TEST(ErrorsTests, IsFindsErrorInChain)
{
    auto base = errors::New("base");
    auto wrap1 = errors::Wrap(base, "ctx1");
    auto wrap2 = errors::Wrap(wrap1, "ctx2");
    EXPECT_TRUE(errors::Is(wrap2, base));
    EXPECT_TRUE(errors::Is(wrap2, wrap1));
    EXPECT_TRUE(errors::Is(wrap2, wrap2));
    EXPECT_FALSE(errors::Is(wrap2, nullptr));
}

TEST(ErrorsTests, IsFindsErrorInJoined)
{
    auto e1 = errors::New("err1");
    auto e2 = errors::New("err2");
    auto joined = errors::Join(e1, e2);
    EXPECT_TRUE(errors::Is(joined, e1));
    EXPECT_TRUE(errors::Is(joined, e2));
}

TEST(ErrorsTests, AsFindsTypeInChain)
{
    auto err = errors::New("msg");
    std::shared_ptr<errors::StringError> specific;
    EXPECT_TRUE(errors::As<errors::StringError>(err, &specific));
    ASSERT_NE(specific, nullptr);
    EXPECT_EQ(specific->What(), "msg");
}

TEST(ErrorsTests, AsFindsTypeInWrapped)
{
    auto base = errors::New("msg");
    auto wrapped = errors::Wrap(base, "ctx");
    std::shared_ptr<errors::StringError> specific;
    EXPECT_TRUE(errors::As<errors::StringError>(wrapped, &specific));
    ASSERT_NE(specific, nullptr);
    EXPECT_EQ(specific->What(), "msg");
}

TEST(ErrorsTests, AsReturnsFalseForWrongType)
{
    auto err = errors::New("msg");
    std::shared_ptr<errors::WrappedError> wrong;
    EXPECT_FALSE(errors::As<errors::WrappedError>(err, &wrong));
    EXPECT_EQ(wrong, nullptr);
}

TEST(ErrorsTests, NullptrErrorBehaviors)
{
    error err = nullptr;
    EXPECT_FALSE(errors::Is(err, errors::New("other")));
    std::shared_ptr<errors::StringError> specific;
    EXPECT_FALSE(errors::As<errors::StringError>(err, &specific));
    auto joined = errors::Join(err);
    EXPECT_EQ(joined, nullptr);
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}