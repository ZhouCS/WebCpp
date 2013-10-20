# WebCpp #

Welcome on the WebCpp project! WebCpp is a high-performance C++ Web development
framework licensed under GNU GPL.

Keep in mind that WebCpp in its early stages of development, it may not be user-
friendly nor stable. If you fail to compile, install or make WebCpp works, don't
hesitate to contact me: I will help you and write documentation / FAQ to help
future users.

## Why WebCpp? ##

With WebCpp you have the ability to develop websites directly in C++. Not only
for the love of that language but for performances. Thus reducing server costs
and providing a more reactive website.

Developping websites in C++ may seem cumbersome. Maybe it's true, but with
WebCpp, it's not the case anymore: now it's plain fun.

## How it works ##

WebCpp is, above all, a daemon. The user code is compiled in .so files
dynamicaly loaded by the framework. So, the user code does not have any `main`
function: the framework calls the user code, and not the reverse.

This executable is started in only one instance and initializes its ressources
(like loading the user modules, establishing a DB connection, loading
configuration, etc.) and enters in an execution loop. WebCpp uses FastCGI to
communicate with the HTTP server. The web server acts as a client which
connects the WebCpp daemon to send the request to process. WebCpp generates the
page and send it back to the HTTP server.

WebCpp initializes only once and keep everything (including configuration and
caches) in RAM for immediate access. This lets WebCpp focus on requests
processing.

## Who we are ##

I’m currently working alone on this project. I’m Kévin Lesénéchal, 21, and I
live in Paris. I’m studying computer science in EPITECH.

You can contact me by email at <kevin@lesenechal.org> or via Jabber at the same
address, in English or French.

## How it is organized ##

The repository is structured like this:

	├─ API     -- Contains public headers to put in /usr/local/include/webcpp/
	├─ Apps    -- Sub-applications like the template engine, DBMS implementations
	│  ├─ CodeHighlighters  -- Syntax highlighters plugins (e.g. C++, SQL)
	│  ├─ DBMS              -- Database implementations (e.g. MySQL, PostgreSQL)
	│  └─ WppTplEngine      -- The default WebCpp's template engine
	├─ Build   -- Temp directory where *.o files are located
	├─ Debug   -- The release of WebCpp, what you actually upload on your server
	│  ├─ Config.ini  -- Config general to the website (free format)
	│  ├─ Logs        -- Website's logs (not WebCpp's logs)
	│  ├─ MainRouter.yml  -- The main router of the site (resolves `/`)
	│  ├─ Mods        -- The site's mods
	│  │  └─ Sample     -- An example mod
	│  │     ├─ Sample.so    -- The mod's binary
	│  │     ├─ Public       -- Its public root (accessed via `/mods/sample/`)
	│  │     ├─ Router.yml   -- Its main router
	│  │     ├─ Templates    -- Its template files
	│  │     └─ Translations -- Its translation files
	│  ├─ Public      -- The HTTP public root (CSS, JS, images, etc.)
	│  ├─ Site.so     -- All code general to the website (not in mods)
	│  ├─ Templates   -- Template files general to the website (e.g. `About.html`)
	│  ├─ Translations -- XML files which contains site-general translations
	│  └─ WebCpp      -- The WebCpp framework internals
	│     ├─ Cache      -- Cache files
	│     │  └─ Public    -- Public cache files (accessed via `/sys/cache/`)
	│     ├─ Config.ini -- WebCpp's configuration (e.g. DB credentials)
	│     ├─ Logs       -- WebCpp's logs
	│     ├─ Plugins    -- Modular components like DBMS, template engines, etc.
	│     ├─ Public     -- WebCpp's public files (accessed via `/sys/`)
	│     ├─ Ressources -- Various files (like countries list)
	│     ├─ Templates  -- WebCpp's internals templates (like error pages)
	│     ├─ Tools      -- Third-party tools (like ClosureCompiler.jar)
	│     ├─ Translations -- WebCpp's translation files
	│     └─ WebCpp     -- The WebCpp's binary (the daemon)
	├─ Docs    -- Useful documentation files, read them!
	├─ Headers -- Header files (*.h)
	└─ Sources -- Source files (*.cpp)

Note: some directories may be missing from the git repository. It is because git
does not keep track of empty directories.

