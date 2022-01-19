set(main_test "test.cc")
add_executable(test_glucose ${main_test})
target_link_libraries(test_glucose glucose)