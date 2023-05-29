# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/hubertkulak/esp/esp-idf/components/bootloader/subproject"
  "/home/hubertkulak/esp/esp-idf/httpw12n/build/bootloader"
  "/home/hubertkulak/esp/esp-idf/httpw12n/build/bootloader-prefix"
  "/home/hubertkulak/esp/esp-idf/httpw12n/build/bootloader-prefix/tmp"
  "/home/hubertkulak/esp/esp-idf/httpw12n/build/bootloader-prefix/src/bootloader-stamp"
  "/home/hubertkulak/esp/esp-idf/httpw12n/build/bootloader-prefix/src"
  "/home/hubertkulak/esp/esp-idf/httpw12n/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/hubertkulak/esp/esp-idf/httpw12n/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/hubertkulak/esp/esp-idf/httpw12n/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
