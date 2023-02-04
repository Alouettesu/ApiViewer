TEMPLATE = subdirs

SUBDIRS += \
    common \
    qml \
    widgets

qml.depends = common
widgets.depends = common


OTHER_FILES += \
    .gitignore

DISTFILES += \
    readme.md
