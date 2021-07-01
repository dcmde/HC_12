cmake_minimum_required(VERSION 3.10)
project(hc12 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

set(USER_SRC
        rs232.c
        hc12.c
        )

add_executable(hc_check check.c ${USER_SRC})
add_executable(hc_tx tx.c ${USER_SRC})
add_executable(hc_rx rx.c ${USER_SRC})