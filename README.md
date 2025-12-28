# Sorting Algorithm Visualizer

### Description:

<dl>
  <dd>
    This is a C++ application that implements various <a href="https://en.wikipedia.org/wiki/Sorting_algorithm">sorting algorithms</a> 
    using colors and shapes to represent how the underlying data structure is changing.
  </dd>
</dl>

<dl>
  <dd>
  <details closed>
  <summary><b>Time Complexity</b></summary>

  | Name       | Best               | Average            | Worst              |
  |:-----------|:-------------------|:-------------------|:-------------------|
  | Bubble     | O(n)               | O(n<sup>2</sup>)   | O(n<sup>2</sup>)   |
  | Cocktail   | O(n)               | O(n<sup>2</sup>)   | O(n<sup>2</sup>)   |
  | Heap       | O(n log(n))        | O(n log(n))        | O(n log(n))        |
  | Insertion  | O(n)               | O(n<sup>2</sup>)   | O(n<sup>2</sup>)   |
  | Merge      | O(n log(n))        | O(n log(n))        | O(n log(n))        |
  | Quick      | O(n log(n))        | O(n log(n))        | O(n<sup>2</sup>)   |
  | Radix      | O(nk)              | O(nk)              | O(nk)              |
  | Selection  | O(n<sup>2</sup>)   | O(n<sup>2</sup>)   | O(n<sup>2</sup>)   |

  </details>
  </dd>
</dl>

### Preview:

<details open>
  <summary>Show</summary>
  <img width="598px" height="600px" src="https://github.com/user-attachments/assets/53180fca-318b-4c76-9f2f-363413b2bc00" alt="image">


  <br>
</details>

### Tooling:

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

# BUILD DEBUG (RUN TESTS)
cmake --build --preset debug
ctest --preset debug

# BUILD RELEASE
cmake --build --preset release

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
