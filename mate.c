#define MATE_IMPLEMENTATION
#include "../include/mate.h"

i32 main(void) {
  StartBuild();
  {
    Executable executable = CreateExecutable((ExecutableOptions){
        .output = "main",
        .flags = "-Wall -g"
    });

    AddFile(executable, "./src/*.c");
    AddFile(executable, "../include/*.c");

    InstallExecutable(executable);

    errno_t err = RunCommand(executable.outputPath);
    Assert(err == SUCCESS, "RunCommand: failed, return from exe should always be SUCCESS"); // Assert that we return SUCCESS == 0
  }
  EndBuild();
}