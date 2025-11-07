Package: pcan-basic:x64-windows@4.10.0.4

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.44.35219.0
- CMake Version: 4.1.1
-    vcpkg-tool version: 2025-10-16-71538f2694db93da4668782d094768ba74c45991
    vcpkg-scripts version: 195276f716 2025-11-06 (7 hours ago)

**To Reproduce**

`vcpkg install `

**Failure logs**

```
CMake Warning at scripts/cmake/vcpkg_common_functions.cmake:3 (message):
  vcpkg_common_functions has been removed and all values are automatically
  provided in all portfile.cmake invocations.  Please remove
  `include(vcpkg_common_functions)`.
Call Stack (most recent call first):
  C:/Users/matis/Documents/Revolve/PCAN-DillDall2/ports/pcan-basic/portfile.cmake:1 (include)
  scripts/ports.cmake:206 (include)


-- pcan-basic: Starting portfile execution for x64-windows
-- pcan-basic: Target architecture is x64
-- pcan-basic: Download details set - URL: https://www.peak-system.com/fileadmin/media/files/PCAN-Basic.zip, ZIP: PCANBasic_Windows.zip
-- pcan-basic: Creating download directory: C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/download
-- pcan-basic: ZIP will be downloaded to: C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/download/PCANBasic_Windows.zip
-- pcan-basic: Downloading zip from https://www.peak-system.com/fileadmin/media/files/PCAN-Basic.zip to C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/download/PCANBasic_Windows.zip
CMake Warning (dev) at C:/Users/matis/Documents/Revolve/PCAN-DillDall2/ports/pcan-basic/portfile.cmake:33 (file):
  Unexpected argument: HTTP_USER_AGENT
Call Stack (most recent call first):
  scripts/ports.cmake:206 (include)
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) at C:/Users/matis/Documents/Revolve/PCAN-DillDall2/ports/pcan-basic/portfile.cmake:33 (file):
  Unexpected argument: Mozilla/5.0 (compatible; VCPKG)
Call Stack (most recent call first):
  scripts/ports.cmake:206 (include)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- [download 0% complete]
-- [download 1% complete]
-- [download 2% complete]
-- [download 3% complete]
-- [download 4% complete]
-- [download 5% complete]
-- [download 6% complete]
-- [download 7% complete]
-- [download 8% complete]
-- [download 9% complete]
-- [download 10% complete]
-- [download 11% complete]
-- [download 12% complete]
-- [download 13% complete]
-- [download 14% complete]
-- [download 15% complete]
-- [download 16% complete]
-- [download 17% complete]
-- [download 18% complete]
-- [download 19% complete]
-- [download 20% complete]
-- [download 21% complete]
-- [download 22% complete]
-- [download 23% complete]
-- [download 24% complete]
-- [download 25% complete]
-- [download 26% complete]
-- [download 27% complete]
-- [download 28% complete]
-- [download 29% complete]
-- [download 30% complete]
-- [download 31% complete]
-- [download 32% complete]
-- [download 33% complete]
-- [download 34% complete]
-- [download 35% complete]
-- [download 36% complete]
-- [download 37% complete]
-- [download 38% complete]
-- [download 39% complete]
-- [download 40% complete]
-- [download 41% complete]
-- [download 42% complete]
-- [download 43% complete]
-- [download 44% complete]
-- [download 45% complete]
-- [download 46% complete]
-- [download 47% complete]
-- [download 48% complete]
-- [download 49% complete]
-- [download 50% complete]
-- [download 51% complete]
-- [download 52% complete]
-- [download 53% complete]
-- [download 54% complete]
-- [download 55% complete]
-- [download 56% complete]
-- [download 57% complete]
-- [download 58% complete]
-- [download 59% complete]
-- [download 60% complete]
-- [download 61% complete]
-- [download 62% complete]
-- [download 63% complete]
-- [download 64% complete]
-- [download 65% complete]
-- [download 66% complete]
-- [download 67% complete]
-- [download 68% complete]
-- [download 69% complete]
-- [download 70% complete]
-- [download 71% complete]
-- [download 72% complete]
-- [download 73% complete]
-- [download 74% complete]
-- [download 75% complete]
-- [download 76% complete]
-- [download 77% complete]
-- [download 78% complete]
-- [download 79% complete]
-- [download 80% complete]
-- [download 81% complete]
-- [download 82% complete]
-- [download 83% complete]
-- [download 84% complete]
-- [download 85% complete]
-- [download 86% complete]
-- [download 87% complete]
-- [download 88% complete]
-- [download 89% complete]
-- [download 90% complete]
-- [download 91% complete]
-- [download 92% complete]
-- [download 93% complete]
-- [download 94% complete]
-- [download 95% complete]
-- [download 96% complete]
-- [download 97% complete]
-- [download 98% complete]
-- [download 99% complete]
-- [download 100% complete]
-- pcan-basic: ZIP downloaded successfully.
-- pcan-basic: Downloaded zip size: 12118416 bytes
-- pcan-basic: Creating extraction directory: C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src
-- pcan-basic: Extracting zip to C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src
-- pcan-basic: Extraction completed.
-- pcan-basic: Contents of extract dir: C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/ARM64;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/Include;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/LiesMich.txt;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/NuGet;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/PCAN-Parameter_Documentation.pdf;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/PCANBasic_deu.chm;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/PCANBasic_enu.chm;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/ReadMe.txt;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/Samples;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/x64;C:/Users/matis/vcpkg/packages/pcan-basic_x64-windows/src/x86
-- pcan-basic: Found directory: ARM64
-- pcan-basic: Found directory: Include
-- pcan-basic: Found directory: NuGet
-- pcan-basic: Found directory: Samples
-- pcan-basic: Found directory: x64
-- pcan-basic: Found directory: x86
CMake Error at C:/Users/matis/Documents/Revolve/PCAN-DillDall2/ports/pcan-basic/portfile.cmake:81 (message):
  pcan-basic: Could not find PCAN-Basic directory in extracted files
Call Stack (most recent call first):
  scripts/ports.cmake:206 (include)



```

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "dependencies": [
    "fmt",
    "pcan-basic"
  ]
}

```
</details>
