# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

find_library( log-lib
              log )
find_library( opensles-lib
              OpenSLES )

# audiomodule
add_library( audiomodule
             SHARED
             src/main/cpp/internal/audio_module.c)

# buffersizeadapter
add_library( buffersizeadapter
             SHARED

             src/main/cpp/internal/audio_module.c

             src/main/cpp/utils/buffer_size_adapter.c)
target_link_libraries( buffersizeadapter )

# audiomoduleinternal
add_library( audiomoduleinternal
             SHARED
             src/main/cpp/internal/audio_module_internal.c
             src/main/cpp/internal/simple_barrier.c
             src/main/cpp/internal/shared_memory_internal.c
             src/main/cpp/opensl_stream/opensl_stream.c)
target_link_libraries( audiomoduleinternal
                       ${log-lib}
                       ${opensles-lib})

# audiomodulejava
add_library( audiomodulejava
             SHARED

             src/main/cpp/internal/audio_module_internal.c
             src/main/cpp/internal/simple_barrier.c
             src/main/cpp/internal/shared_memory_internal.c
             src/main/cpp/opensl_stream/opensl_stream.c

             src/main/cpp/internal/audio_module.c

             src/main/cpp/internal/audio_module_java.c)
target_link_libraries( audiomodulejava
                       ${log-lib}
                       ${opensles-lib})

# shared_memory_utils
add_library( shared_memory_utils
             SHARED
             src/main/cpp/internal/shared_memory_utils.c
             src/main/cpp/internal/shared_memory_internal.c)
target_link_libraries( shared_memory_utils
                       ${log-lib} )

# patchfield
add_library( patchfield
             SHARED

             src/main/cpp/internal/audio_module_internal.c
             src/main/cpp/internal/simple_barrier.c
             src/main/cpp/internal/shared_memory_internal.c
             src/main/cpp/opensl_stream/opensl_stream.c

            src/main/cpp/internal/patchfield.c)
target_link_libraries( patchfield
                       ${log-lib}
                       ${opensles-lib})

# lowpass
add_library( lowpass
             SHARED

             src/main/cpp/internal/audio_module_internal.c
             src/main/cpp/internal/simple_barrier.c
             src/main/cpp/internal/shared_memory_internal.c
             src/main/cpp/opensl_stream/opensl_stream.c

             src/main/cpp/internal/audio_module.c

             src/main/cpp/internal/patchfield.c

             src/main/cpp/lowpass/lowpass.c )
target_link_libraries( lowpass
                       ${opensles-lib}
                       ${log-lib})

# pcm
add_library( pcmsource
             SHARED

             src/main/cpp/internal/audio_module.c

             src/main/cpp/pcm/pcmsource.c )
target_link_libraries( pcmsource
                       ${log-lib})
