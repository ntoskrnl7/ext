#include <ext/debug_utils>

#include <gtest/gtest.h>

TEST(debug_utils_test, build_test)
{
    msleep(1000);
    is_debugger_present();
    wait_for_debugger(1000);
}