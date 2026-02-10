## Testing workflow
Look at [the example folder](https://github.com/malachycrossan/illiterate/tree/main/Example) to see how tests should be set up.

DISCLAIMER: I vibecoded the github actions because I don't know the syntax.

The workflow will look for any .c, .cpp, or .java files (`/FilePath/ProgramName.*`) that have changed, compile them, run them with all test cases (`/FilePath/tests/ProgramName_test#.in`), and collect their output (`/test-results/FilePath/ProgramName_test#_actual.out`). It will compare that with the expected output (`/FilePath/tests/ProgramName_test#.out`) to create a diff (`/test-results/FilePath/ProgramName_test#_diff.txt`) and an error log (`/test-results/FilePath/ProgramName_test#_error.log`).

This means that your folder structure relative to the root directory is essentially duplicated into the directory called `test-results`

Finally, it will compile all tests into a markdown document called `summary.md`. This is where you should view the results of your tests. [This](https://github.com/malachycrossan/illiterate/blob/main/test-results/summary.md) is the summary for **all** of the tests run from the most recent commit.

```
FilePath/
├─ ProgramName.c OR ProgramName.cpp OR ProgramName.java
├─ tests/
│  ├─ ProgramName_test1.in
│  ├─ ProgramName_test1.out
│  ├─ ProgramName_test2.in
│  ├─ ProgramName_test2.out
test-results/
├─ FilePath/
│  ├─ SUMMARY.md                       //summary of tests inside 'FilePath'
│  ├─ ProgramName_test1_actual.out
│  ├─ ProgramName_test2_actual.out
│  ├─ ProgramName_test1_diff.txt
│  ├─ ProgramName_test2_diff.txt
│  ├─ ProgramName_test1_error.log
│  ├─ ProgramName_test2_error.log
├─ summary.md                          //summary of all tests
```
