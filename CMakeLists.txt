cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project("rdf-canonicalization-cpp-client" VERSION 0.5.0
        LANGUAGES CXX )

find_package(jsonld-cpp 0.5.0 CONFIG REQUIRED)
find_package(rdf-canonicalization-cpp 0.5.0 CONFIG REQUIRED)



add_executable(jsonld2canon jsonld2canon.cpp)

target_compile_features(jsonld2canon PRIVATE cxx_std_14)
set_target_properties(jsonld2canon PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(jsonld2canon rdf-canonicalization-cpp::rdf-canonicalization-cpp)



