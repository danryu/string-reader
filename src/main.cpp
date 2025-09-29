#include "string-reader.hpp"

auto main() -> int {
    auto r = StringReader{"hello"};
    ensure(r.peek() == 'h');
    ensure(r.read() == 'h');
    ensure(r.read() == 'e');
    ensure(!r.is_eof());
    ensure(r.read_until('o') == "ll");
    ensure(r.read() == 'o');
    ensure(r.is_eof());

    r = StringReader{"=-=-=hello=-=-="};
    ensure(r.skip_while('=', '-'));
    ensure(r.read_until('=') == "hello");

    r = StringReader{"abcd/*hello*/efgh"};
    ensure(r.read_until("/*") == "abcd");
    ensure(r.read(2) == "/*");
    ensure(r.read_until("*/") == "hello");

    std::println("pass");
    return 0;
}
