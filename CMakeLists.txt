CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(FeatureSearch)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_EXECUTABLE(a
    datum.cpp
    set.cpp
	main.cpp
)