#ifndef CATCH_UTIL_H
#define CATCH_UTIL_H


#include <string>
#include "catch.hpp"


#if defined(CATCH_CONFIG_MAIN) || defined(CATCH_CONFIG_RUNNER)
    struct TestCaseNameRecorder final : Catch::TestEventListenerBase
    {
        using TestEventListenerBase::TestEventListenerBase; // inherit constructor

        void testCaseStarting(Catch::TestCaseInfo const& testInfo) override
        { TestCaseNameRecorder::testCaseName_ = testInfo.name; }
        
        void testCaseEnded(Catch::TestCaseStats const& /* testCaseStats */) override
        { TestCaseNameRecorder::testCaseName_.erase(); }

        static std::string testCaseName_;
    };

    std::string TestCaseNameRecorder::testCaseName_{};

    CATCH_REGISTER_LISTENER(TestCaseNameRecorder)

    std::string current_test_case_name()
    { return TestCaseNameRecorder::testCaseName_; }
#else
    std::string current_test_case_name();

#   define THIS_TEST_CASE_NAME current_test_case_name()
#endif


#endif // CATCH_UTIL_H
