#include <ext/version>
#include <gtest/gtest.h>

#ifdef _EXT_VERSION_
TEST(version_test, invalid) {
  EXPECT_THROW(ext::version v("a.b.c"), std::invalid_argument);
}

TEST(version_test, parse) {
  {
    ext::version v("0.0.4");
    EXPECT_EQ(v.major(), 0);
    EXPECT_EQ(v.minor(), 0);
    EXPECT_EQ(v.patch(), 4);
    EXPECT_EQ(v.prerelease(), "");
    EXPECT_EQ(v.build_metadata(), "");
  }
  {
    ext::version v("1.2.3");
    EXPECT_EQ(v.major(), 1);
    EXPECT_EQ(v.minor(), 2);
    EXPECT_EQ(v.patch(), 3);
    EXPECT_EQ(v.prerelease(), "");
    EXPECT_EQ(v.build_metadata(), "");
  }

  {
    ext::version v("10.20.30");
    EXPECT_EQ(v.major(), 10);
    EXPECT_EQ(v.minor(), 20);
    EXPECT_EQ(v.patch(), 30);
    EXPECT_EQ(v.prerelease(), "");
    EXPECT_EQ(v.build_metadata(), "");
  }
  {
    ext::version v("1.1.2-prerelease+meta");
    EXPECT_EQ(v.major(), 1);
    EXPECT_EQ(v.minor(), 1);
    EXPECT_EQ(v.patch(), 2);
    EXPECT_EQ(v.prerelease(), "prerelease");
    EXPECT_EQ(v.build_metadata(), "meta");
  }
}

TEST(version_test, hash) {
  typedef std::unordered_map<ext::version, std::string> ver_desc;
  ver_desc map;
  map.insert(
      std::pair<ext::version, std::string>(ext::version("1.2.3"), "abc"));

  map.insert(
      std::pair<ext::version, std::string>(ext::version("5.0.0"), "def"));

  map.insert(std::pair<ext::version, std::string>(
      ext::version("1.2.3-prerelease"), "ghi"));

  ver_desc::iterator it = map.find(ext::version("1.2.3"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "abc");

  it = map.find(ext::version("5.0.0"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "def");

  it = map.find(ext::version("1.2.0"));
  EXPECT_EQ(it, map.end());

  it = map.find(ext::version("1.2.3-prerelease"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "ghi");

  it = map.find(ext::version("1.2.3-prerelease+meta"));
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->second, "ghi");

  it = map.find(ext::version("1.2.3-test+meta"));
  EXPECT_EQ(it, map.end());
}

TEST(version_test, comparison) {
  ext::version v1("1.2.3");
  ext::version v2("1.3.2");
  EXPECT_FALSE(v1 > v2);
  EXPECT_LT(v1, v2);
  EXPECT_LE(v1, v2);
  EXPECT_NE(v1, v2);

  v2 = ext::version("1.2.3-prerelease+meta");
  EXPECT_FALSE(v1 < v2);
  EXPECT_GT(v1, v2);
  EXPECT_GE(v1, v2);
  EXPECT_NE(v1, v2);

  v1 = "1.2.3";
  v2 = "1.2.2";
  EXPECT_GT(v1, v2);

  v2 = v1;
  EXPECT_EQ(v1, v2);

  // https://semver.org/#spec-item-10
  EXPECT_EQ(ext::version("1.0.0+20130313144700"),
            ext::version("1.0.0+20130313144700"));

  // https://semver.org/#spec-item-11
  //
  // 11.2
  // Example: 1.0.0 < 2.0.0 < 2.1.0 < 2.1.1.
  EXPECT_TRUE(ext::version("1.0.0") < ext::version("2.0.0"));
  EXPECT_TRUE(ext::version("2.0.0") < ext::version("2.1.0"));
  EXPECT_TRUE(ext::version("2.1.0") < ext::version("2.1.1"));
  //
  // 11.3
  // Example: 1.0.0-alpha < 1.0.0.
  EXPECT_TRUE(ext::version("1.0.0-alpha") < ext::version("1.0.0"));
  //
  // 11.4
  // Example: 1.0.0-alpha < 1.0.0-alpha.1 < 1.0.0-alpha.beta < 1.0.0-beta
  // < 1.0.0-beta.2 < 1.0.0-beta.11 < 1.0.0-rc.1 < 1.0.0. Pre-release value
  // comparison is not implemented yet.
}

TEST(version_test, update) {
  ext::version v1("1.3.2");
  ++v1; // Patch version incremented
  EXPECT_EQ(v1, ext::version("1.3.3"));

  ++v1.minor(); // Minor version incremented
  EXPECT_EQ(v1, ext::version("1.4.0"));

  ++v1.major(); // Major version incremented
  EXPECT_EQ(v1, ext::version("2.0.0"));

  v1.build_metadata("meta+meta");
  EXPECT_NE(v1.build_metadata(), "meta+meta");

  v1.prerelease("alpha_beta");
  EXPECT_NE(v1.prerelease(), "alpha_beta");
  EXPECT_TRUE(v1.released());

  v1.build_metadata("build.1-aef.1-its-okay");
  EXPECT_EQ(v1.build_metadata(), "build.1-aef.1-its-okay");

  v1.prerelease("alpha-a.b-c-somethinglong");
  EXPECT_EQ(v1.prerelease(), "alpha-a.b-c-somethinglong");
  EXPECT_FALSE(v1.released());
}

TEST(version_test, string) {
  ext::version v1("1.3.2");
  std::string ver_str = v1;
  EXPECT_EQ(v1.str(), ver_str);
}
#endif