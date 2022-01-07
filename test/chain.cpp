#include <string>
#include <tuple>

#include <ext/chain>

#define GTEST_HAS_TR1_TUPLE 0
#include <gtest/gtest.h>

#include <map>

namespace http {
struct request {
  enum method { http_get, http_post, http_delete, http_put, http_invalid };
  request() : method(http_invalid) {}
  request(const std::string &path, method method,
          const std::map<std::string, std::string> headers =
              std::map<std::string, std::string>())
      : path(path), method(method), headers(headers) {}
  method method;
  std::string path;
  std::map<std::string, std::string> headers;

  std::string get_method() const {
    switch (method) {
    case http_get:
      return "GET";
    case http_post:
      return "POST";
    case http_delete:
      return "DELETE";
    case http_put:
      return "PUT";
    default:
      throw std::runtime_error("Invalid method");
    }
  }

  void validate() const {
    if (path.empty())
      throw std::runtime_error("path is empty");
    if (path[0] != '/')
      throw std::runtime_error("Invalid path : " + path);
  }
};

struct response {
  enum status {
    ok = 200,
    unauthorized = 401,
    forbidden = 403,
    not_found = 404,
    internal_server_error = 500
  };
  response() : status(internal_server_error) {}
  response(status s, const std::string &body = std::string())
      : status(s), body(body) {}
  status status;
  std::string body;
};

template <class T> struct validation_chain : T {
  typename T::result execute(const request &req) {
    try {
      req.validate();
      return T::execute(req);
    } catch (const std::exception &e) {
      return T::done(response(response::internal_server_error, e.what()));
    }
  }
};
struct basic_chain : ext::chain<basic_chain, response, const request &> {};
} // namespace http

TEST(chain_test, basic) {
  struct auth_check_chain_type : public http::basic_chain {
    result execute(const http::request &req) {
      std::map<std::string, std::string>::const_iterator it =
          req.headers.find("auth");
      if (it != req.headers.end() && it->second == "authorized")
        return chain::next(req);
      return chain::done(http::response(http::response::unauthorized));
    }
  };
  http::validation_chain<auth_check_chain_type> auth_check_chain;

  struct get_info_chain_type : public http::basic_chain {
    result execute(const http::request &req) {
      if ((req.path == "/info") && (req.method == http::request::http_get)) {
        std::map<std::string, std::string>::const_iterator it =
            req.headers.find("perm");
        if ((it != req.headers.end()) && it->second == "read")
          return chain::done(http::response(
              http::response::ok, "[" + req.get_method() + "] " + req.path));
        return chain::done(http::response(http::response::forbidden,
                                          "Read permission required"));
      }
      return chain::next(req);
    }
  };
  http::validation_chain<get_info_chain_type> get_info_chain;

  struct not_found_chain_type : public http::basic_chain {
    result execute(const http::request &req) {
      return chain::done(http::response(
          http::response::not_found, "[" + req.get_method() + "] " + req.path));
    }
  };
  http::validation_chain<not_found_chain_type> not_found_chain;

  // Build a chain.
  auth_check_chain >> get_info_chain >> not_found_chain;

  // Execute the first chain (auth_check_chain).
  http::response res =
      auth_check_chain(http::request("/info", http::request::http_get)).get();
  EXPECT_EQ(res.status, http::response::unauthorized);

  std::map<std::string, std::string> headers;
  headers.insert(std::pair<std::string, std::string>("auth", "authorized"));

  res =
      auth_check_chain(http::request("/info", http::request::http_get, headers))
          .get();
  EXPECT_EQ(res.status, http::response::forbidden);
  EXPECT_STREQ(res.body.c_str(), "Read permission required");

  headers.insert(std::pair<std::string, std::string>("perm", "read"));
  res =
      auth_check_chain(http::request("/info", http::request::http_get, headers))
          .get();
  EXPECT_EQ(res.status, http::response::ok);
  EXPECT_STREQ(res.body.c_str(), "[GET] /info");

  res =
      auth_check_chain(http::request("/test", http::request::http_get, headers))
          .get();
  EXPECT_EQ(res.status, http::response::not_found);

  res = auth_check_chain(
            http::request("/info", http::request::http_post, headers))
            .get();
  EXPECT_EQ(res.status, http::response::not_found);

  res =
      auth_check_chain(http::request("info", http::request::http_post, headers))
          .get();
  EXPECT_EQ(res.status, http::response::internal_server_error);
  EXPECT_STREQ(res.body.c_str(), "Invalid path : info");

  res = auth_check_chain(
            http::request("/info", (enum http::request::method)100, headers))
            .get();
  EXPECT_EQ(res.status, http::response::internal_server_error);
  EXPECT_STREQ(res.body.c_str(), "Invalid method");

  // Execute the second chain (get_info_chain).
  headers.erase("auth");
  res = get_info_chain(http::request("/info", http::request::http_get, headers))
            .get();
  EXPECT_EQ(res.status, http::response::ok);
  EXPECT_STREQ(res.body.c_str(), "[GET] /info");

  res = get_info_chain(http::request("/info", http::request::http_post)).get();
  EXPECT_EQ(res.status, http::response::not_found);

  res = get_info_chain(http::request("", http::request::http_get)).get();
  EXPECT_EQ(res.status, http::response::internal_server_error);
  EXPECT_STREQ(res.body.c_str(), "path is empty");
}

class object_with_name {
public:
  object_with_name(const std::string &name) : name_(name) {}
  const std::string &name() const { return name_; }

private:
  std::string name_;
};

#ifdef __cpp_variadic_templates
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

  EXPECT_THROW(long result = current_chain(3, "test"),
               test_chain::end_of_chain);

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
  EXPECT_NO_THROW(long result = (chain1.start(0, "test") | chain2 | chain3 |
                                 chain4 | chain5 | chain6));
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
#else
class test_chain : public object_with_name,
                   public ext::chain<test_chain, long, const std::string &> {
public:
  test_chain(const std::string &name) : object_with_name(name), chain() {}
};

class test_chain_impl0 : public test_chain {
  using test_chain::test_chain;

private:
  result execute(const std::string &s) {
    std::cout << "test_chain_impl0 - " << name() << " : " << s << std::endl;
    if (s.empty())
      throw std::runtime_error("String argument is empty :-(");
    if (s.size() == 1) {
      std::cout << "done : " << name() << std::endl;
      return chain::done(1);
    }
    return chain::next(s);
  }
};

class test_chain_impl1 : public test_chain {
  using test_chain::test_chain;

private:
  result execute(const std::string &s) {
    std::cout << "test_chain_impl1 - " << name() << " : " << s << std::endl;
    if (s.empty())
      throw std::runtime_error("String argument is empty :-(");
    if (s.size() == 2) {
      std::cout << "done : " << name() << std::endl;
      return chain::done(2);
    }
    return chain::next(s);
  }
};

class test_chain_impl2 : public test_chain {
  using test_chain::test_chain;

private:
  result execute(int i, const std::string &s) {
    std::cout << "test_chain_impl2 - " << name() << " : " << s << std::endl;
    if (s.empty())
      throw std::runtime_error("String argument is empty :-(");
    if (s.size() == 3) {
      std::cout << "done : " << name() << std::endl;
      return chain::done(3);
    }
    return chain::next(s);
  }
};
#endif // __cpp_variadic_templates