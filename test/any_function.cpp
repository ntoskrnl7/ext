#include <ext/any_function>
#include <gtest/gtest.h>

#include <ext/collection>

#ifdef _EXT_ANY_FUNCTION_
TEST(any_function_test, call_operator_test) {
  ext::any_function fn_strlen(strlen);
  ext::any_function fn_lambda(
      [](int v, const std::string &s) { return s + std::to_string(v); });

  std::any result;
  EXPECT_NO_THROW(result = fn_strlen({"test"}));
  EXPECT_NO_THROW(EXPECT_EQ(std::any_cast<size_t>(result), strlen("test")));

  EXPECT_NO_THROW(result = fn_lambda({1, "test"}));
  EXPECT_NO_THROW(
      EXPECT_STREQ(std::any_cast<std::string>(result).c_str(), "test1"));

  std::vector<std::any> args = {"test"};
  EXPECT_NO_THROW(result = fn_strlen(args));
  EXPECT_NO_THROW(EXPECT_EQ(std::any_cast<size_t>(result), strlen("test")));

  args = {1, "test"};
  EXPECT_NO_THROW(result = fn_lambda(args));
  EXPECT_NO_THROW(
      EXPECT_STREQ(std::any_cast<std::string>(result).c_str(), "test1"));

  args = {"test"};
  fn_strlen.set_args(args);
  EXPECT_NO_THROW(result = fn_strlen());
  EXPECT_NO_THROW(EXPECT_EQ(std::any_cast<size_t>(result), strlen("test")));

  args = {1, "test"};
  fn_lambda.set_args(args);
  EXPECT_NO_THROW(result = fn_lambda());
  EXPECT_NO_THROW(
      EXPECT_STREQ(std::any_cast<std::string>(result).c_str(), "test1"));

  fn_strlen.clear();
  fn_strlen.push_back("test");
  EXPECT_NO_THROW(result = fn_strlen());
  EXPECT_NO_THROW(EXPECT_EQ(std::any_cast<size_t>(result), strlen("test")));

  fn_lambda.clear();
  fn_lambda.push_back(1);
  fn_lambda.push_back("test");
  EXPECT_NO_THROW(result = fn_lambda());
  EXPECT_NO_THROW(
      EXPECT_STREQ(std::any_cast<std::string>(result).c_str(), "test1"));
}

TEST(any_function_test, call_method_test) {
  ext::any_function fn_strlen(strlen);
  auto size = fn_strlen.call("test");
  EXPECT_EQ(size, strlen("test"));

  ext::any_function fn_lambda([](int v) { return std::to_string(v); });
  EXPECT_STREQ(fn_lambda.call(1).c_str(), "1");
}

TEST(any_function_test, invalid_argument_test) {
  ext::any_function cmd([]() {});
  ext::any_function cmd2(strlen);
  ext::any_function cmd3([](const std::string &str) -> std::string {
    return str + std::to_string(str.size());
  });

  EXPECT_THROW(cmd({1}), ext::argument_count_mismatch);
  EXPECT_THROW(cmd2({"abc", "def"}), ext::argument_count_mismatch);
  EXPECT_THROW(cmd3({"abc", "def"}), ext::argument_count_mismatch);

  EXPECT_THROW(cmd2({1234}), ext::invalid_argument_type);
  EXPECT_THROW(cmd3({1234}), ext::invalid_argument_type);
}

class commands {
  friend class command_item;

public:
  static auto &get(const std::string &name) { return items_.at(name); }

private:
  static std::map<std::string, ext::any_function_base &> items_;
};
std::map<std::string, ext::any_function_base &> commands::items_;

class command_desc {
public:
  command_desc(const std::string &name) : name_(name) {}
  const std::string name() const { return name_; }

private:
  std::string name_;
};

class command_item : commands {
public:
  command_item(const command_desc &desc, ext::any_function_base &f) {
    name_ = desc.name();
    items_.insert({desc.name(), f});
  }
  ~command_item() { items_.erase(name_); }

private:
  std::string name_;
};

template <typename T>
class command : public command_item, public ext::any_function<T> {
  using type = ext::any_function<T>;

public:
  command(const command_desc &desc, T f)
      : command_item(desc, *static_cast<ext::any_function_base *>(this)),
        ext::any_function<T>(f) {}
};

template <typename R, typename... Args>
command(const command_desc &, R (*)(Args...)) -> command<R(Args...)>;

template <typename T>
command(const command_desc &, T)
    -> command<typename ext::deduce_mem_fn<T>::type>;

#include <queue>
using command_queue_item = std::pair<std::string, std::vector<std::any>>;
using command_queue = std::queue<command_queue_item>;

TEST(any_function_test, command_queue_test) {
  command cmd_run(command_desc("run"), [](int v) -> std::string {
    return "run : " + std::to_string(v);
  });

  command cmd_stop(command_desc("stop"), [](int v) -> std::string {
    return "stop : " + std::to_string(v);
  });

  command_queue command_queue;
  command_queue.emplace(command_queue_item("run", {1}));
  command_queue.emplace(command_queue_item("stop", {2}));
  command_queue.emplace(command_queue_item("run", {3}));

  command_queue.emplace(command_queue_item("run", {1, 2}));
  command_queue.emplace(command_queue_item("stop", {"2"}));

  while (!command_queue.empty()) {
    auto &item = command_queue.front();

    try {
      auto &cmd = commands::get(item.first);
      auto r = cmd(item.second);
      if (r.has_value()) {
        if (item.first == "run")
          EXPECT_NO_THROW(auto ret =
                              std::any_cast<decltype(cmd_run)::result_type>(r));
        else if (item.first == "stop")
          EXPECT_NO_THROW(
              auto ret = std::any_cast<decltype(cmd_stop)::result_type>(r));
      }
    } catch (const ext::invalid_argument_type &e) {
      std::cerr << "index : " << e.index() << "\n";
      std::cerr << "type name : " << e.type_name() << "\n";
      std::cerr << "what : " << e.what() << "\n";
    } catch (const ext::argument_count_mismatch &e) {
      std::cerr << "count : " << e.count() << "\n";
      std::cerr << "what : " << e.what() << "\n";
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
    command_queue.pop();
  }
}

class command_ref : public ext::any_function_base {
public:
  command_ref(ext::any_function_base &ref) { ptr_ = &ref; }
  void push_back(std::any value) { return ptr_->push_back(value); }
  void clear() { ptr_->clear(); }
  void set_args(const std::vector<std::any> &args) { ptr_->set_args(args); }
  std::any operator()() const { return ptr_->operator()(); }
  std::any operator()(const std::vector<std::any> args) const {
    return ptr_->operator()(args);
  }

private:
  ext::any_function_base *ptr_;
};

TEST(any_function_test, command_ref_test) {
  command cmd_run(command_desc("run"), [](int v) -> std::string {
    return "run : " + std::to_string(v);
  });

  command cmd_stop(command_desc("stop"), [](int v) -> std::string {
    return "stop : " + std::to_string(v);
  });

  try {
    command_ref current_cmd = cmd_run;
    current_cmd.push_back(100);
    auto r = current_cmd();
    auto b = std::any_cast<std::string>(r);

    current_cmd = cmd_stop;
    current_cmd.push_back(100);
    r = current_cmd();
    b = std::any_cast<std::string>(r);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}
#endif // _EXT_ANY_FUNCTION_