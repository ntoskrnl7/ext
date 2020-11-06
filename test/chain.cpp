#include <gtest/gtest.h>

#include <ext/chain>
#include <string>

class object_with_name {
public:
  object_with_name(const std::string &name) : name_(name) {}
  const std::string &name() const { return name_; }

private:
  std::string name_;
};

class test_chain
    : public object_with_name,
      public ext::chain<test_chain, long, int, const std::string &> {
public:
  test_chain(const std::string &name) : object_with_name(name), chain() {}
};

class test_chain_impl0 : public test_chain {
  using test_chain::test_chain;

private:
  result execute(int i, const std::string &s) {
    std::cout << "test_chain_impl0 - " << name() << " : " << i << "," << s
              << std::endl;
    if (s.empty())
      throw std::runtime_error("String argument is empty :-(");
    if (i == 0) {
      std::cout << "done : " << name() << std::endl;
      return chain::done(1);
    }
    return chain::next(i, s);
  }
};

class test_chain_impl1 : public test_chain {
  using test_chain::test_chain;

private:
  result execute(int i, const std::string &s) {
    std::cout << "test_chain_impl1 - " << name() << " : " << i << "," << s
              << std::endl;
    if (s.empty())
      throw std::runtime_error("String argument is empty :-(");
    if (i == 1) {
      std::cout << "done : " << name() << std::endl;
      return chain::done(2);
    }
    return chain::next(i, s);
  }
};

class test_chain_impl2 : public test_chain {
  using test_chain::test_chain;

private:
  result execute(int i, const std::string &s) {
    std::cout << "test_chain_impl2 - " << name() << " : " << i << "," << s
              << std::endl;
    if (s.empty())
      throw std::runtime_error("String argument is empty :-(");
    if (i == 2) {
      std::cout << "done : " << name() << std::endl;
      return chain::done(3);
    }
    return chain::next(i, s);
  }
};

