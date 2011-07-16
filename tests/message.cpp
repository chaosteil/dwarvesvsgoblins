#include <UnitTest++.h>

#include "utils/message.h"

using namespace ::dvg::utils;

SUITE (Message) {
  TEST (Header) {
    Message m(0);
    Message n(1001);

    CHECK_EQUAL(0, (int)m.GetHeader());
    CHECK_EQUAL(1001, (int)n.GetHeader());
  }

  TEST (Basic_types) {
    Message m(0);

    m.Write<char>('a');
    CHECK_EQUAL('a', m.Read<char>());

    m.Write<uint32_t>(1002);
    CHECK_EQUAL((uint32_t)1002, m.Read<uint32_t>());

    m.Write<double>(1.234);
    CHECK_EQUAL(1.234, m.Read<double>());

    m.Write<int32_t>(-12);
    m.Write<float>(1.1f);
    CHECK_EQUAL(-12, m.Read<int32_t>());
    CHECK_EQUAL(1.1f, m.Read<float>());
  }

  TEST (Strings) {
    Message m(0);

    m.Write<std::string>(std::string("abc"));
    CHECK_EQUAL(std::string("abc"), m.Read<std::string>());

    m.Write<std::string>(std::string("a\0\0b", 4));
    CHECK_EQUAL(std::string("a\0\0b", 4), m.Read<std::string>());
  }

  TEST (Header_reading) {
    Message m(0);

    m.Write<char>('a');
    m.Write<char>('b');

    m.Read<char>();

    m.GetHeader();
    CHECK_EQUAL('a', m.Read<char>());
  }
}
