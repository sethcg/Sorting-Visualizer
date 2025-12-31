# Sorting Algorithm Visualizer

### Description:

<dl>
  <dd>
    This application implements <a href="https://en.wikipedia.org/wiki/Sorting_algorithm">sorting algorithms</a>, representing their state with colors and shape positions.
  </dd>
</dl>

### Preview:

<details open>
  <summary><b>Demo</b></summary>
  <img width="274px" height="256px" src="https://github.com/user-attachments/assets/ecb20ad5-957e-4b4c-bd11-f576a8757b46" alt="demo">
  <br>
</details>

<details closed>
  <summary><b>Image</b></summary>
  <img width="728px" height="488px" src="https://github.com/user-attachments/assets/ead2ad2f-3a62-424c-b18f-9e53e9c5c031" alt="image"/>
  <br>
</details>

---
### Developer Notes:

```bash

# CONFIGURE
cmake --preset default

# BUILD DEBUG
cmake --build --preset debug
ctest --preset default --build-config debug

# BUILD RELEASE
cmake --build --preset release
ctest --preset default --build-config release

```

<details closed>
<summary><b>Tooling</b></summary>
<br/>

  - [x] SDL3
  - [x] ImGui
  - [x] Google Test
  - [x] Vcpkg
  - [x] CMake

</details>

<details closed>
<summary><b>Line Count</b></summary>
<br/>

```bash

# GET LINE COUNT (REQUIRES CLOC TO BE INSTALLED)
cloc --include-lang=C++,"C/C++ Header",CMake --exclude-dir=build,vcpkg --out=line-count.txt .

```

| Language         | Files | Blank | Comment | Code |
|:-----------------|:-----:|:-----:|:-------:|:----:|
| **C++**          | 11    | 122   | 34      | 417  |
| **C/C++ Header** | 11    | 127   | 25      | 295  |
| **CMake**        | 5     | 29    | 17      | 77   |
|                                                   |
| **Total**        | 39    | 268   | 76      | 789  |

</details>
