#include <gtest/gtest.h>
#include <sstream>
#include "MultiSet.h"
#include "PostMachine.h"

using namespace std;

TEST(MultiSetTest, ElementConstructorsAndAssignment) {
    Element e1("a");
    Element e2("b");
    Element e3 = e1;
    EXPECT_TRUE(e1 == e3);
    EXPECT_TRUE(e1 != e2);

    e3 = e2;
    EXPECT_TRUE(e3 == e2);
}

TEST(MultiSetTest, SetOperations) {
    MultiSet ms;
    EXPECT_TRUE(ms.empty());
    EXPECT_EQ(ms.size(), 0);

    ms.add("a");
    MultiSet nested("{b, c}");
    ms.add(nested);

    EXPECT_EQ(ms.size(), 2);

    Element elA("a");
    EXPECT_EQ(ms.count(elA), 1);

    EXPECT_TRUE(ms.remove(elA));
    EXPECT_FALSE(ms.remove(elA));
    EXPECT_EQ(ms.size(), 1);

    ms.clear();
    EXPECT_TRUE(ms.empty());
}

TEST(MultiSetTest, MathOperators) {
    MultiSet ms1("{a, a, b}");
    MultiSet ms2("{a, c}");

    MultiSet sum = ms1 + ms2;
    EXPECT_EQ(sum.size(), 5);

    MultiSet diff = ms1 - ms2;
    EXPECT_EQ(diff.size(), 2);

    MultiSet inter = ms1.intersect(ms2);
    EXPECT_EQ(inter.size(), 1);
}

TEST(MultiSetTest, ParsingAndStreams) {
    MultiSet ms1;
    stringstream input("{x, {y, z}, x}");
    input >> ms1;
    EXPECT_EQ(ms1.size(), 3);

    stringstream output;
    output << ms1;
    string result = output.str();
    EXPECT_TRUE(result.find("x") != string::npos);
}

TEST(MultiSetTest, EqualityAndCopying) {
    MultiSet ms1("{a, b, c}");
    MultiSet ms2("{c, a, b}");
    MultiSet ms3("{a, a}");

    EXPECT_TRUE(ms1 == ms2);
    EXPECT_FALSE(ms1 == ms3);

    MultiSet ms4 = ms1;
    EXPECT_TRUE(ms4 == ms1);

    ms3 = ms1;
    EXPECT_TRUE(ms3 == ms1);
}

TEST(PostMachineTest, InitializationAndTape) {
    PostMachine pm(5);
    vector<int> startTape = {4, 6};
    pm.setTape(startTape);

    testing::internal::CaptureStdout();
    pm.printState();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Tape:") != string::npos);
}

TEST(PostMachineTest, AllCommandsExecution) {
    PostMachine pm(0);
    vector<int> tape = {1};
    pm.setTape(tape);

    pm.addInstruction('>', 1);
    pm.addInstruction('?', 2, 3);
    pm.addInstruction('>', 4);
    pm.addInstruction('0', 4);
    pm.addInstruction('<', 5);
    pm.addInstruction('1', 6);
    pm.addInstruction('!', -1);

    EXPECT_TRUE(pm.step());
    EXPECT_TRUE(pm.step());
    EXPECT_TRUE(pm.step());
    EXPECT_TRUE(pm.step());
    EXPECT_TRUE(pm.step());
    EXPECT_FALSE(pm.step());
}

TEST(PostMachineTest, RunAndLoadProgram) {
    PostMachine pm;
    vector<string> code = {
        "> 1",
        "1 2",
        "!"
    };
    pm.loadProgram(code);
    pm.run();

    PostMachine emptyMachine;
    EXPECT_FALSE(emptyMachine.step());
}

TEST(PostMachineTest, InvalidCommand) {
    PostMachine pm;
    pm.addInstruction('X', 1);
    EXPECT_FALSE(pm.step());
}
