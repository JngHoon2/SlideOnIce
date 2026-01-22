# CMake 최소 버전 요구사항
# 로컬에 설치된 CMake 버전을 기입하셔야합니다.
cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 및 버전
project(SlideOnIce VERSION 0.1)

# 실행 파일 생성 (실행파일명, 소스파일명)
# build 디렉토리에서의 실행을 기준으로 작성되었습니다.
# 다른 디렉토리에서 실행하는 경우, 소스파일명의 디렉토리를 변경해야합니다.

file(GLOB_RECURSE SOURCES "src/*.cpp")
message(STATUS "-----------------------------------")
message(STATUS "찾은 소스 파일 목록:")

foreach(FILE_PATH ${SOURCES})
    message(STATUS "  - ${FILE_PATH}")
endforeach()

message(STATUS "-----------------------------------")

if(NOT SOURCES)
    message(FATAL_ERROR "소스 파일을 찾지 못했습니다! 경로를 확인하세요.")
endif()

add_executable(SlideOnIce ${SOURCES})

target_include_directories(SlideOnIce PUBLIC "include")