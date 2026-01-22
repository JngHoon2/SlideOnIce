# CMake 최소 버전 요구사항
# 로컬에 설치된 CMake 버전을 기입하셔야합니다.
cmake_minimum_required(VERSION 4.2.1)

# 프로젝트 이름 및 버전
project(SlideOnIce VERSION 0.1)

# 실행 파일 생성 (실행파일명, 소스파일명)
# build 디렉토리에서의 실행을 기준으로 작성되었습니다.
# 다른 디렉토리에서 실행하는 경우, 소스파일명의 디렉토리를 변경해야합니다.
add_executable(SlideOnIce ../src/main.cpp)
