add_executable(15_solver)

target_sources(15_solver PRIVATE
    ${PROJECT_SOURCE_DIR}/15_solver/main.cpp
)

add_subdirectory(
    board
)
