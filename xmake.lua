--[[
Author: CsVeryLoveXieWenLi
Description: 4ascend-server
@Copyright (c) 2026 by CsVeryLoveXieWenLi, All Rights Reserved.
--]]

-- xmake project -k compile_commands


-- 运行库
if is_os("windows") then
    set_runtimes("MT")
end


-- 模式
add_rules("mode.release")
-- add_rules("mode.releasedbg")


-- 指令集
-- add_vectorexts("avx2")
-- add_vectorexts("sse4.2")


-- 头文件路径
add_includedirs("./submodule/cinatra/include")
add_includedirs("./submodule/nlohmann-json/include")


-- 优化等级
set_optimize("fastest")


-- 语言版本
set_languages("clatest", "c++20")


-- 任务配置
target("4ascend-server")
    set_kind("binary")
    add_files("src/*.cpp")

    set_strip("all")
    set_symbols("hidden")


--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

