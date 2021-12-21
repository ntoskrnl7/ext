#include <gtest/gtest.h>

#include <ext/wordexp>

#include <string>

TEST(wordexp, basic_test) {
#if defined(_WIN32)
  std::string system_drive = ext::wordexp("%SYSTEMDRIVE%");
  std::string windir = ext::wordexp("%WINDIR%");
  std::string user_profile = ext::wordexp("%USERPROFILE%");
  std::string user_name = ext::wordexp("%USERNAME%");

  EXPECT_EQ(windir.rfind(system_drive), 0);
  EXPECT_EQ(user_profile.rfind(system_drive), 0);
  EXPECT_NE(user_profile.find(user_name), std::string::npos);
#else
  std::string home_path = ext::wordexp("$HOME");
  std::string user = ext::wordexp("$USER");

  EXPECT_EQ(windir.rfind("/"), 0);
  EXPECT_EQ(user_profile.rfind("/"), 0);
  EXPECT_NE(home_path.find(user), std::string::npos);
#endif
}