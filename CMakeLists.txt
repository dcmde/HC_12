cmake_minimum_required(VERSION 3.10)
project(hc12 C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(.
        include)

set(USER_SRC
        rs232.c
        hc12.c
        )

add_executable(hc_check check.c ${USER_SRC})
add_executable(hc_tx tx.c ${USER_SRC})
add_executable(hc_rx rx.c ${USER_SRC})

add_executable(cli_tx tx_cli.c ${USER_SRC})
target_link_libraries(cli_tx ${CURSES_LIBRARIES})