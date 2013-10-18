TEMPLATE = app

CONFIG -= qt
CONFIG += debug

INCLUDEPATH = Headers/ /usr/local/include/webcpp/
OBJECTS_DIR = Build/
TARGET = WppTplEngine.so
DESTDIR = ../../../Debug/WebCpp/Plugins/TemplateEngines/

QMAKE_LFLAGS = -shared

debug {
	#DEFINES = DEBUG
	QMAKE_CXXFLAGS = -std=gnu++11 -fPIC -pedantic -Wextra -Ofast -march=native
} else {
	QMAKE_CXXFLAGS = -std=gnu++11 -fPIC -pedantic -Wextra -Ofast -march=native
}

SOURCES += \
    Sources/Block.cpp \
    Sources/CompiledTpl.cpp \
    Sources/Expr.cpp \
    Sources/ExprNode.cpp \
    Sources/WppTplEngine.cpp \
    Sources/Lexer.cpp \
    Sources/Parser.cpp \
    Sources/Operator.cpp \
    Sources/Operators/ArithmOps.cpp \
    Sources/Blocks/InheritanceBlocks.cpp \
    Sources/Blocks/ConditionBlocks.cpp \
    Sources/Blocks/ForBlocks.cpp \
    Sources/Operators/MiscOps.cpp \
    Sources/Function.cpp \
    Sources/Functions/MathFuncs.cpp \
    Sources/Functions/MiscFuncs.cpp \
    Sources/Filters/StringFilters.cpp \
    Sources/Operators/LogicOps.cpp \
    Sources/Operators/CompOps.cpp \
    Sources/Filters/LocaleFilters.cpp \
    Sources/Tests/LexerTests.cpp

HEADERS += \
    Headers/Block.h \
    Headers/Expr.h \
    Headers/ExprNode.h \
    Headers/WppTplEngine.h \
    Headers/CompiledTpl.h \
    Headers/Lexer.h \
    Headers/Parser.h \
    Headers/Operator.h \
    Headers/Operators/ArithmOps.h \
    Headers/Blocks/InheritanceBlocks.h \
    Headers/Blocks/ConditionBlocks.h \
    Headers/Blocks/ForBlocks.h \
    Headers/Operators/MiscOps.h \
    Headers/Function.h \
    Headers/Functions/MathFuncs.h \
    Headers/Functions/MiscFuncs.h \
    Headers/Filters/StringFilters.h \
    Headers/Operators/LogicOps.h \
    Headers/Operators/CompOps.h \
    Headers/Filters/LocaleFilters.h \
    Headers/Tests/LexerTests.h
