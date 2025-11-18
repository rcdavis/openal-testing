project(Game)

add_executable(Game
    src/Utils/FileUtils.cpp
    src/SoundBuffer.cpp
    src/SoundEffect.cpp
    src/AudioEngine.cpp
    src/Main.cpp
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
     DESTINATION ${CMAKE_BINARY_DIR}/Game)

target_include_directories(Game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(Game PRIVATE cxx_std_17)

find_package(OpenAL REQUIRED)

target_link_libraries(Game PRIVATE
    OpenAL::OpenAL
)
