cmake_minimum_required (VERSION 3.2)
set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")

project (smileInterface)

set (TEST_VERSION 0.1)

set(CMAKE_BUILD_TYPE "Release")

find_package(Eigen3 3.1.0)
find_package(boost REQUIRED)
find_package(nlohmann_json 3.1.0)

INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
#set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -march=native -fopenmp")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} /Ot /openmp /favor:INTEL64 /arch:AVX2 /fp:fast" )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRC)

include_directories(${PROJECT_SOURCE_DIR}/src)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(interface ${DIR_SRC})

target_link_libraries(interface PRIVATE nlohmann_json::nlohmann_json)