cmake_minimum_required(VERSION 3.31)
project(ChessProj)

set(CMAKE_CXX_STANDARD 20)

add_executable(ChessProj src/main.cpp
        src/Entities/Board.cpp
        include/ChessProj/Board.h
        src/Entities/Piece.cpp
        include/ChessProj/Piece.h
        src/Factories/PieceFactory.h)

target_include_directories(ChessProj PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)