TEST(chain_test, prepare_next_test) {
  test_chain_impl0 chain1("chain 1");
  test_chain_impl1 chain2("chain 2");
  test_chain_impl2 chain3("chain 3");
  test_chain_impl0 chain4("chain 4");
  test_chain_impl1 chain5("chain 5");
  test_chain_impl2 chain6("chain 6");

  test_chain &current_chain = chain1;

  chain1 >> chain2 >> chain3 >> chain4 >> chain5 >> chain6;
  // chain1.next(chain2).next(chain3).next(chain4).next(chain5).next(chain6);

  //
  // Starting from current chain (chain 1)
  //
  EXPECT_EQ(current_chain(0, "").state(), test_chain::result::aborted);
  EXPECT_STREQ(((test_chain &)current_chain(0, "")).name().c_str(), "chain 1");

  EXPECT_EQ(current_chain(0, "test").state(), test_chain::result::done);
  EXPECT_STREQ(((test_chain &)current_chain(0, "test")).name().c_str(),
               "chain 1");
  EXPECT_EQ((long)current_chain(0, "test"), 1);

  EXPECT_EQ(current_chain(1, "test").state(), test_chain::result::done);
  EXPECT_STREQ(current_chain(1, "test").get_chain().name().c_str(), "chain 2");
  EXPECT_EQ((long)current_chain(1, "test"), 2);

  EXPECT_EQ(current_chain(2, "test").state(), test_chain::result::done);
  EXPECT_STREQ(current_chain(2, "test").get_chain().name().c_str(), "chain 3");
  EXPECT_EQ((long)current_chain(2, "test"), 3);

  EXPECT_EQ(current_chain(3, "test").state(), test_chain::result::end_of_chain);
  EXPECT_STREQ(current_chain(3, "test").get_chain().name().c_str(), "chain 6");

  //
  // Starting from chain 4
  //
  EXPECT_EQ(chain4(0, "").state(), test_chain::result::aborted);
  EXPECT_STREQ(chain4(0, "").get_chain().name().c_str(), "chain 4");

  EXPECT_EQ(chain4(0, "test").state(), test_chain::result::done);
  EXPECT_STREQ(chain4(0, "test").get_chain().name().c_str(), "chain 4");
  EXPECT_EQ((long)chain4(0, "test"), 1);

  EXPECT_EQ(chain4(1, "test").state(), test_chain::result::done);
  EXPECT_STREQ(chain4(1, "test").get_chain().name().c_str(), "chain 5");
  EXPECT_EQ((long)chain4(1, "test"), 2);

  EXPECT_EQ(chain4(2, "test").state(), test_chain::result::done);
  EXPECT_STREQ(chain4(2, "test").get_chain().name().c_str(), "chain 6");
  EXPECT_EQ((long)chain4(2, "test"), 3);

  EXPECT_EQ(chain4(3, "test").state(), test_chain::result::end_of_chain);
  EXPECT_STREQ(chain4(3, "test").get_chain().name().c_str(), "chain 6");

  //
  // Starting from chain 5
  //
  EXPECT_EQ(chain5(0, "").state(), test_chain::result::aborted);
  EXPECT_STREQ(chain5(0, "").get_chain().name().c_str(), "chain 5");

  EXPECT_EQ(chain5(0, "test").state(), test_chain::result::end_of_chain);
  EXPECT_STREQ(chain5(0, "test").get_chain().name().c_str(), "chain 6");

  EXPECT_EQ(chain5(1, "test").state(), test_chain::result::done);
  EXPECT_STREQ(chain5(1, "test").get_chain().name().c_str(), "chain 5");
  EXPECT_EQ((long)chain5(1, "test"), 2);

  EXPECT_EQ(chain5(2, "test").state(), test_chain::result::done);
  EXPECT_STREQ(chain5(2, "test").get_chain().name().c_str(), "chain 6");
  EXPECT_EQ((long)chain5(2, "test"), 3);

  EXPECT_EQ(chain5(3, "test").state(), test_chain::result::end_of_chain);
  EXPECT_STREQ(chain5(3, "test").get_chain().name().c_str(), "chain 6");

  //
  // Starting from chain 6
  //
  EXPECT_EQ(chain6(0, "").state(), test_chain::result::aborted);
  EXPECT_STREQ(chain6(0, "").get_chain().name().c_str(), "chain 6");

  EXPECT_EQ(chain6(0, "test").state(), test_chain::result::end_of_chain);
  EXPECT_STREQ(chain6(0, "test").get_chain().name().c_str(), "chain 6");

  EXPECT_EQ(chain6(1, "test").state(), test_chain::result::end_of_chain);
  EXPECT_STREQ(chain6(1, "test").get_chain().name().c_str(), "chain 6");

  EXPECT_EQ(chain6(2, "test").state(), test_chain::result::done);
  EXPECT_STREQ(chain6(2, "test").get_chain().name().c_str(), "chain 6");
  EXPECT_EQ((long)chain6(2, "test"), 3);

  EXPECT_EQ(chain6(3, "test").state(), test_chain::result::end_of_chain);
  EXPECT_STREQ(chain6(3, "test").get_chain().name().c_str(), "chain 6");
}

