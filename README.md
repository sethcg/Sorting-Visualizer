# Sorting Algorithm Visualizer

### Description:

<details closed>
<summary><b>Tooling</b></summary>
<br/>

- [x] C++ Language
- [x] SDL3
- [x] ImGui
- [x] Google Test
- [x] Vcpkg
- [x] CMake

</details>

### Preview:

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
| **C++**          | 21    | 424   | 227     | 1253 |
| **C/C++ Header** | 14    | 112   | 1       | 197  |
| **CMake**        | 4     | 24    | 19      | 63   |
|                                                   |
| **Total**        | 39    | 560   | 247     | 1513 |

</details>