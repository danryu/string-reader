#pragma once
#include "macros/unwrap.hpp"

struct StringReader {
    std::string_view str;
    size_t           cursor = 0;

    template <class T, class... Args>
    static auto contains(const T value, const Args... args) -> bool {
        return ((value == args) || ...);
    }

    auto peek() const -> std::optional<char> {
        ensure(cursor < str.size());
        return str[cursor];
    }

    auto read() -> std::optional<char> {
        unwrap(c, peek());
        cursor += 1;
        return c;
    }

    auto peek(const size_t len) -> std::optional<std::string_view> {
        ensure(cursor + len <= str.size());
        return str.substr(cursor, len);
    }

    auto read(const size_t len) -> std::optional<std::string_view> {
        unwrap(s, peek(len));
        cursor += len;
        return s;
    }

    auto is_eof() const -> bool {
        return cursor >= str.size();
    }

    template <class... Args>
        requires((std::is_same_v<Args, char>) && ...)
    auto skip_while(const Args... args) -> bool {
    loop:
        unwrap(c, read());
        if(!contains(c, args...)) {
            cursor -= 1;
            return true;
        }
        goto loop;
    }

    template <class... Args>
        requires((std::is_same_v<Args, char>) && ...)
    auto read_until(const Args... args) -> std::optional<std::string_view> {
        auto begin = cursor;
    loop:
        unwrap(c, read());
        if(contains(c, args...)) {
            cursor -= 1;
            return str.substr(begin, cursor - begin);
        }
        goto loop;
    }

    auto read_until(const std::string_view arg) -> std::optional<std::string_view> {
        const auto i = str.find(arg, cursor);
        ensure(i != str.npos);
        const auto ret = str.substr(cursor, i - cursor);
        cursor         = i;
        return ret;
    }
};
