//
//  KeyTree.hh
//  Fleece
//
//  Created by Jens Alfke on 5/14/16.
//  Copyright (c) 2016 Couchbase. All rights reserved.
//

#pragma once

#include "slice.hh"
#include <vector>

namespace fleece {

    /** A very compact dictionary of strings (or arbitrary blobs) that bidirectionally maps each
        one to a small positive integer. Internally it's stored as a tree, so lookup time is
        O(log n). The total storage overhead (beyond the sizes of the strings themselves) is
        about 1.5n bytes, although this increases somewhat as the length of the strings or the
        total size of the dictionary increase. */
    class KeyTree {
    public:
        KeyTree(const void *encodedDataStart);
        KeyTree(alloc_slice encodedData);
        
        static KeyTree fromSortedStrings(const std::vector<slice>&);
        static KeyTree fromStrings(std::vector<slice>);

        unsigned operator[] (slice str) const;
        slice operator[] (unsigned id) const;

        slice encodedData() const       {return _ownedData;}

    private:
        alloc_slice _ownedData;
        const void * _data;
    };

}