TEST(chain_test, prepare_next_test_with_throw) {
  test_chain_impl0 chain1("chain 1");
  test_chain_impl1 chain2("chain 2");
  test_chain_impl2 chain3("chain 3");
  test_chain_impl0 chain4("chain 4");
  test_chain_impl1 chain5("chain 5");
  test_chain_impl2 chain6("chain 6");

  test_chain &current_chain = chain1;

  chain1 >> chain2 >> chain3 >> chain4 >> chain5 >> chain6;
  // chain1.next(chain2).next(chain3).next(chain4).next(chain5).next(chain6);

  //
  // Starting from current chain (chain 1)
  //
  EXPECT_THROW(long result = current_chain(0, ""), test_chain::chain_aborted);
  ASSERT_NO_THROW(long result = current_chain(0, "test"));
  EXPECT_EQ((long)current_chain(0, "test"), 1);
#if CXX_VER >= 201703L
  {
    auto [result, chain] = current_chain(0, "test").tuple();
    EXPECT_EQ(result, 1);
    EXPECT_STREQ(dynamic_cast<test_chain &>(chain).name().c_str(), "chain 1");
  }
#endif

  ASSERT_NO_THROW(long result = current_chain(1, "test"));
  EXPECT_EQ((long)current_chain(1, "test"), 2);
#if CXX_VER >= 201703L
  {
    auto [result, chain] = current_chain(1, "test").tuple();
    EXPECT_EQ(result, 2);
    EXPECT_STREQ(dynamic_cast<test_chain &>(chain).name().c_str(), "chain 2");
  }
#endif

  ASSERT_NO_THROW(long result = current_chain(2, "test"));
  EXPECT_EQ((long)current_chain(2, "test"), 3);
#if CXX_VER >= 201703L
  {
    auto [result, chain] = current_chain(2, "test").tuple();
    EXPECT_EQ(result, 3);
    EXPECT_STREQ(dynamic_cast<test_chain &>(chain).name().c_str(), "chain 3");
  }
#endif

  EXPECT_THROW(long result = current_chain(3, "test"), test_chain::end_of_chain);

  //
  // Starting from chain 4
  //
  EXPECT_THROW(long result = chain4(0, ""), test_chain::chain_aborted);
  ASSERT_NO_THROW(long result = chain4(0, "test"));
  ASSERT_NO_THROW(long result = chain4(1, "test"));
  ASSERT_NO_THROW(long result = chain4(2, "test"));
  EXPECT_THROW(long result = chain4(3, "test"), test_chain::end_of_chain);

  //
  // Starting from chain 4
  //
  EXPECT_THROW(long result = chain4(0, ""), test_chain::chain_aborted);
  ASSERT_NO_THROW(long result = chain4(0, "test"));
  ASSERT_NO_THROW(long result = chain4(1, "test"));
  ASSERT_NO_THROW(long result = chain4(2, "test"));
  EXPECT_THROW(long result = chain4(3, "test"), test_chain::end_of_chain);

  //
  // Starting from chain 5
  //
  EXPECT_THROW(long result = chain5(0, ""), test_chain::chain_aborted);
  EXPECT_THROW(long result = chain5(0, "test"), test_chain::end_of_chain);
  ASSERT_NO_THROW(long result = chain5(1, "test"));
  ASSERT_NO_THROW(long result = chain5(2, "test"));
  EXPECT_THROW(long result = chain5(3, "test"), test_chain::end_of_chain);

  //
  // Starting from chain 6
  //
  EXPECT_THROW(long result = chain6(0, ""), test_chain::chain_aborted);
  EXPECT_THROW(long result = chain6(0, "test"), test_chain::end_of_chain);
  EXPECT_THROW(long result = chain6(1, "test"), test_chain::end_of_chain);
  ASSERT_NO_THROW(long result = chain6(2, "test"));
  EXPECT_THROW(long result = chain6(3, "test"), test_chain::end_of_chain);
}

TEST(chain_test, chain_pipe_with_tuple) {
  test_chain_impl0 chain1("chain 1");
  test_chain_impl1 chain2("chain 2");
  test_chain_impl2 chain3("chain 3");
  test_chain_impl0 chain4("chain 4");
  test_chain_impl1 chain5("chain 5");
  test_chain_impl2 chain6("chain 6");

  test_chain &current_chain = chain1;

  auto &last_chain = std::make_tuple(3, "test") >> chain1 | chain2 | chain3 |
                     chain4 | chain5 | chain6;
  EXPECT_STREQ(last_chain.name().c_str(), "chain 6");

  test_chain::result result = std::make_tuple(0, "test") | chain1 | chain2 |
                              chain3 | chain4 | chain5 | chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 1");
  EXPECT_EQ(result.state(), test_chain::result::done);
  EXPECT_EQ(result.get(), 1);

  result = std::make_tuple(1, "test") | chain1 | chain2 | chain3 | chain4 |
           chain5 | chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 2");
  EXPECT_EQ(result.state(), test_chain::result::done);
  EXPECT_EQ(result.get(), 2);

  result = std::make_tuple(2, "test") | chain1 | chain2 | chain3 | chain4 |
           chain5 | chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 3");
  EXPECT_EQ(result.state(), test_chain::result::done);
  EXPECT_EQ(result.get(), 3);

  result = std::make_tuple(3, "test") | chain1 | chain2 | chain3 | chain4 |
           chain5 | chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 6");
  EXPECT_EQ(result.state(), test_chain::result::end_of_chain);

  result = std::make_tuple(3, "") | chain1 | chain2 | chain3 | chain4 | chain5 |
           chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 1");
  EXPECT_EQ(result.state(), test_chain::result::aborted);
}

