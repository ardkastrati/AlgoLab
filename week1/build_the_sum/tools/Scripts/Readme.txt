This file is bundled with 3 files:

In general, the setup assumes that
- the code is located in file "main.cpp"
- the testcases are located in folder "test" named as "*.in"
- the reference solutions are located in folder "test" named as "*.out"

More naming conventions (that are enforced automatically)
- the executable is "./main"

*Makefile*
Defines the basic necessities to compile and clean the project, and includes "helpers.mk"

*helpers.mk*
Defines some useful Makefile targets. Its default configuration makes it work well with "Makefile" and also with the Makefile generated from "setup_cgal.sh". It e.g. offers "make test", which checks the program on all available ".in" files.

*setup_cgal.sh*
Sets up cgal, enabling the following:
- Enables c++11 features
- Enables running valgrind on the generated executable
- Disables optimizations, simplifying debugging
- Compiles in debug mode
- Includes "helpers.mk"
This requires that "helpers.mk" is also available.

Notes:
- If you have a CGAL task, run "setup_cgal.sh" and copy the "helpers.mk" to your project folder. The Makefile is generated automatically by "setup_cgal.sh"
- If you have a non-CGAL task, copy "Makefile" and "helpers.mk" to your project folder
- This also works with eclipse, assuming you generate your project using "File -> New -> C++ Project -> Makefile project -> Empty Project -> Cross GCC -> Finish". Do not forget to enable C++11 features using "Right click on project -> Properties -> C/C++ General -> Preprocessor Include Paths, Macros etc. -> Tab Providers -> CDT GCC Built-in Compiler Settings -> append '-std=c++11' to Command to get compiler specs" and "Right click on project -> Properties -> C/C++ General -> Paths and Symbols -> Symbols -> GNU C++ -> Click "Add..." -> Put '__GXX_EXPERIMENTAL_CXX0X__' into 'Name', leave 'Value' blank -> OK -> OK". Sometimes, this only takes effect after Restart or after "Right click on project -> Index -> Rebuild"
