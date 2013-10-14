TEMPLATE = app
CONFIG -= qt

CONFIG += debug

INCLUDEPATH = Headers
OBJECTS_DIR = Build
MOC_DIR = Build

DESTDIR = Debug/WebCpp
TARGET = WebCpp

LIBS = -lpcre -lfcgi++ -lfcgi -ldl -lboost_date_time -lboost_program_options -lpugixml -lyaml

debug {
	DEFINES = DEBUG
	QMAKE_CXXFLAGS = -std=gnu++11 -pedantic -Wextra -Ofast -march=native
	QMAKE_LFLAGS = -Wl,--export-dynamic
} else {
	QMAKE_CXXFLAGS = -std=gnu++11 -pedantic -Wextra -Ofast -march=native
	QMAKE_LFLAGS = -Wl,--export-dynamic
}


SOURCES += Sources/Main.cpp \
    Sources/System.cpp \
    Sources/Object.cpp \
    Sources/Types/Version.cpp \
    Sources/Types/Variant.cpp \
    Sources/Types/Time.cpp \
    Sources/Types/StringList.cpp \
    Sources/Types/String.cpp \
    Sources/Types/Stack.cpp \
    Sources/Types/Path.cpp \
    Sources/Types/Pair.cpp \
    Sources/Types/OrderedMap.cpp \
    Sources/Types/MultiMap.cpp \
    Sources/Types/Map.cpp \
    Sources/Types/List.cpp \
    Sources/Types/IpAddr.cpp \
    Sources/Types/DateTime.cpp \
    Sources/Types/Date.cpp \
    Sources/Types/ByteArray.cpp \
    Sources/Sites/Site.cpp \
    Sources/Sites/Module.cpp \
    Sources/Services/CliAdminService.cpp \
    Sources/Services/AbstractService.cpp \
    Sources/Requests/UserAgent.cpp \
    Sources/Requests/SystemRouter.cpp \
    Sources/Requests/Session.cpp \
    Sources/Requests/RequestThread.cpp \
    Sources/Requests/RequestStream.cpp \
    Sources/Requests/RequestProfile.cpp \
    Sources/Requests/RequestError.cpp \
    Sources/Requests/Request.cpp \
    Sources/Plugins/Plugin.cpp \
    Sources/MVC/Repository.cpp \
    Sources/MVC/Model.cpp \
    Sources/MVC/Entity.cpp \
    Sources/MVC/Controller.cpp \
    Sources/MVC/AbstractView.cpp \
    Sources/MVC/Templates/TemplatesManager.cpp \
    Sources/MVC/Templates/Template.cpp \
    Sources/MVC/Templates/AbstractTemplateEngine.cpp \
    Sources/MVC/Templates/AbstractCompiledTemplate.cpp \
    Sources/MVC/Routers/ViewRoute.cpp \
    Sources/MVC/Routers/Router.cpp \
    Sources/MVC/Routers/Route.cpp \
    Sources/MVC/Routers/FuncRoute.cpp \
    Sources/MVC/Routers/AbstractRouter.cpp \
    Sources/MVC/Routers/AbstractRoute.cpp \
    Sources/Libs/Thread.cpp \
    Sources/Libs/Settings.cpp \
    Sources/Libs/Regex.cpp \
    Sources/Libs/Random.cpp \
    Sources/Libs/Dir.cpp \
    Sources/Libs/Chrono.cpp \
    Sources/Libs/Xml/XmlNode.cpp \
    Sources/Libs/Xml/XmlDoc.cpp \
    Sources/Libs/Wml/WmlDocument.cpp \
    #Sources/Libs/ThirdParty/BacktraceSymbols.c \
    Sources/Libs/Locale/TransManager.cpp \
    Sources/Libs/Locale/Translation.cpp \
    Sources/Libs/Locale/TransContext.cpp \
    Sources/Libs/Locale/Locale.cpp \
    Sources/Libs/IO/Process.cpp \
    Sources/Libs/IO/IODevice.cpp \
    Sources/Libs/IO/File.cpp \
    Sources/Libs/Crypt/Sha2.cpp \
    Sources/Libs/Crypt/Hash.cpp \
    Sources/Exceptions/Plugins.cpp \
    Sources/Exceptions/Exception.cpp \
    Sources/DB/DatabaseSystem.cpp \
    Sources/DB/AbstractDbRow.cpp \
    Sources/DB/AbstractDbResult.cpp \
    Sources/DB/AbstractDbConnection.cpp \
    Sources/Shell/Shell.cpp \
    Sources/Shell/ShellCommand.cpp \
    Sources/Shell/CmdCore.cpp \
    Sources/CliOptions.cpp \
    Sources/Libs/StackTrace.cpp \
    Sources/Libs/CodeHighlighter.cpp

