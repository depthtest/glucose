set(main_test "test.cc")
add_executable(test_glucose ${main_test})
target_link_libraries(test_glucose glucose_sim)

set(main_test_par "test_parallel.cc")
add_executable(test_glucosep ${main_test_par})
target_link_libraries(test_glucosep glucose_par)