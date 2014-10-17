
find_package(Boost)
find_package(Boost COMPONENTS unit_test_framework)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_custom_target(tests)

include_directories(${Boost_INCLUDE_DIR})

function(add_boost_test name)
  add_executable(${name} EXCLUDE_FROM_ALL ${ARGN})

  target_link_libraries(${name} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  
  add_test(${name} ./${name})
  
  add_dependencies(check ${name})
  add_dependencies(tests ${name})
endfunction()

add_boost_test(string string.cpp)
add_boost_test(istr istr.cpp)