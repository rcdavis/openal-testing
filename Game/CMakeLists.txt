project(Game)

add_executable(Game
    src/Main.cpp
)

target_compile_features(Game PRIVATE cxx_std_17)

find_package(OpenAL REQUIRED)

target_link_libraries(Game PRIVATE
    OpenAL::OpenAL
)
