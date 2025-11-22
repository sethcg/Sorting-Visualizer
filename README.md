# Sorting Algorithm Visualizer

### Description:

### Preview:

### Tooling:
- [x] C++ Language
- [x] SDL3
- [x] ImGui
- [x] Google Test
- [x] Vcpkg
- [x] CMake

---
### Developer Notes:

```bash

# CONFIGURE
cmake --preset default

# BUILD
cmake --build --preset default

# RUN TESTS
ctest --preset default

```

<details closed>
<summary><b>Line Count</b></summary>
<br/>

```bash

# GET LINE COUNT (REQUIRES CLOC TO BE INSTALLED)
cloc --include-lang=C++,"C/C++ Header",CMake --exclude-dir=build,vcpkg --out=line-count.txt .

```

| Language         | Files | Blank | Comment | Code |
|:-----------------|:-----:|:-----:|:-------:|:----:|
| **C++**          | 19    | 385   | 213     | 1150 |
| **C/C++ Header** | 13    | 104   | 1       | 186  |
| **CMake**        | 4     | 24    | 19      | 63   |
|                                                   |
| **Total**        | 36    | 513   | 233     | 1399 |

</details>