TEST(chain_test, chain_start_method_with_tuple) {
  test_chain_impl0 chain1("chain 1");
  test_chain_impl1 chain2("chain 2");
  test_chain_impl2 chain3("chain 3");
  test_chain_impl0 chain4("chain 4");
  test_chain_impl1 chain5("chain 5");
  test_chain_impl2 chain6("chain 6");

  test_chain &current_chain = chain1;

  auto &last_chain =
      chain1.start(3, "test") | chain2 | chain3 | chain4 | chain5 | chain6;
  EXPECT_STREQ(last_chain.name().c_str(), "chain 6");

  test_chain::result result =
      chain1.start(0, "test") | chain2 | chain3 | chain4 | chain5 | chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 1");
  EXPECT_EQ(result.state(), test_chain::result::done);
  EXPECT_EQ(result.get(), 1);

  result = chain1.start(1, "test") | chain2 | chain3 | chain4 | chain5 | chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 2");
  EXPECT_EQ(result.state(), test_chain::result::done);
  EXPECT_EQ(result.get(), 2);

  result = chain1.start(2, "test") | chain2 | chain3 | chain4 | chain5 | chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 3");
  EXPECT_EQ(result.state(), test_chain::result::done);
  EXPECT_EQ(result.get(), 3);

  result = chain1.start(3, "test") | chain2 | chain3 | chain4 | chain5 | chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 6");
  EXPECT_EQ(result.state(), test_chain::result::end_of_chain);

  result = chain1.start(3, "") | chain2 | chain3 | chain4 | chain5 | chain6;
  EXPECT_STREQ(result.get_chain().name().c_str(), "chain 1");
  EXPECT_EQ(result.state(), test_chain::result::aborted);
}

TEST(chain_test, chain_result_test) {
  test_chain_impl0 chain1("chain 1");
  test_chain_impl1 chain2("chain 2");
  test_chain_impl2 chain3("chain 3");
  test_chain_impl0 chain4("chain 4");
  test_chain_impl1 chain5("chain 5");
  test_chain_impl2 chain6("chain 6");

  test_chain &current_chain = chain1;

  EXPECT_THROW(long result = current_chain, test_chain::invalid_chain);
  EXPECT_THROW(test_chain::result result = current_chain,
               test_chain::invalid_chain);
  EXPECT_NO_THROW(long result = (chain1.start(0, "test") | chain2 | chain3 | chain4 |
                         chain5 | chain6));
  EXPECT_NO_THROW(long result = current_chain);
  EXPECT_NO_THROW(test_chain::result result = current_chain);

  chain1 >> chain2 >> chain3 >> chain4 >> chain5 >> chain6;
  // chain1.next(chain2).next(chain3).next(chain4).next(chain5).next(chain6);

  EXPECT_THROW(long result = current_chain, std::invalid_argument);
  EXPECT_THROW(test_chain::result result = current_chain,
               std::invalid_argument);

  EXPECT_NO_THROW(long result = current_chain(0, "test"));
  EXPECT_NO_THROW(test_chain::result result = current_chain(0, "test"));
}

TEST(chain_test, chain_next_method_test) {
  test_chain_impl0 chain1("chain 1");
  test_chain_impl1 chain2("chain 2");
  test_chain_impl2 chain3("chain 3");
  test_chain_impl0 chain4("chain 4");
  test_chain_impl1 chain5("chain 5");
  test_chain_impl2 chain6("chain 6");

  chain1 >> chain1 >> chain1 >> chain2 >> chain2 >> chain2 >> chain3 >> chain1;
  // chain1.next(chain1).next(chain1).next(chain2).next(chain2).next(chain2).next(chain3).next(chain1);
  EXPECT_STREQ(chain1.next().name().c_str(), "chain 2");
  EXPECT_STREQ(chain2.next().name().c_str(), "chain 3");
  EXPECT_STREQ(chain3.next().name().c_str(), "chain 1");

  chain1 >> chain3;
  // chain1.next(chain3);
  EXPECT_STREQ(chain1.next().name().c_str(), "chain 3");
  EXPECT_STREQ(chain3.next().name().c_str(), "chain 1");

  chain1 >> chain6;
  // chain1.next(chain3);
  EXPECT_STREQ(chain1.next().name().c_str(), "chain 6");
  EXPECT_THROW(chain6.next(), test_chain::invalid_chain);
}