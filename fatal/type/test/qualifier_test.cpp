/*
 *  Copyright (c) 2016, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 */

#include <fatal/type/qualifier.h>

#include <fatal/test/driver.h>

namespace fatal {

struct foo {
  void noncv();
  void c() const;
  void v() volatile;
  void cv() const volatile;
  void vc() volatile const;
};

FATAL_TEST(qualifier, cv_qualifier_bitwise_and) {
  FATAL_EXPECT_FALSE(cv_qualifier::none & cv_qualifier::none);
  FATAL_EXPECT_FALSE(cv_qualifier::none & cv_qualifier::c);
  FATAL_EXPECT_FALSE(cv_qualifier::none & cv_qualifier::v);
  FATAL_EXPECT_FALSE(cv_qualifier::none & cv_qualifier::cv);

  FATAL_EXPECT_FALSE(cv_qualifier::c & cv_qualifier::none);
  FATAL_EXPECT_TRUE(cv_qualifier::c & cv_qualifier::c);
  FATAL_EXPECT_FALSE(cv_qualifier::c & cv_qualifier::v);
  FATAL_EXPECT_TRUE(cv_qualifier::c & cv_qualifier::cv);

  FATAL_EXPECT_FALSE(cv_qualifier::v & cv_qualifier::none);
  FATAL_EXPECT_FALSE(cv_qualifier::v & cv_qualifier::c);
  FATAL_EXPECT_TRUE(cv_qualifier::v & cv_qualifier::v);
  FATAL_EXPECT_TRUE(cv_qualifier::v & cv_qualifier::cv);

  FATAL_EXPECT_FALSE(cv_qualifier::cv & cv_qualifier::none);
  FATAL_EXPECT_TRUE(cv_qualifier::cv & cv_qualifier::c);
  FATAL_EXPECT_TRUE(cv_qualifier::cv & cv_qualifier::v);
  FATAL_EXPECT_TRUE(cv_qualifier::cv & cv_qualifier::cv);
}

FATAL_TEST(qualifier, add_const_from) {
# define TEST_IMPL(From, T, ...) \
  FATAL_EXPECT_SAME<__VA_ARGS__, add_const_from<T, From>::type>();

  TEST_IMPL(int, int &&, int &&);
  TEST_IMPL(int, int &, int &);
  TEST_IMPL(int, int *&&, int *&&);
  TEST_IMPL(int, int *&, int *&);
  TEST_IMPL(int, int *, int *);
  TEST_IMPL(int, int, int);
  TEST_IMPL(int, int *const &&, int *const &&);
  TEST_IMPL(int, int *const &, int *const &);
  TEST_IMPL(int, int *const, int *const);
  TEST_IMPL(int, int const &&, int const &&);
  TEST_IMPL(int, int const &, int const &);
  TEST_IMPL(int, int const *&&, int const *&&);
  TEST_IMPL(int, int const *&, int const *&);
  TEST_IMPL(int, int const *, int const *);
  TEST_IMPL(int, int const *const &&, int const *const &&);
  TEST_IMPL(int, int const *const &, int const *const &);
  TEST_IMPL(int, int const *const, int const *const);
  TEST_IMPL(int, int const, int const);

  TEST_IMPL(int const, int &&, int &&);
  TEST_IMPL(int const, int &, int &);
  TEST_IMPL(int const, int, int const);
  TEST_IMPL(int const, int *&&, int *&&);
  TEST_IMPL(int const, int *&, int *&);
  TEST_IMPL(int const, int *, int *const);
  TEST_IMPL(int const, int *const &&, int *const &&);
  TEST_IMPL(int const, int *const &, int *const &);
  TEST_IMPL(int const, int *const, int *const);
  TEST_IMPL(int const, int const &&, int const &&);
  TEST_IMPL(int const, int const &, int const &);
  TEST_IMPL(int const, int const, int const);
  TEST_IMPL(int const, int const *&&, int const *&&);
  TEST_IMPL(int const, int const *&, int const *&);
  TEST_IMPL(int const, int const *, int const *const);
  TEST_IMPL(int const, int const *const &&, int const *const &&);
  TEST_IMPL(int const, int const *const &, int const *const &);
  TEST_IMPL(int const, int const *const, int const *const);

# undef TEST_IMPL
}

FATAL_TEST(qualifier, add_reference_from) {
# define TEST_IMPL(From, T, ...) \
  FATAL_EXPECT_SAME<__VA_ARGS__, add_reference_from<T, From>::type>();

  TEST_IMPL(int &&, int &&, int &&);
  TEST_IMPL(int &&, int &, int &);
  TEST_IMPL(int &&, int, int &&);
  TEST_IMPL(int &&, int *&&, int *&&);
  TEST_IMPL(int &&, int *&, int *&);
  TEST_IMPL(int &&, int *, int * &&);
  TEST_IMPL(int &&, int *const &&, int *const &&);
  TEST_IMPL(int &&, int *const &, int *const &);
  TEST_IMPL(int &&, int *const, int *const &&);
  TEST_IMPL(int &&, int const &&, int const &&);
  TEST_IMPL(int &&, int const &, int const &);
  TEST_IMPL(int &&, int const, int const &&);
  TEST_IMPL(int &&, int const *&&, int const *&&);
  TEST_IMPL(int &&, int const *&, int const *&);
  TEST_IMPL(int &&, int const *, int const * &&);
  TEST_IMPL(int &&, int const *const &&, int const *const &&);
  TEST_IMPL(int &&, int const *const &, int const *const &);
  TEST_IMPL(int &&, int const *const, int const *const &&);

  TEST_IMPL(int &, int &&, int &);
  TEST_IMPL(int &, int &, int &);
  TEST_IMPL(int &, int, int &);
  TEST_IMPL(int &, int *&&, int *&);
  TEST_IMPL(int &, int *&, int *&);
  TEST_IMPL(int &, int *, int *&);
  TEST_IMPL(int &, int *const &&, int *const &);
  TEST_IMPL(int &, int *const &, int *const &);
  TEST_IMPL(int &, int *const, int *const &);
  TEST_IMPL(int &, int const &&, int const &);
  TEST_IMPL(int &, int const &, int const &);
  TEST_IMPL(int &, int const, int const &);
  TEST_IMPL(int &, int const *&&, int const *&);
  TEST_IMPL(int &, int const *&, int const *&);
  TEST_IMPL(int &, int const *, int const *&);
  TEST_IMPL(int &, int const *const &&, int const *const &);
  TEST_IMPL(int &, int const *const &, int const *const &);
  TEST_IMPL(int &, int const *const, int const *const &);

  TEST_IMPL(int, int &&, int &&);
  TEST_IMPL(int, int &, int &);
  TEST_IMPL(int, int, int);
  TEST_IMPL(int, int *&&, int *&&);
  TEST_IMPL(int, int *&, int *&);
  TEST_IMPL(int, int *, int *);
  TEST_IMPL(int, int *const &&, int *const &&);
  TEST_IMPL(int, int *const &, int *const &);
  TEST_IMPL(int, int *const, int *const);
  TEST_IMPL(int, int const &&, int const &&);
  TEST_IMPL(int, int const &, int const &);
  TEST_IMPL(int, int const, int const);
  TEST_IMPL(int, int const *&&, int const *&&);
  TEST_IMPL(int, int const *&, int const *&);
  TEST_IMPL(int, int const *, int const *);
  TEST_IMPL(int, int const *const &&, int const *const &&);
  TEST_IMPL(int, int const *const &, int const *const &);
  TEST_IMPL(int, int const *const, int const *const);

# undef TEST_IMPL
}

} // namespace fatal {
