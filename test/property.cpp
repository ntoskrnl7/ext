#include <ext/property>
#include <gtest/gtest.h>

#ifdef _EXT_PROPERTY_
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
  ext::property<size_t> total;
};

class user {
public:
  user() {}
  user(const std::string &id, const std::string &name, const std::string &phone,
       size_t count)
      : id(id), name(name), phone(phone), count(count) {}
  ext::property<std::string> id;
  ext::property<std::string> name;
  ext::property<std::string> phone;
  ext::property<size_t> count;
};

namespace ext {
template <typename T> using reaction = property<T>;
} // namespace ext

template <typename U, typename T>
U reduce(T &array, std::function<U(U &, typename T::value_type &)> callback,
         U init_value = {}) {
  for (typename T::value_type &item : array)
    init_value = callback(init_value, item);
  return init_value;
};

TEST(property_test, basic_test) {
  dialog dlg("dialog 1");
  dialog dlg2("dialog 2");
  user data;
  user data2;

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
  dlg.title = "test3";
  EXPECT_STREQ(data.id.value().c_str(), "test3");
  EXPECT_STREQ(data2.id.value().c_str(), "test3");
  EXPECT_STREQ(dlg.title.value().c_str(), "test3");
  EXPECT_STREQ(dlg2.title.value().c_str(), "test3");

  data2.id = "data2 id";
  EXPECT_STREQ(data.id.value().c_str(), "data2 id");
  EXPECT_STREQ(data2.id.value().c_str(), "data2 id");
  EXPECT_STREQ(dlg.title.value().c_str(), "data2 id");
  EXPECT_STREQ(dlg2.title.value().c_str(), "data2 id");

  data.name = "Jung-kwnag Lee";
#if defined(_MSC_VER)
  dlg.contents = "name : " + data.name + "\tphone : " + data.phone;
#else
  dlg.contents = decltype(dlg.contents)::chain("name : ", data.name) +
                 "\tphone : " + data.phone;
#endif
  EXPECT_STREQ(dlg.contents.value().c_str(), "name : Jung-kwnag Lee\tphone : ");

  data.phone = "010-1234-5678";
  EXPECT_STREQ(dlg.contents.value().c_str(),
               "name : Jung-kwnag Lee\tphone : 010-1234-5678");

  data.count = 10;
  data2.count = 0;
  dlg.total = data.count + data2.count;
  EXPECT_EQ(dlg.total.value(), 10);

  data2.count = 20;
  data.count = 40;
  EXPECT_EQ(dlg.total.value(), 60);

  std::vector<user> users;
  users.emplace_back("test", "alice", "1234", 0);
  users.emplace_back("test1", "bob", "5678", 0);

  dlg.total = reduce<decltype(user::count)::chain>(
      users, [](auto &pre, auto &user) { return pre + user.count; });

  users[0].count = 10;
  EXPECT_EQ(dlg.total.value(), 10);

  users[1].count = 20;
  EXPECT_EQ(dlg.total.value(), 30);
}
#endif // _EXT_PROPERTY_