/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <librevenge/librevenge.h>

namespace librevenge
{

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &out, const RVNGString &str)
{
	return out << str.cstr();
}

}

namespace test
{

using namespace librevenge;

class RVNGPropertyListTest : public CPPUNIT_NS::TestFixture
{
public:
	virtual void setUp();
	virtual void tearDown();

private:
	CPPUNIT_TEST_SUITE(RVNGPropertyListTest);
	CPPUNIT_TEST(testInsertWithConversion);
	CPPUNIT_TEST_SUITE_END();

private:
	void testInsertWithConversion();
};

void RVNGPropertyListTest::setUp()
{
}

void RVNGPropertyListTest::tearDown()
{
}

void RVNGPropertyListTest::testInsertWithConversion()
{
	RVNGPropertyList props;

	// valid int
	props.insert("int", RVNGString("42"));
	CPPUNIT_ASSERT_EQUAL(42, props["int"]->getInt());
	CPPUNIT_ASSERT_EQUAL(RVNG_GENERIC, props["int"]->getUnit());
	props.insert("int", RVNGString("  42 "));
	CPPUNIT_ASSERT_EQUAL(42, props["int"]->getInt());
	// invalid int
	props.insert("int", RVNGString("42a"));
	CPPUNIT_ASSERT_EQUAL(0, props["int"]->getInt());
	CPPUNIT_ASSERT_EQUAL(RVNGString("42a"), props["int"]->getStr());

	const double eps = 0.00001;
	// valid double
	props.insert("double", RVNGString("3.14"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_GENERIC, props["double"]->getUnit());
	props.insert("double", RVNGString("  3.14 "));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_GENERIC, props["double"]->getUnit());
	// valid double with unit
	props.insert("double", RVNGString("3.14pt"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_POINT, props["double"]->getUnit());
	// TODO: is this really expected to work?
	props.insert("double", RVNGString("3.14  pt"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_POINT, props["double"]->getUnit());
	props.insert("double", RVNGString("3.14in"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_INCH, props["double"]->getUnit());
	props.insert("double", RVNGString("314%"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_PERCENT, props["double"]->getUnit());
	props.insert("double", RVNGString("3.14*"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_TWIP, props["double"]->getUnit());
	props.insert("double", RVNGString("2.54cm"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_INCH, props["double"]->getUnit());
	props.insert("double", RVNGString("25.4mm"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_INCH, props["double"]->getUnit());
	// invalid double
	props.insert("double", RVNGString("25.4a"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, props["double"]->getDouble(), eps);
	CPPUNIT_ASSERT_EQUAL(RVNG_UNIT_ERROR, props["double"]->getUnit());

	// valid bool
	props.insert("bool", RVNGString("true"));
	CPPUNIT_ASSERT_EQUAL(1, props["bool"]->getInt());
	CPPUNIT_ASSERT_EQUAL(RVNGString("true"), props["bool"]->getStr());
	props.insert("bool", RVNGString("FALSE"));
	CPPUNIT_ASSERT_EQUAL(0, props["bool"]->getInt());
	CPPUNIT_ASSERT_EQUAL(RVNGString("false"), props["bool"]->getStr());
	props.insert("bool", RVNGString("TRUE"));
	CPPUNIT_ASSERT_EQUAL(1, props["bool"]->getInt());
	props.insert("bool", RVNGString(" true "));
	CPPUNIT_ASSERT_EQUAL(1, props["bool"]->getInt());
	// invalid bool
	props.insert("bool", RVNGString("truer"));
	CPPUNIT_ASSERT_EQUAL(0, props["bool"]->getInt());
}

CPPUNIT_TEST_SUITE_REGISTRATION(RVNGPropertyListTest);

}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
