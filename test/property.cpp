
#include <ext/property>
#include <gtest/gtest.h>

class dialog {
public:
  dialog(const std::string &name)
      : title([name](const std::string &new_value) {
          std::cout << name << " - title : " << new_value << std::endl;
          return true;
        }),
        contents([name](const std::string &new_value) {
          std::cout << name << " - contents : " << new_value << std::endl;
          return true;
        }) {}

  ext::property<std::string> title;
  ext::property<std::string> contents;
  ext::property<int> total;
};

class table_data {
public:
  ext::property<std::string> id;
  ext::property<std::string> phone;
  ext::property<std::string> name;
  ext::property<int> count;
};

TEST(property_test, table_veiwer_test) {
  dialog dlg("dialog 1");
  dialog dlg2("dialog 2");
  table_data data;
  table_data data2;

  data.id = data2.id;
  data.id = "test";
  dlg2.title = data.id;
  dlg.title = data.id;
  EXPECT_STREQ(data.id.value().c_str(), "test");
  EXPECT_STREQ(data2.id.value().c_str(), "test");
  EXPECT_STREQ(dlg.title.value().c_str(), "test");
  EXPECT_STREQ(dlg2.title.value().c_str(), "test");

  data.id = "test2";
  EXPECT_STREQ(data.id.value().c_str(), "test2");
  EXPECT_STREQ(data2.id.value().c_str(), "test2");
  EXPECT_STREQ(dlg.title.value().c_str(), "test2");
  EXPECT_STREQ(dlg2.title.value().c_str(), "test2");

  data.id = dlg.title;
  dlg.title = "title changed";
  EXPECT_STREQ(data.id.value().c_str(), "title changed");
  EXPECT_STREQ(data2.id.value().c_str(), "title changed");
  EXPECT_STREQ(dlg.title.value().c_str(), "title changed");
  EXPECT_STREQ(dlg2.title.value().c_str(), "title changed");

  data2.id = "data2 id";
  EXPECT_STREQ(data.id.value().c_str(), "data2 id");
  EXPECT_STREQ(data2.id.value().c_str(), "data2 id");
  EXPECT_STREQ(dlg.title.value().c_str(), "data2 id");
  EXPECT_STREQ(dlg2.title.value().c_str(), "data2 id");

  data.name = "ahn";
  dlg.contents = "name : " + data.name + "\nphone : " + data.phone;
  data.name = "haaha";
  data.phone = "010-6649-8813";
  dlg2.title = data.name;
  data.name = "xxx";
  data.name = data2.name;
  data2.name = "yyyy";

  data.count = 10;
  data2.count = 0;
  dlg.total = data.count + data2.count;

  data2.count = 20;
  data.count = 40;
}