#pragma once

#if defined(_MSC_VER)
#define BOOST_UT_DISABLE_MODULE
#pragma warning(push)
#pragma warning(disable : 4459)
#endif

#include <boost/ut.hpp>

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

using namespace boost::ut;
