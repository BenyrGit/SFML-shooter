cmake_minimum_required(VERSION 3.28)

project(SFMLGameBook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System)

add_executable(SFMLGame
    src/main.cpp
    src/Game.cpp
    src/Game.hpp
    src/ResourceHolder.hpp
    src/ResourceIdentifiers.hpp
    src/ResourceTypes.hpp
    src/SceneNode.hpp
    src/SceneNode.cpp
    src/SpriteNode.hpp
    src/SpriteNode.cpp
    src/Entity.hpp
    src/Entity.cpp
    src/Aircraft.cpp
    src/Aircraft.hpp
    src/World.cpp
    src/World.hpp
    src/Category.hpp
    src/Command.hpp
    src/CommandQueue.cpp
    src/CommandQueue.hpp
    src/Player.cpp
    src/Player.hpp
    src/State.cpp
    src/State.hpp
    src/StateIdentifiers.hpp
    src/StateStack.cpp
    src/StateStack.hpp
    src/GameState.cpp
    src/GameState.hpp
    src/TitleState.cpp
    src/TitleState.hpp
    src/MenuState.cpp
    src/MenuState.hpp
    )

target_link_libraries(SFMLGame PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_compile_features(SFMLGame PRIVATE cxx_std_20)

add_custom_command(
    TARGET SFMLGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:SFMLGame>/assets
)