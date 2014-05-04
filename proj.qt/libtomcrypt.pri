INCLUDEPATH += $$PWD/../src/headers
CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/bin/debug/ -llibtomcrypt
} else {
    LIBS += -L$$PWD/bin/release/ -llibtomcrypt
}
