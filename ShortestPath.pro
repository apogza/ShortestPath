TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        graph.cpp \
        graph_edge.cpp \
        main.cpp \
        node_priority_queue.cpp \
        path_finder.cpp

HEADERS += \
    graph.h \
    graph_edge.h \
    node_priority_queue.h \
    path_finder.h
