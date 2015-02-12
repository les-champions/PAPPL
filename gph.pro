TEMPLATE 	= app
CONFIG 		+= qt
DESTDIR 	= bin
OBJECTS_DIR     = .tmp
LIBS 		= -L/usr/lib/graphviz -lcgraph -lpathplan -lcdt -lgvplugin_dot_layout
LIBS            += "-LC:/Program Files (x86)/Graphviz2.38/lib/release/lib/" -lgvc
LIBS += -L$$PWD/../../Downloads/boost_1_57_0/bin.v2/libs/filesystem/build/gcc-mingw-4.9.2/release/link-static/threading-multi/ -lboost_filesystem-mgw49-mt-1_57
LIBS += -L$$PWD/../../Downloads/boost_1_57_0/bin.v2/libs/system/build/gcc-mingw-4.9.2/release/link-static/threading-multi/ -lboost_system-mgw49-mt-1_57

HEADERS 	= 	headers/Action.h 		\
                        headers/Exceptions.h 	\
                        headers/IO.h 			\
                        headers/GProcess.h 		\
                        headers/GAction.h 		\
                        headers/GSort.h 		\
                        headers/GVEdge.h 		\
                        headers/GVNode.h	 	\
                        headers/MainWindow.h 	\
                        headers/MyArea.h 		\
                        headers/PH.h 			\
                        headers/PHScene.h		\
                        headers/PHIO.h 			\
                        headers/Process.h 		\
                        headers/Sort.h \
                        headers/Area.h \
                        headers/TextArea.h \
                        headers/TreeArea.h \
                        headers/ColorerSequences.h \
                          #Connection.h \
                          #src/ui/connectionsettings.h \
                          #src/ui/ConnectionSettings.h \
                          #src/ui/ConnectionSettings.h \
                        headers/ConnectionSettings.h \
                        headers/ArgumentFrame.h \
                        headers/FuncFrame.h \
                        headers/FunctionForm.h \
                        headers/test/ChoixLigne.h \
                        headers/GVSkeletonGraph.h \
                        headers/TikzEditor.h

INCLUDEPATH = headers headers/axe headers/test
INCLUDEPATH += "C:/Users/IAZERTYUIOPI/Downloads/boost_1_57_0/boost/smart_ptr/"
INCLUDEPATH += "C:/Users/IAZERTYUIOPI/Downloads/boost_1_57_0/"
INCLUDEPATH += "C:/Program Files (x86)/Graphviz2.38/include"



SOURCES			= 	src/gfx/GProcess.cpp		\
                                src/gfx/GAction.cpp		\
                                src/gfx/GSort.cpp		\
                                src/gfx/PHScene.cpp		\
                                src/gviz/GVSkeletonGraph.cpp	\
                                src/io/IO.cpp			\
                                src/io/PHIO.cpp			\
                                src/ph/Action.cpp		\
                                src/ph/PH.cpp			\
                                src/ph/Process.cpp		\
                                src/ph/Sort.cpp			\
                                src/ui/MainWindow.cpp		\
                                src/ui/MyArea.cpp		\
                                src/ui/TextArea.cpp \
                                src/ui/TreeArea.cpp \
                                src/ui/Area.cpp \
                                src/ui/ColorerSequences.cpp \
                                src/ui/ConnectionSettings.cpp \
                                src/ui/ArgumentFrame.cpp \
                                src/ui/FuncFrame.cpp \
                                src/ui/FunctionForm.cpp \
                                src/ui/ChoixLigne.cpp \
                                src/ui/TikzEditor.cpp

#So 2013 (needed for Axe)
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -ggdb

QT += widgets

test {

        QMAKE_CXXFLAGS += -ggdb
        QT += testlib
        HEADERS +=	headers/test/PHIOTest.h
        SOURCES	+= 	src/test/TestRunner.cpp	\
                        src/test/PHIOTest.cpp

} else {
        SOURCES	+= src/Main.cpp
}

