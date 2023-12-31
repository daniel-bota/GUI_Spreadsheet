A simple QtQuick implementation of a spreadsheet application with limited functionality. You can watch a short demonstration on Youtube! [![Youtube](https://i.ytimg.com/vi/Q5gcqy2bhkM/hqdefault.jpg)](https://youtu.be/Q5gcqy2bhkM).

This project uses [Qt 6.6.0](https://www.qt.io/offline-installers).

In order to run this project in Qt Creator, you need to:

1. Create a user account at https://www.qt.io
2. Download [Qt for open source use](https://www.qt.io/download-open-source#contributing) -> "Download the Qt Online Installer" or follow [this link](https://www.qt.io/download-qt-installer-oss?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4).
3. During installation, make sure to:
- under Qt, check at least version 6.6.0
- under Qt version, check MSVC 2019 64-bit
- under Developer and Designer Tools, check the latest version of Qt Creator, and the provided version of CMake and Ninja
4. Install Visual Studio and C++ build tools (https://visualstudio.microsoft.com/). During installation, make sure to check "Desktop development with C++".
5. Open CMakeLists.txt with Qt Creator
6. In the "Configure Project" window, select "Desktop Qt \<VERSION\> MSVC2019 64bit" kit and, under Details, select the build type of your choosing. Qt Creator should automatically find the MSVC compiler and link it to the active build kit. Otherwise, you must provide the compiler path manually  by opening the "Manage Kits..." dialog.
7. Press "Configure Project".

Implemented formulas:

- Reference (=A1)
- Range (A1:B5)
- SUM (=SUM(arg1;arg2;...))
- COUNT (=COUNT(...))
- AVERAGE (=AVG(...))
- MINIMUM (=MIN(...))
- MAXIMUM (=MAX(...))
- MODULUS (=MOD(arg1;arg2))
- POWER (=POW(arg1;arg2))
- LENGTH (=LEN(arg1))
- TRIM (=TRIM(arg1))
- CONCATENATE (=CONCAT(arg1;arg2))

Table navigation is possible using the arroy keys, Tab and the mouse. 

Cell data can be input by typing straight away and commited by pressing Enter or Tab. The input can be dropped by pressing Esc. Cell contents can be edited using F2.  

The columns and rows are resizable, but the changes remain available only for the current instance of the application, they don't get saved.

KNOWN ISSUES: Sometimes text that doesn't fit the cell is not displayed until the cell is manually resized (horizontally or vertically).