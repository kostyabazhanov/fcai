#include "test_bitset.h"

#include <cstdio>

#include <vector>

TestFunctionGroup TestBitSetAll("TestBitSet", &TestBitSet);

std::vector<TestFunction> GetAllBitSetTestFunctions() {
    std::vector<TestFunction> res;
    res.push_back(TestFunction("TestBitSetConctruct", &TestBitSetConctruct));
    res.push_back(TestFunction("TestBitSetSetAndTest", &TestBitSetSetAndTest));
    res.push_back(TestFunction("TestBitSetCopyConstruct", &TestBitSetCopyConstruct));
    res.push_back(TestFunction("TestBitSetAnyAndNone", &TestBitSetAnyAndNone));
    res.push_back(TestFunction("TestBitSetSetAllAndTestAll", &TestBitSetSetAllAndTestAll));
    res.push_back(TestFunction("TestBitSetFlipAll", &TestBitSetFlipAll));
    res.push_back(TestFunction("TestBitSetFlip", &TestBitSetFlip));
    res.push_back(TestFunction("TestBitSetIsSubsetOf", &TestBitSetIsSubsetOf));
    res.push_back(TestFunction("TestBitSetIsProperSubsetOf", &TestBitSetIsProperSubsetOf));
    res.push_back(TestFunction("TestBitSetSize", &TestBitSetSize));
    return res;
}

TEST_RESULT TestBitSet(const std::string& indent, size_t& ok, size_t& fail) {
    fprintf(stdout, "%sTestBitSet:\n", indent.c_str());
    ok = 0;
    fail = 0;
    TestFunctionVector allTests = GetAllBitSetTestFunctions();
    RunTestsFromGroup(allTests, indent + "\t", ok, fail);

    fprintf(stdout, "%sTotal subtest OK: %lu\n", indent.c_str(), ok);
    fprintf(stdout, "%sTotal subtest FAIL: %lu\n", indent.c_str(), fail);
    const double p = (0 == ok + fail ? 100 : static_cast<double>(ok * 100) / static_cast<double>(ok + fail));
    fprintf(stdout, "%sSuccessfull subtests: %.2lf %%\n", indent.c_str(), p);
    fprintf(stdout, "%sTestBitSet:", indent.c_str());
    TEST_RESULT res = (0 == fail ? TEST_RESULT_OK : TEST_RESULT_FAIL);
    PrintOkFailAndLineFeed(res, stdout);
    return res;
}

TEST_RESULT TestBitSetConctruct() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    if (bs.size() != len) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < len; ++i) {
        if (bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetSetAndTest() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
        }
    }
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && !bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetCopyConstruct() {
    const size_t len = 100;
    FCA::BitSet bsOriginal(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bsOriginal.set(i);
        }
    }
    const FCA::BitSet bsCopy(bsOriginal);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && !bsCopy.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && bsCopy.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetAnyAndNone() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
        }
    }
    if (!bs.any() || bs.none()) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < len; ++i) {
        bs.reset(i);
    }
    if (bs.any() || !bs.none()) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetSetAllAndTestAll() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    bs.set();
    for (size_t i = 0; i < len; ++i) {
        if (!bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    bs.reset();
    for (size_t i = 0; i < len; ++i) {
        if (bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetFlipAll() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
        }
    }
    bs.flip();
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && bs.test(i)) {
            return TEST_RESULT_FAIL;
        } else if (i % 3 != 0 && !bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetFlip() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
        }
    }
    for (size_t i = 0; i < len; ++i) {
        bs.flip(i);
    }
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && bs.test(i)) {
            return TEST_RESULT_FAIL;
        } else if (i % 3 != 0 && !bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetIsSubsetOf() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs3.set(i);
        }
    }
    FCA::BitSet bs4(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs4.set(i);
        }
    }
    if (!bs1.is_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (!bs2.is_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (!bs3.is_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (bs4.is_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetIsProperSubsetOf() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs3.set(i);
        }
    }
    FCA::BitSet bs4(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs4.set(i);
        }
    }
    if (bs1.is_proper_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (!bs2.is_proper_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (bs3.is_proper_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (bs4.is_proper_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetSize() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    return (bs.size() == len ? TEST_RESULT_OK : TEST_RESULT_FAIL);
}
