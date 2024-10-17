add_executable(15_solver)

target_sources(15_solver PRIVATE
    ${PROJECT_SOURCE_DIR}/15_solver/main.cpp
    ${PROJECT_SOURCE_DIR}/15_solver/board/board.cpp
    ${PROJECT_SOURCE_DIR}/15_solver/solver/bfs_solver.cpp
)
