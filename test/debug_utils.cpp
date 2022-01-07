#include <ext/debug_utils.h>

#include <gtest/gtest.h>

TEST(debug_utils_test, build_test)
{
    msleep(100);
    is_debugger_present();
    wait_for_debugger(100);
}