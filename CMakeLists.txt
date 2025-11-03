cmake_minimum_required(VERSION 4.0)
project(home C)

set(CMAKE_C_STANDARD 11)

add_executable(home main.c
        tp2/bissextile.c
        tp2/times.c
        tp2/times.c
        tp3/serie.c
        tp3/matrice.c
        tp3/text.c
        custom/pi.c
        td6/exo.c
        td6/chained_list.c
        tp6/exo1.c
        tp3/text_normal.c
        tp4/duration.c
        tp4/sort.c
)
