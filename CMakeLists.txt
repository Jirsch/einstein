cmake_minimum_required(VERSION 2.8.4)
project(einstein)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    buffer.cpp
    buffer.h
    conf.cpp
    conf.h
    convert.cpp
    convert.h
    descr.cpp
    descr.h
    einstein.res
    exceptions.h
    font.cpp
    font.h
    formatter.cpp
    formatter.h
    game.cpp
    game.h
    horhints.cpp
    horhints.h
    i18n.cpp
    i18n.h
    iconset.cpp
    iconset.h
    lexal.cpp
    lexal.h
    main.cpp
    main.h
    menu.cpp
    messages.cpp
    messages.h
    opensave.cpp
    opensave.h
    options.cpp
    options.h
    puzgen.cpp
    puzgen.h
    puzzle.cpp
    puzzle.h
    random.cpp
    random.h
    regstorage.cpp
    regstorage.h
    resources.cpp
    resources.h
    rules.cpp
    screen.cpp
    screen.h
    sound.cpp
    sound.h
    storage.cpp
    storage.h
    streams.cpp
    streams.h
    table.cpp
    table.h
    tablestorage.cpp
    tablestorage.h
    tokenizer.cpp
    tokenizer.h
    toolKit.cpp
    toolKit.h
    topscores.cpp
    topscores.h
    unicode.cpp
    unicode.h
    utils.cpp
    utils.h
    verthints.cpp
    verthints.h
    visitor.h
    widgets.cpp
    widgets.h)

 FIND_LIBRARY(COCOA_LIBRARY Cocoa)

 link_libraries( sdl sdl_mixer sdl_ttf SDLmain z ${COCOA_LIBRARY})


add_executable(einstein ${SOURCE_FILES} CspSolver.cpp CspSolver.h)

SET( FOO_LINKFLAGS ${CMAKE_CURRENT_SOURCE_DIR}/einstein.res )
SET_TARGET_PROPERTIES( einstein PROPERTIES LINK_FLAGS ${FOO_LINKFLAGS} )