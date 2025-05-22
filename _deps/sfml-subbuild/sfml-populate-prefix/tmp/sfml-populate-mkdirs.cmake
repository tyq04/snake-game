# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/My_code/Cpp/OOP/snake-game/_deps/sfml-src"
  "D:/My_code/Cpp/OOP/snake-game/_deps/sfml-build"
  "D:/My_code/Cpp/OOP/snake-game/_deps/sfml-subbuild/sfml-populate-prefix"
  "D:/My_code/Cpp/OOP/snake-game/_deps/sfml-subbuild/sfml-populate-prefix/tmp"
  "D:/My_code/Cpp/OOP/snake-game/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
  "D:/My_code/Cpp/OOP/snake-game/_deps/sfml-subbuild/sfml-populate-prefix/src"
  "D:/My_code/Cpp/OOP/snake-game/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/My_code/Cpp/OOP/snake-game/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/My_code/Cpp/OOP/snake-game/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
