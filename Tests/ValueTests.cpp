//
//  ValueTests.cpp
//  Fleece
//
//  Created by Jens Alfke on 11/26/15.
//  Copyright © 2015 Couchbase. All rights reserved.
//

#include "FleeceTests.hh"
#include "Value.hh"

namespace fleece {
    using namespace internal;

    class ValueTests : public CppUnit::TestFixture {
    public:

        void testPointers() {
            value v(4, kNarrow);
            AssertEqual(v.pointerValue<false>(), 4u);
            value w(4, kWide);
            AssertEqual(w.pointerValue<true>(), 4u);
        }

        void testDeref() {
            uint8_t data[6] = {0x01, 0x02, 0x03, 0x04, 0x80, 0x02};
            auto start = (const value*)&data[4];
            AssertEqual(start->pointerValue<false>(), 4u);
            auto dst = value::derefPointer<false>(start);
            AssertEqual((ptrdiff_t)dst - (ptrdiff_t)&data[0], 0L);
        }

        CPPUNIT_TEST_SUITE( ValueTests );
        CPPUNIT_TEST( testPointers );
        CPPUNIT_TEST( testDeref );
        CPPUNIT_TEST_SUITE_END();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(ValueTests);

}