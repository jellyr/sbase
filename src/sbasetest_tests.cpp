#include <sbasetest/tests.hpp>

#include <scpp/tests.hpp>
#include <sboost/tests.hpp>
#include <sfp/tests.hpp>
#include <sfrp/tests.hpp>
#include <smisc/tests.hpp>
#include <stest/tests.hpp>

namespace sbasetest {
void tests(stest::TestCollector& col) {
  scpp::tests(col);
  sboost::tests(col);
  sfp::tests(col);
  sfrp::tests(col);
  smisc::tests(col);
  stest::tests(col);
}
}
