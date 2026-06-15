# chain

[Back to API reference](README.md)

## Header

`#include <ext/chain>`

## Requirements

- GCC 8.3.0+
- Clang 10.0+
- Visual Studio 2008 SP1+

## Examples

- Implements an http request chain.

    ```C++
    #include <map>
    #include <string>
    #include <string>
    #include <tuple>

    #include <ext/chain>

    namespace http {
        struct request {
            enum method { http_get, http_post, http_delete, http_put, http_invalid };
            request() : method(method::http_invalid) {}
            request(const std::string &path, method method,
                    const std::map<std::string, std::string> headers = {})
                : path(path), method(method), headers(headers) {}
            method method;
            std::string path;
            std::map<std::string, std::string> headers;
            std::string get_method() const {
                switch (method) {
                case method::http_get:
                    return "GET";
                case method::http_post:
                    return "POST";
                case method::http_delete:
                    return "DELETE";
                case method::http_put:
                    return "PUT";
                default:
                    throw std::runtime_error("Invalid method");
                }
            }
            void validate() const {
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
            response(status s, const std::string &body = {}) : status(s), body(body) {}
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

    struct auth_check_chain_type : public http::basic_chain {
        result execute(const http::request &req) {
        auto it = req.headers.find("auth");
        if (it != req.headers.cend() && it->second == "authorized")
            return chain::next(req);
        return chain::done(http::response(http::response::unauthorized));
        }
    };
    http::validation_chain<auth_check_chain_type> auth_check_chain;

    struct get_info_chain_type : public http::basic_chain {
        result execute(const http::request &req) {
        if ((req.path == "/info") && (req.method == http::request::http_get))
            return chain::done(http::response(
                http::response::ok, "[" + req.get_method() + "] " + req.path));
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
    auto res = auth_check_chain(http::request("/info", http::request::http_get)).get();
    // res.status == http::response::unauthorized

    res = auth_check_chain(http::request("/info", http::request::http_post, {{"auth", "authorized"}})).get();
    // res.status == http::response::not_found

    res = auth_check_chain(http::request("/test", http::request::http_get, {{"auth", "authorized"}})).get();
    // res.status == http::response::not_found

    res = auth_check_chain(http::request("1234", http::request::http_post, {{"auth", "authorized"}})).get();
    // res.status == http::response::internal_server_error
    // res.body == "Invalid path : 1234"

    res = auth_check_chain(http::request("/info", http::request::http_get, {{"auth", "authorized"}})).get();
    // res.status == http::response::ok
    // res.body == "[GET] /info"

    // Execute the second chain (get_info_chain).
    res = get_info_chain(http::request("/info", http::request::http_get)).get();
    // res.status == http::response::ok
    // res.body == "[GET] /info"
    ```
