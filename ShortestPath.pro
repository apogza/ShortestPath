TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        graph.cpp \
        graph_edge.cpp \
        main.cpp \
        mst_finder.cpp \
        node_priority_queue.cpp \
        path_finder.cpp

HEADERS += \
    graph.h \
    graph_edge.h \
    mst_finder.h \
    node_priority_queue.h \
    path_finder.h

DISTFILES += \
    mst_data.txt
