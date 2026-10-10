#include <gtest/gtest.h>
#include "PostMachine.h"

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

TEST(PostMachineTest, Reset) {
    PostMachine pm;
    vector<string> code = {
        "> 1",
        "!"
    };
    pm.loadProgram(code);
    EXPECT_TRUE(pm.step());
    EXPECT_FALSE(pm.step());

    pm.reset();

    EXPECT_TRUE(pm.step());
}

TEST(PostMachineTest, ClearProgram){
    PostMachine pm;
    vector<string> code = {
        "> 1",
        "!"
    };
    pm.loadProgram(code);
    pm.clearProgram();
    EXPECT_FALSE(pm.step());
}
