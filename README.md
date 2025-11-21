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
| **C++**          | 17    | 336   | 182     | 1018 |
| **C/C++ Header** | 12    | 92    | 1       | 171  |
| **CMake**        | 4     | 24    | 19      | 63   |
|                                                   |
| **Total**        | 33    | 452   | 202     | 1252 |

</details>