HEADERS += \
    Headers/System.h \
    Headers/Object.h \
    Headers/Types/Version.h \
    Headers/Types/Variant.h \
    Headers/Types/Time.h \
    Headers/Types/StringList.h \
    Headers/Types/String.h \
    Headers/Types/Stack.h \
    Headers/Types/Path.h \
    Headers/Types/Pair.h \
    Headers/Types/OrderedMap.h \
    Headers/Types/MultiMap.h \
    Headers/Types/Map.h \
    Headers/Types/List.h \
    Headers/Types/IpAddr.h \
    Headers/Types/DateTime.h \
    Headers/Types/Date.h \
    Headers/Types/ByteArray.h \
    Headers/Sites/Site.h \
    Headers/Sites/Module.h \
    Headers/Services/CliAdminService.h \
    Headers/Services/AbstractService.h \
    Headers/Requests/UserAgent.h \
    Headers/Requests/SystemRouter.h \
    Headers/Requests/Session.h \
    Headers/Requests/RequestThread.h \
    Headers/Requests/RequestStream.h \
    Headers/Requests/RequestProfile.h \
    Headers/Requests/RequestError.h \
    Headers/Requests/Request.h \
    Headers/Plugins/Plugin.h \
    Headers/MVC/Repository.h \
    Headers/MVC/Model.h \
    Headers/MVC/Entity.h \
    Headers/MVC/Controller.h \
    Headers/MVC/AbstractView.h \
    Headers/MVC/Templates/TemplatesManager.h \
    Headers/MVC/Templates/Template.h \
    Headers/MVC/Templates/AbstractTemplateEngine.h \
    Headers/MVC/Templates/AbstractCompiledTemplate.h \
    Headers/MVC/Routers/ViewRoute.h \
    Headers/MVC/Routers/Router.h \
    Headers/MVC/Routers/Route.h \
    Headers/MVC/Routers/FuncRoute.h \
    Headers/MVC/Routers/AbstractRouter.h \
    Headers/MVC/Routers/AbstractRoute.h \
    Headers/Libs/Thread.h \
    Headers/Libs/Settings.h \
    Headers/Libs/Regex.h \
    Headers/Libs/Random.h \
    Headers/Libs/Dir.h \
    Headers/Libs/Chrono.h \
    Headers/Libs/Xml/XmlNode.h \
    Headers/Libs/Xml/XmlDoc.h \
    Headers/Libs/Wml/WmlDocument.h \
    Headers/Libs/Locale/TransManager.h \
    Headers/Libs/Locale/Translation.h \
    Headers/Libs/Locale/TransContext.h \
    Headers/Libs/Locale/Locale.h \
    Headers/Libs/IO/Process.h \
    Headers/Libs/IO/IODevice.h \
    Headers/Libs/IO/File.h \
    Headers/Libs/Crypt/Sha2.h \
    Headers/Libs/Crypt/Hash.h \
    Headers/Exceptions/Xml.h \
    Headers/Exceptions/Types.h \
    Headers/Exceptions/Templates.h \
    Headers/Exceptions/Routers.h \
    Headers/Exceptions/Requests.h \
    Headers/Exceptions/Regex.h \
    Headers/Exceptions/Plugins.h \
    Headers/Exceptions/Exception.h \
    Headers/Exceptions/Db.h \
    Headers/Exceptions/Controllers.h \
    Headers/DB/DatabaseSystem.h \
    Headers/DB/AbstractDbRow.h \
    Headers/DB/AbstractDbResult.h \
    Headers/DB/AbstractDbConnection.h \
    Headers/Shell/Shell.h \
    Headers/Shell/ShellCommand.h \
    Headers/CliOptions.h \
    Headers/Exceptions/Files.h \
    Headers/Libs/StackTrace.h \
    Headers/Exceptions/Segfault.h \
    Headers/Libs/CodeHighlighter.h \
    Headers/Exceptions/CodeHighlighters.h

SOURCES -= Sources/Types/Stack.cpp \
    Sources/Types/Pair.cpp \
    Sources/Types/OrderedMap.cpp \
    Sources/Types/MultiMap.cpp \
    Sources/Types/Map.cpp \
    Sources/Types/List.cpp
