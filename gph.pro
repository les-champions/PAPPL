TEMPLATE 	= app
CONFIG 		+= qt
DESTDIR 	= bin
OBJECTS_DIR     = .tmp
MOC_DIR         = .moc

LIBS 		=  /usr/local/Cellar/boost/1.57.0/lib/libboost_filesystem.a
LIBS            +=  /usr/local/Cellar/boost/1.57.0/lib/libboost_system.a
LIBS            +=  /usr/local/Cellar/graphviz/2.38.0/lib/libgvc.dylib
LIBS            +=  /usr/local/Cellar/graphviz/2.38.0/lib/libcgraph.dylib
LIBS            +=  /usr/local/Cellar/graphviz/2.38.0/lib/libpathplan.dylib
LIBS            +=  /usr/local/Cellar/graphviz/2.38.0/lib/libcdt.dylib
LIBS            +=  /usr/local/Cellar/graphviz/2.38.0/lib/graphviz/libgvplugin_dot_layout.dylib

HEADERS 	=   headers/Action.h \
                    headers/Exceptions.h \
                    headers/IO.h \
                    headers/GProcess.h \
                    headers/GAction.h \
                    headers/GSort.h \
                    headers/GVEdge.h \
                    headers/GVNode.h \
                    headers/MainWindow.h \
                    headers/MyArea.h \
                    headers/PH.h \
                    headers/PHScene.h \
                    headers/PHIO.h \
                    headers/Process.h \
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
INCLUDEPATH += /usr/local/Cellar/graphviz/2.38.0/include/
INCLUDEPATH += /usr/local/Cellar/boost/1.57.0/include/

SOURCES			=   src/gfx/GProcess.cpp \
                            src/gfx/GAction.cpp \
                            src/gfx/GSort.cpp \
                            src/gfx/PHScene.cpp \
                            src/gviz/GVSkeletonGraph.cpp \
                            src/io/IO.cpp \
                            src/io/PHIO.cpp \
                            src/ph/Action.cpp \
                            src/ph/PH.cpp \
                            src/ph/Process.cpp \
                            src/ph/Sort.cpp \
                            src/ui/MainWindow.cpp \
                            src/ui/MyArea.cpp \
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
QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -ggdb

QT += widgets

test {
  QMAKE_CXXFLAGS += -ggdb
  QT      += testlib
  HEADERS += headers/test/PHIOTest.h
  SOURCES += src/test/TestRunner.cpp	\
             src/test/PHIOTest.cpp
} else {
  SOURCES	+= src/Main.cpp
}

FORMS +=
