cmake_minimum_required(VERSION 3.20)

project(
    MultiCameraStreamer
    VERSION 1.0.0
    DESCRIPTION "Multi-pipeline GStreamer application for virtual RTSP cameras"
    LANGUAGES C
)

# -------------------------------------------------------------------
# C Standard
# -------------------------------------------------------------------

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------------------------------------------
# Dependencies
# -------------------------------------------------------------------

find_package(PkgConfig REQUIRED)

pkg_check_modules(
    GSTREAMER
    REQUIRED
    IMPORTED_TARGET
    gstreamer-1.0
)

# -------------------------------------------------------------------
# Executable
# -------------------------------------------------------------------

add_executable(${PROJECT_NAME}

    src/main.c
    src/application.c
    src/pipeline_manager.c
    src/camera.c
    src/camera_pipeline.c
    src/config_manager.c
)

# -------------------------------------------------------------------
# Include Directories
# -------------------------------------------------------------------

target_include_directories(${PROJECT_NAME}

    PRIVATE

        include
)

# -------------------------------------------------------------------
# Link Libraries
# -------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}

    PRIVATE

        PkgConfig::GSTREAMER
)