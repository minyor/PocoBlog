# PocoBlog
Web framework in C++

## Features
* Templating
* Cross-Site Request Forgery (CSRF)
* SHA256 hashing
* Http sessions
* SqlLite and MySql support
* BBCode
* Emoticons
* Email verification
* UPnP port auto binding

## Getting Started
* Install CodeLite
* Download, build and install Poco C++ library
* Install 'libgupnp-1.0-dev'
* To disable UPnP, uncomment line '#define UPNP_DISABLED' in core/Header.h
* Build CodeLite project
* First registered user will become admin
* Email verification for other users
* Edit 'bin/WebServer.properties' for email server, port and other parameters
* Tested on Ubuntu 14.04 using gcc and clang

##License
BSD License
