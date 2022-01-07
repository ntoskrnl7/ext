#include <ext/cdbg>
#include <gtest/gtest.h>

TEST(cdbg_test, cdbg) { ext::cdbg << "test"; }

TEST(cdbg_test, cwdbg) { ext::wcdbg << "test"; }
