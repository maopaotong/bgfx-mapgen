
set_policy("build.progress_style", "multirow")
add_rules("mode.debug", "mode.release")
add_requires("bgfx")
set_defaultmode("debug")
target("hello")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("bgfx")
    
    