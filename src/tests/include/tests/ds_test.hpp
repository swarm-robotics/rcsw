/*******************************************************************************
 * Name            : ds_test.h
 * Project         : ds
 * Module          : ds
 * Description     : Header file for common DS test routines (C++)
 * Creation Date   : Sun Apr 27 19:29:22 2014
 * Original Author : jharwell
 *
 ******************************************************************************/

#define _DS_TEST_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "ds_test.h"

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
/* Test data element for all data structures */
struct element_set {
    element_set(
        int size):
        size_(size),
        elts_(new struct element[size]) {}
    int size_;
    struct element* elts_;
    ~element_set() {
        delete[] elts_;
    }
    void data_gen(void) {
        for (int i = 0; i < size_; ++i) {
            elts_[i].value1 = (rand() % 25);
        } /* for(i..) */
    }
    struct element* elts(void) { return elts_;}
};

#undef _DS_TEST_HPP_
