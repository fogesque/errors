#include <iterator>
#include <memory>
#include <print>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "errors/errors.hpp"

class ErrorSamples
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
    // Sample 0: Base code flow with errors package
    static void SampleCodeFlow()
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
        std::stringstream vecStr;
        std::copy(data1->begin(), data1->end(), std::ostream_iterator<int>(vecStr, " "));
        std::println("SuccessfulOperation data: {}", vecStr.str());
    }

    // Sample 1: Creating a simple error with New()
    static void SampleNew()
    {
        auto err = errors::New("something went wrong");
        std::println("New: {}", err->What());
    }

    // Sample 2: Creating a formatted error with Errorf()
    static void SampleErrorf()
    {
        auto err = errors::Errorf("error code {}: {}", 404, "not found");
        std::println("Errorf: {}", err->What());
    }

    // Sample 3: Wrapping an error with a static message using Wrap()
    static void SampleWrap()
    {
        auto base = errors::New("disk full");
        auto wrapped = errors::Wrap(base, "failed to save file");
        std::println("Wrap: {}", wrapped->What());
    }

    // Sample 4: Wrapping an error with a formatted message using Wrapf()
    static void SampleWrapf()
    {
        auto base = errors::New("connection refused");
        auto wrapped = errors::Wrapf(base, "attempt {} failed", 3);
        std::println("Wrapf: {}", wrapped->What());
    }

    // Sample 5: Joining multiple errors with Join()
    static void SampleJoin()
    {
        auto err1 = errors::New("error one");
        auto err2 = errors::New("error two");
        auto joined = errors::Join(err1, err2);
        std::println("Join: {}", joined->What());
    }

    // Sample 6: Using Is() to check if an error is in the chain
    static void SampleIs()
    {
        auto base = errors::New("root");
        auto wrapped = errors::Wrap(base, "context");
        bool found = errors::Is(wrapped, base);
        std::println("Is: {}", found ? "true" : "false");
    }

    // Sample 7: Using As() to check for a specific error type
    static void SampleAs()
    {
        auto err = errors::New("type test");
        std::shared_ptr<errors::StringError> specific;
        bool matched = errors::As<errors::StringError>(err, &specific);
        std::println("As: {}", matched ? "matched" : "not matched");
        if (matched) {
            std::println("As What(): {}", specific->What());
        }
    }

    // Sample 8: Handling nullptr errors
    static void SampleNullptr()
    {
        error err = nullptr;
        std::println("Nullptr: {}", err ? err->What() : "no error");
    }
};

int main()
{
    ErrorSamples::SampleCodeFlow();
    ErrorSamples::SampleNew();
    ErrorSamples::SampleErrorf();
    ErrorSamples::SampleWrap();
    ErrorSamples::SampleWrapf();
    ErrorSamples::SampleJoin();
    ErrorSamples::SampleIs();
    ErrorSamples::SampleAs();
    ErrorSamples::SampleNullptr();

    return 0;
}