cmake_minimum_required(VERSION 3.5)

project(posix_timers LANGUAGES C)


add_executable(simple_threading_timer simple_threading_timer.c)
target_link_libraries(simple_threading_timer rt)


add_executable(advanced_interrupt_timer advanced_interrupt_timer.c)
target_link_libraries(advanced_interrupt_timer rt)


add_executable(signal_interrupt_timer signal_interrupt_timer.c)
target_link_libraries(signal_interrupt_timer rt)
