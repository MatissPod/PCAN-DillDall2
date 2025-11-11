Package: pcan-basic-linux:x64-windows@4.10.0.4

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.44.35219.0
- CMake Version: 4.1.1
-    vcpkg-tool version: 2025-10-16-71538f2694db93da4668782d094768ba74c45991
    vcpkg-scripts version: 195276f716 2025-11-06 (4 days ago)

**To Reproduce**

`vcpkg install `

**Failure logs**

```
CMake Warning at scripts/cmake/vcpkg_common_functions.cmake:3 (message):
  vcpkg_common_functions has been removed and all values are automatically
  provided in all portfile.cmake invocations.  Please remove
  `include(vcpkg_common_functions)`.
Call Stack (most recent call first):
  C:/Users/matis/Documents/Revolve/PCAN-DillDall2/ports/pcan-basic-linux/portfile.cmake:1 (include)
  scripts/ports.cmake:206 (include)


-- pcan-basic: Starting portfile execution for x64-linux
-- pcan-basic: Download details set - URL: https://www.peak-system.com/quick/BasicLinux, Tarball: PCAN-Basic_API.tar.gz, Folder: PCAN-Basic_Linux-4.10.0.4
-- pcan-basic: Creating download directory: C:/Users/matis/vcpkg/packages/pcan-basic-linux_x64-windows/download
-- pcan-basic: Tarball will be downloaded to: C:/Users/matis/vcpkg/packages/pcan-basic-linux_x64-windows/download/PCAN-Basic_API.tar.gz
-- pcan-basic: Downloading tarball from https://www.peak-system.com/quick/BasicLinux to C:/Users/matis/vcpkg/packages/pcan-basic-linux_x64-windows/download/PCAN-Basic_API.tar.gz
CMake Warning (dev) at C:/Users/matis/Documents/Revolve/PCAN-DillDall2/ports/pcan-basic-linux/portfile.cmake:20 (file):
  Unexpected argument: HTTP_USER_AGENT
Call Stack (most recent call first):
  scripts/ports.cmake:206 (include)
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) at C:/Users/matis/Documents/Revolve/PCAN-DillDall2/ports/pcan-basic-linux/portfile.cmake:20 (file):
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
-- pcan-basic: Tarball downloaded successfully.
-- pcan-basic: Downloaded tarball size: 3573612 bytes
-- pcan-basic: Creating extraction directory: C:/Users/matis/vcpkg/packages/pcan-basic-linux_x64-windows/src
-- pcan-basic: Extracting tarball to C:/Users/matis/vcpkg/packages/pcan-basic-linux_x64-windows/src
-- pcan-basic: Extraction completed.
-- pcan-basic: API directory set to: C:/Users/matis/vcpkg/packages/pcan-basic-linux_x64-windows/src/PCAN-Basic_Linux-4.10.0.4
-- pcan-basic: Build directory set to: C:/Users/matis/vcpkg/packages/pcan-basic-linux_x64-windows/src/PCAN-Basic_Linux-4.10.0.4/libpcanbasic/pcanbasic
-- pcan-basic: Running 'make clean' in C:/Users/matis/vcpkg/packages/pcan-basic-linux_x64-windows/src/PCAN-Basic_Linux-4.10.0.4/libpcanbasic/pcanbasic
CMake Error at C:/Users/matis/Documents/Revolve/PCAN-DillDall2/ports/pcan-basic-linux/portfile.cmake:62 (message):
  pcan-basic: 'make clean' failed with error code no such file or directory
Call Stack (most recent call first):
  scripts/ports.cmake:206 (include)



```

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "dependencies": [
    "fmt",
    "pcan-basic-linux",
    "pcan-basic-windows"
  ]
}

```
</details>
