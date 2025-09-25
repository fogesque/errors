#include <iterator>
#include <memory>
#include <print>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "errors.hpp"

class ErrorExamples
{
private:
    using Data = std::vector<int>;
    using DataPtr = std::shared_ptr<Data>;

    // Simulates an operation that fails and returns an error
    static std::tuple<DataPtr, error> FailingOperation()
    {
        return { {}, errors::New("operation failed") };
    }

    // Simulates an operation that succeeds and returns data
    static std::tuple<DataPtr, error> SuccessfulOperation()
    {
        return { std::make_shared<Data>(Data{ 1, 2, 3 }), nullptr };
    }

public:
    // Example 0: Base code flow with errors package
    static void ExampleCodeFlow()
    {
        auto [data0, err0] = FailingOperation();
        if (err0) {
            std::println("FailingOperation error: {}", err0->What());
        }

        auto [data1, err1] = SuccessfulOperation();
        if (err1) {
            std::println("SuccessfulOperation error: {}", err1->What());
            return;
        }
        std::stringstream vec_str;
        std::copy(data1->begin(), data1->end(), std::ostream_iterator<int>(vec_str, " "));
        std::println("SuccessfulOperation data: {}", vec_str.str());
    }

    // Example 1: Creating a simple error with New()
    static void ExampleNew()
    {
        auto err = errors::New("something went wrong");
        std::println("New: {}", err->What());
    }

    // Example 2: Creating a formatted error with Errorf()
    static void ExampleErrorf()
    {
        auto err = errors::Errorf("error code %d: %s", 404, "not found");
        std::println("Errorf: {}", err->What());
    }

    // Example 3: Wrapping an error with a static message using Wrap()
    static void ExampleWrap()
    {
        auto base = errors::New("disk full");
        auto wrapped = errors::Wrap(base, "failed to save file");
        std::println("Wrap: {}", wrapped->What());
    }

    // Example 4: Wrapping an error with a formatted message using Wrapf()
    static void ExampleWrapf()
    {
        auto base = errors::New("connection refused");
        auto wrapped = errors::Wrapf(base, "attempt %d failed", 3);
        std::println("Wrapf: {}", wrapped->What());
    }

    // Example 5: Joining multiple errors with Join()
    static void ExampleJoin()
    {
        auto err1 = errors::New("error one");
        auto err2 = errors::New("error two");
        auto joined = errors::Join(err1, err2);
        std::println("Join:\n{}", joined->What());
    }

    // Example 6: Using Is() to check if an error is in the chain
    static void ExampleIs()
    {
        auto base = errors::New("root");
        auto wrapped = errors::Wrap(base, "context");
        bool found = errors::Is(wrapped, base);
        std::println("Is: {}", found ? "true" : "false");
    }

    // Example 7: Using As() to check for a specific error type
    static void ExampleAs()
    {
        auto err = errors::New("type test");
        std::shared_ptr<errors::StringError> specific;
        bool matched = errors::As<errors::StringError>(err, &specific);
        std::println("As: {}", matched ? "matched" : "not matched");
        if (matched) {
            std::println("As What: {}", specific->What());
        }
    }

    // Example 8: Handling nullptr errors
    static void ExampleNullptr()
    {
        error err = nullptr;
        std::println("Nullptr: {}", err ? err->What() : "no error");
    }
};

int main()
{
    ErrorExamples::ExampleCodeFlow();
    ErrorExamples::ExampleNew();
    ErrorExamples::ExampleErrorf();
    ErrorExamples::ExampleWrap();
    ErrorExamples::ExampleWrapf();
    ErrorExamples::ExampleJoin();
    ErrorExamples::ExampleIs();
    ErrorExamples::ExampleAs();
    ErrorExamples::ExampleNullptr();

    return 0;
}