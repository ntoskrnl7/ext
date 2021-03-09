#include <ext/ini>

#include <gtest/gtest.h>

#include <sstream>
TEST(ini_test, istringstream_test) {
  std::istringstream ss("[TEST]\nX=10\nY=20\n[TEST1]\nZ=30");
  ext::ini ini(ss);
  EXPECT_STREQ(ini["TEST"]["X"].c_str(), "10");
  EXPECT_STREQ(ini["TEST"]["Y"].c_str(), "20");
  EXPECT_STREQ(ini["TEST1"]["Z"].c_str(), "30");

  ini << std::istringstream("[TEST2]\nX=40\nY=50\n[TEST3]\nZ=60");
  EXPECT_STREQ(ini["TEST"]["X"].c_str(), "10");
  EXPECT_STREQ(ini["TEST"]["Y"].c_str(), "20");
  EXPECT_STREQ(ini["TEST1"]["Z"].c_str(), "30");
  EXPECT_STREQ(ini["TEST2"]["X"].c_str(), "40");
  EXPECT_STREQ(ini["TEST2"]["Y"].c_str(), "50");
  EXPECT_STREQ(ini["TEST3"]["Z"].c_str(), "60");

  {
    std::stringstream ss;
    ss << ini;
    EXPECT_STREQ(ss.str().c_str(), "[TEST]\nX=10\nY=20\n[TEST1]\nZ=30\n[TEST2]"
                                   "\nX=40\nY=50\n[TEST3]\nZ=60\n");
  }

  EXPECT_TRUE(ini.contains("TEST"));
  EXPECT_TRUE(ini.contains("TEST", "X"));

  EXPECT_FALSE(ini.contains("TEST5"));
  EXPECT_FALSE(ini.contains("TEST", "A"));
}

#include <fstream>
TEST(ini_test, ifstream_test) {
  {
    std::ofstream ofs("sample.ini");
    ofs << "[TEST]\nX=10\nY=20\n[TEST1]\nZ=30";
  }

  std::ifstream fs("sample.ini");
  ext::ini ini(fs);
  EXPECT_STREQ(ini["TEST"]["X"].c_str(), "10");
  EXPECT_STREQ(ini["TEST"]["Y"].c_str(), "20");
  EXPECT_STREQ(ini["TEST1"]["Z"].c_str(), "30");

  ini["TEST4"]["A"] = "1";
  ini["TEST4"]["B"] = "2";
  ini["TEST4"]["C"] = "3";

  std::cout << ini;
  {
    std::ofstream ofs("sample2.ini");
    ofs << ini;
  }
}

TEST(ini_test, ofstream_test) {
  {
    {
      std::istringstream ss("[TEST]\nX=10\nY=20\n[TEST1]\nZ=30");
      ext::ini ini(ss);
      std::ofstream ofs("sample2.ini");
      ofs << ini;
    }

    {
      std::ifstream ifs("sample2.ini");
      ext::ini ini(ifs);
      EXPECT_STREQ(ini["TEST"]["X"].c_str(), "10");
      EXPECT_STREQ(ini["TEST"]["Y"].c_str(), "20");
      EXPECT_STREQ(ini["TEST1"]["Z"].c_str(), "30");
    }
  }
}