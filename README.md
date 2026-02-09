## Testing workflow
Look at [the example folder](https://github.com/malachycrossan/illiterate/tree/main/Example) to see how tests should be set up.

The workflow will look for any .c, .cpp, or .java files (`/FilePath/ProgramName.*`) that have changed, compile them, run them with all test cases (`/FilePath/tests/ProgramName_test#.in`), and collect their output (`/test-results/FilePath/ProgramName_test#_actual.out`). It will compare that with the expected output (`/FilePath/tests/ProgramName_test#.out`) to create a diff (`/test-results/FilePath/ProgramName_test#_diff.txt`) and an error log (`/test-results/FilePath/ProgramName_test#_error.log`).

Finally, it will compile all tests into a markdown document called `summary.md`. This is where you should view the results of your tests. [This](https://github.com/malachycrossan/illiterate/blob/main/test-results/summary.md) is the summary for **all** of the tests run from the most recent commit.