Here is the structure of the `Sources` and `Headers` directories:

	├─ DB  -- Interface to a DBMS (connections, queries, results)
	├─ Exceptions  -- Exception classes
	├─ Libs  -- Internal libs (not third-party)
	│  ├─ Crypt  -- Related to cryptography
	│  ├─ IO     -- Related to inputs/ouputs (files, processes, network, ...)
	│  ├─ Locale -- Related to i18n / translations
	│  ├─ Wml    -- YAML-like parser, obsolete: will be removed
	│  └─ Xml    -- Wrapper of pugixml lib
	├─ MVC  -- MVC components (including routing system and templates)
	│  ├─ Routers    -- Basic router and routes (for the routing system)
	│  └─ Templates  -- Interface to templates (not the template engine)
	├─ Plugins   -- Sources related to plugins
	├─ Requests  -- Requests handling (errors, profiling, sessions, I/O, ...)
	├─ Services  -- Services interface and basic services implementations
	├─ Shell     -- The development (run-time) shell
	├─ Sites     -- Site and modules management
	└─ Types     -- Basic type classes (strings, map, list, datetime, stack, ...)

## What is done so far ##

Currently these features are implemented:

 * Executing HTTP requests through FastCGI;
 * Receiving / sending HTTP headers;
 * `GET` / `POST` datas;
 * Cookies (reading and writing);
 * Sessions (with optional IP-check security);
 * `User-Agent` parsing;
 * Exceptions and segfaults handling;
 * Code profiling (execution time, SQL requests, warnings, etc.);
 * Dev-bar (like on Symfony2);
 * Plugins;
 * Controllers and actions;
 * Views and view variables (for templates);
 * Routers, routes (on controller/action, view and function) + arguments
 * Connection to a DBMS, query execution, result handling;
 * Implementation of the MariaDB / MySQL DBMS;
 * Utility classes (`String`, `ByteArray`, `Date`, `DateTime`, `List`, `Map`,
   `MultiMap`, `OrderedMap`, `Pair`, `Stack`, `String`, `StringList`, `Time`,
   `Variant`, `Chrono`);
 * Files and directories access (POSIX);
 * Regular expressions (with PCRE);
 * INI files parsing (using Boost);
 * Pseudo-random generator (thanks C++11);
 * Syntax highlighting (C++ currently implemented);
 * XML parsing (with `pugixml` lib);
 * Processus handling (POSIX);
 * Cryptographic hashes (SHA-256, SHA-384 and SHA-512 currently implemented);
 * Languages, translations and regional formats (on numbers, dates, etc.);
 * Dates and times, time zones, UTC ↔ local time conversions;
 * UTF-8 inputs security: suppression of invalid UTF-8 sequences (cf.
   [RFC3629](https://tools.ietf.org/html/rfc3629#section-10)), transparent
   correction of overlong sequences, suppression of undesirable characters
   (`SOH`, `STX`, `ETX`, `EOT`, `ENQ`, …) and replacement of `CRLF` by `LF`;
 * Development shell;
 * Templates engine (big!):
   * Blocks (if, elseif, else, for);
   * Expressions parsing and execution:
     * Literals (strings, int, float, lists, maps);
     * Variables;
     * Operators (unary, binary, precedance, associativity):
       * Arithmetic operators (`+`, `-`, `*`, `/`, `%`);
       * Logic operators (`&&`, `||`, `!`, `==`, `!=`, `<`, `<=`, `>`, `>=`);
       * Misc operators (`typeof`, `#`).
     * Functions;
     * Filters (e.g. `lastName|upper`);
     * Indexing (`str[2]`, `list[i + 1]`, `map['field']` or `map.field`).
   * Automatic formatting (on numbers, dates, strings, etc.).

## What needs to be done now ##

In a near future, here is what features are planned to be done:

 * Refactoring of the routing system to implement YAML routers, domains, HTTPS,
   redirections (e.g. `/forum` → `/forum/`, or `/about/` → `/about`) and path
   generation;
 * HTTPS / HSTS support + client certificates;
 * Fixing of some memory leaks;
 * *BSD support.

This will mark the first release (0.1), that will need to be the most stable
possible even if the later versions will not keep compatibility.

Some features are also planned for latter releases:

 * An ORM;
 * Emails sending;
 * Forms;
 * Experimental Windows support;
 * Thread-safety;
 * The manager: a low-level Web interface to manage WebCpp.

## Additional documentation ##

There is corrently not a lot of documentation available for WebCpp, I’m working
on it. Here is what you can find for the moment:

 * The Doxygen online documentation: <http://doc.webcpp.org/>;
 * The C++ coding rules: `./Docs/CodingRules.md`.
